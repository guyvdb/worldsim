#include "transaction.h"


#include <tx/transactionmanager.h>
#include <cache/cache.h>
#include <type/base.h>

#include <storeable.h>
#include <entity.h>
#include <relation.h>
#include <class.h>

#include <cassert>
#include <iostream>

namespace graph {






  // What states can the transaction be in .... .
  // created
  // started
  // rolled-back
  // committed



  /* ----------------------------------------------------------------------------------------
   * A transaction is created in the Created state. Once the transaction is started via the
   * TransactionManage its state is changed to Started. Finally its state is changed to
   * Committed or RolledBack
   * --------------------------------------------------------------------------------------*/
  Transaction::Transaction() : m_readonly(true), m_transactionManager(0x0), m_lastError(graph::type::ErrorNone), m_state(Created) {
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  Transaction::~Transaction() {
    // If we are in started state then no commit was issued. Do a rollback
    if(this->m_state == Started) {
      this->Rollback();
    }
  }


  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  bool Transaction::Commit() {
    // what changes have been made?
    if(this->m_transactionManager->Commit(*this)) {
      this->ReleaseResources();
      this->m_state = Committed;
      return true;
    } else {
      this->ReleaseResources();
      this->m_state = RolledBack;
      return false;
    }
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  void Transaction::Rollback() {
    this->m_transactionManager->Rollback(*this);
    this->ReleaseResources();
    this->m_state = RolledBack;
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  cache::CacheManager* Transaction::CacheMan() {
    return this->TxMan()->GetCacheManager();
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  bool Transaction::IsReadable() {
    if(this->m_state != Started) {
      return false;
    }
    return true;
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  bool Transaction::IsWriteable() {
    if(!this->IsReadable() || this->m_readonly) {
      return false;
    }
    return true;
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  std::vector<Storeable*> Transaction::ModifiedObjects() {
    return this->m_transactionCacheManager.GetModifiedObjects();
  }

  /* ----------------------------------------------------------------------------------------
   * Create a new entity.
   * --------------------------------------------------------------------------------------*/
  Entity *Transaction::CreateEntity(type::gid clazz) {
    if(!this->IsWriteable()) {
      std::cout << "[TX] Error - transaction is not writeable." << std::endl;
      return  0x0;
    }

    StoreableId rec = this->AllocateId(Storeable::Concept::EntityConcept);

    // use the type system to create the entity as there might be a more
    // specialised class available

    Entity *e = new Entity(rec.Id);
    e->SetFlag(0x1);
    e->SetClassId(clazz);
    e->SetTransaction(this);
    e->SetDirty(true);

    this->m_transactionCacheManager.Add(e);
    //this->m_allocatedObjects.push_back(e);
    this->m_allocatedIds.push_back(rec);
    return e;
  }

  Entity *Transaction::CreateEntity(std::string clazz) {

  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  Entity *Transaction::FindEntity(type::gid id) {
    if(!this->IsReadable()) {
      std::cout << "[TX] Error - transaction is not readable." << std::endl;
      return 0x0;
    }

    // is the entity in the transaction cache? If so return that copy
    if(this->m_transactionCacheManager.Contains(Storeable::EntityConcept, id)) {
      return (Entity*)this->m_transactionCacheManager.Get(Storeable::EntityConcept, id);
    }


    graph::type::ByteBuffer *b = this->CacheMan()->CopyBytesFromPage(Storeable::Concept::EntityConcept, id);
    if(b == 0x0) {
      std::cout << "[TX] Error - failed to load entity from cache." << std::endl;
      return 0x0;
    }
    Entity *e = new Entity(id, b);
    e->SetTransaction(this);
    this->m_transactionCacheManager.Add(e);
    //this->m_allocatedObjects.push_back(e);
    return e;
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  Class *Transaction::CreateClass(Storeable::Concept concept, std::string name, Class *superclass) {
    Class *super = superclass;

    if(!this->IsWriteable()) {
      std::cout << "[TX] Error - transaction is not writeable." << std::endl;
      return 0x0;
    }

    // make sure type name is unique
    if(this->m_transactionManager->GetTypeRegistry()->ClassExists(name)) {
      std::cout << "[TX] Error - class " << name << " already exists." << std::endl;
      return 0x0;
    }

    // Only create types derived from entity and relation
    if(concept != Storeable::Concept::EntityConcept && concept != Storeable::Concept::RelationConcept) {
      std::cout << "[TX] Error - can only create classes for entities and relations." << std::endl;
      return 0x0;
    }

    // entity and relation will have null superclasses
    // every other class has a superclass even if not provided
    if(super == 0x0 && name != "entity" && name != "relation") {
      if(concept == Storeable::Concept::EntityConcept) {
        super = this->FindClass("Entity");
      } else {
        super = this->FindClass("Relation");
      }
    }

    // create the type
    StoreableId rec = this->AllocateId(Storeable::Concept::ClassConcept);
    Class *t = new Class(rec.Id);
    t->SetFlag(0x1);
    t->SetTransaction(this);
    t->SetDirty(true);
    t->SetName(name);
    t->SetTargetConcept(concept);

    // set up the heirachy
    if(super != 0x0) {
      t->SetSuperclassId(super->GetGraphId());
      Inheritance *i = super->AddSubclass(t);
      std::cout << "inheritance: id=" << i->GetGraphId() <<
                   ", super=" << i->GetSuperclassId() <<
                   ", sub=" << i->GetSubclassId() <<
                   ", next=" << i->GetNextInheritanceId() <<
                   ", prev=" << i->GetPrevInheritanceId() <<
                   ", supername=" << super->GetName() << std::endl;
    }

    // house keeping
    this->m_transactionCacheManager.Add(t);
    this->m_allocatedIds.push_back(rec);
    this->m_transactionManager->GetTypeRegistry()->IndexTypeName(rec.Id, name);

    return t;
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  Class *Transaction::FindClass(type::gid id) {
    if(!this->IsReadable()) {
      std::cout << "[TX] Error - transaction is not readable." << std::endl;
      return 0x0;
    }

    // is the entity in the transaction cache?
    if(this->m_transactionCacheManager.Contains(Storeable::ClassConcept, id)) {
      return (Class*)this->m_transactionCacheManager.Get(Storeable::ClassConcept, id);
    }

    graph::type::ByteBuffer *b = this->CacheMan()->CopyBytesFromPage(Storeable::Concept::ClassConcept, id);
    if(b == 0x0) {
      std::cout << "[TX] Error - failed to load class from cache." << std::endl;
      return 0x0;
    }

    Class *c = new Class(id, b);
    c->SetTransaction(this);
    this->m_transactionCacheManager.Add(c);
    return c;
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  Class *Transaction::FindClass(std::string name) {
    if(!this->m_transactionManager->GetTypeRegistry()->ClassExists(name)) {
      return 0x0;
    }
    type::gid id = this->m_transactionManager->GetTypeRegistry()->GetClassGraphId(name);
    return this->FindClass(id);
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  Inheritance *Transaction::CreateInheritance(type::gid superclass, type::gid subclass) {
    if(!this->IsWriteable()) {
      std::cout << "[TX] Error - transaction is not writeable." << std::endl;
      return 0x0;
    }

    StoreableId rec = this->AllocateId(Storeable::Concept::InheritanceConcept);
    Inheritance *h = new Inheritance(rec.Id);
    h->SetFlag(0x1);
    h->SetTransaction(this);
    h->SetDirty(true);
    h->SetSuperclassId(superclass);
    h->SetSubclassId(subclass);


    this->m_transactionCacheManager.Add(h);
    this->m_allocatedIds.push_back(rec);
    return h;
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  Inheritance *Transaction::FindInheritance(type::gid id) {
    if(!this->IsReadable()) {
      std::cout << "[TX] Error - transaction is not readable." << std::endl;
      return 0x0;
    }

    // is the entity in the transaction cache?
    if(this->m_transactionCacheManager.Contains(Storeable::InheritanceConcept, id)) {
      return (Inheritance*)this->m_transactionCacheManager.Get(Storeable::InheritanceConcept, id);
    }

    graph::type::ByteBuffer *b = this->CacheMan()->CopyBytesFromPage(Storeable::Concept::InheritanceConcept, id);
    if(b == 0x0) {
      std::cout << "[TX] Error - failed to load inheritance from cache." << std::endl;
      return 0x0;
    }

    Inheritance *h = new Inheritance(id, b);
    h->SetTransaction(this);
    this->m_transactionCacheManager.Add(h);
    return h;
  }


  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  Relation* Transaction::CreateRelation(type::gid clazz) {
    if(!this->IsWriteable()) {
      std::cout << "[TX] Error - transaction is not writeable." << std::endl;
      return  0x0;
    }

    StoreableId rec = this->AllocateId(Storeable::Concept::RelationConcept);
    Relation *r = new Relation(rec.Id);
    r->SetFlag(0x1);
    r->SetClassId(clazz);
    r->SetTransaction(this);
    r->SetDirty(true);
    this->m_transactionCacheManager.Add(r);
    this->m_allocatedIds.push_back(rec);
    return r;
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
    Relation * Transaction::FindRelationById(type::gid id) {
      if(!this->IsReadable()) {
        std::cout << "[TX] Error - transaction is not readable." << std::endl;
        return 0x0;
      }

      // is the relation in the transaction cache?
      if(this->m_transactionCacheManager.Contains(Storeable::RelationConcept, id)) {
        // return from transaction cache
        return (Relation*)this->m_transactionCacheManager.Get(Storeable::RelationConcept, id);
      } else {
        // return from file cache
        graph::type::ByteBuffer *b = this->CacheMan()->CopyBytesFromPage(Storeable::Concept::RelationConcept, id);
        if(b == 0x0) {
          std::cout << "[TX] Error - failed to load relation from cache." << std::endl;
          return 0x0;
        }
        Relation *r = new Relation(id, b);
        r->SetTransaction(this);
        this->m_transactionCacheManager.Add(r);
        return r;
      }
  }


  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  StoreableId Transaction::AllocateId(Storeable::Concept concept) {
    return this->TxMan()->AllocateId(concept);
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  bool Transaction::ReclaimId(StoreableId id) {
    return this->TxMan()->ReclaimId(id);
  }


  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  void Transaction::ReleaseResources() {

  }


}

