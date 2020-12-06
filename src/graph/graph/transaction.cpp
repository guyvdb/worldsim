#include "transaction.h"


#include <transactionmanager.h>
#include <cache.h>
#include <types.h>

#include <storeable.h>
#include <entity.h>
#include <relation.h>
#include <attribute.h>

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
  Transaction::Transaction() : m_readonly(true), m_transactionManager(0x0), m_lastError(ErrorNone), m_state(Created) {
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
  CacheManager* Transaction::CacheMan() {
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

  std::vector<Storeable*> Transaction::ModifiedObjects() {
    std::vector<Storeable*> v;
    v.reserve(this->m_allocatedObjects.size());

    for(auto obj : this->m_allocatedObjects) {
      if(obj->IsDirty()) {
        v.push_back(obj);
      }
    }
    return v;
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
 /* Entity *Transaction::CopyEntity(Entity *src) {
    if(this->m_state != Started) {
      std::cout << "[TX] Error - transaction in wrong state to copy entity." << std::endl;
      return 0x0;
    }
    StoreableId rec = this->AllocateId(Storeable::Concept::CEntity);
    Entity *e = new Entity(rec.Id, src->Buffer());
    e->SetTypeId(src->GetTypeId());
    e->SetTransaction(this);
    this->m_createdObjects.push_back(e);
    this->m_allocatedIds.push_back(rec);
    return e;
  }*/

  /* ----------------------------------------------------------------------------------------
   * Create a new entity.
   * --------------------------------------------------------------------------------------*/
  Entity *Transaction::CreateEntity(gid type) {

    if(!this->IsWriteable()) {
      std::cout << "[TX] Error - transaction is not writeable." << std::endl;
      return  0x0;
    }

    StoreableId rec = this->AllocateId(Storeable::Concept::CEntity);
    Entity *e = new Entity(rec.Id);
    e->SetTypeId(type);
    e->SetTransaction(this);
    e->SetDirty(true);

    this->m_allocatedObjects.push_back(e);
    this->m_allocatedIds.push_back(rec);
    return e;
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  class Relation* Transaction::CreateRelation(gid type) {

    if(!this->IsWriteable()) {
      std::cout << "[TX] Error - transaction is not writeable." << std::endl;
      return  0x0;
    }

    StoreableId rec = this->AllocateId(Storeable::Concept::CRelation);
    class Relation *rel = new Relation(rec.Id);
    rel->SetTypeId(type);
    rel->SetTransaction(this);
    rel->SetDirty(true);
    this->m_allocatedObjects.push_back(rel);
    this->m_allocatedIds.push_back(rec);
    return rel;
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
    Relation * Transaction::FindRelationById(gid id) {
      if(!this->IsReadable()) {
        std::cout << "[TX] Error - transaction is not readable." << std::endl;
        return 0x0;
      }


      ByteBuffer *b = this->CacheMan()->GetStoreableBuffer(Storeable::Concept::CRelation, id);
      if(b == 0x0) {
        std::cout << "[TX] Error - failed to load relation from cache." << std::endl;
        return 0x0;
      }
      Relation *r = new Relation(id, b);

      this->m_allocatedObjects.push_back(r);
      return r;
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
  AttributeCollection* Transaction::LoadAttributes(StoreableWithAttributes *storeable) {
    if (this->m_state != Started) {
      std::cout << "[TX] Error - transaction not started." << std::endl;
      return 0x0;
    }

    // have we cached this collection in this transaction?
    if ( this->m_attributeCollectionIndex.find(storeable) == this->m_attributeCollectionIndex.end() ) {
      // not found - create collection and return
      AttributeCollection *c = new AttributeCollection(this, storeable);
      gid root = storeable->GetRootAttributesBucketId();

      // load from cache and follow linked list to get all buckets.
      // add bucket to collection
      // index it and return


      //this->m_transactionManager->GetCacheManager()->FindAttributeBucketById(root);

    } else {
      // return locally cached version
      return this->m_attributeCollectionIndex[storeable];
    }

  }


  void Transaction::ReleaseResources() {

    for(auto obj : this->m_allocatedObjects) {
      delete obj;
    }

    for(auto obj : this->m_attributeCollections) {
      delete obj;
    }
  }

}

