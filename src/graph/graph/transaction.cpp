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

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  std::vector<Storeable*> Transaction::ModifiedObjects() {
    return this->m_transactionCacheManager.GetModifiedObjects();
    /*
    std::vector<Storeable*> v;
    v.reserve(this->m_allocatedObjects.size());

    for(auto obj : this->m_allocatedObjects) {
      if(obj->IsDirty()) {
        v.push_back(obj);
      }
    }
    return v;
    */
  }

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

    this->m_transactionCacheManager.Add(e);
    //this->m_allocatedObjects.push_back(e);
    this->m_allocatedIds.push_back(rec);
    return e;
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  Entity *Transaction::FindEntityById(gid id) {
    if(!this->IsReadable()) {
      std::cout << "[TX] Error - transaction is not readable." << std::endl;
      return 0x0;
    }

    // is the entity in the transaction cache?
    if(this->m_transactionCacheManager.Contains(Storeable::CEntity, id)) {
      return (Entity*)this->m_transactionCacheManager.Get(Storeable::CEntity, id);
    }

    ByteBuffer *b = this->CacheMan()->GetStoreableBuffer(Storeable::Concept::CEntity, id);
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
  Relation* Transaction::CreateRelation(gid type) {

    if(!this->IsWriteable()) {
      std::cout << "[TX] Error - transaction is not writeable." << std::endl;
      return  0x0;
    }

    StoreableId rec = this->AllocateId(Storeable::Concept::CRelation);
    Relation *r = new Relation(rec.Id);
    r->SetTypeId(type);
    r->SetTransaction(this);
    r->SetDirty(true);
    this->m_transactionCacheManager.Add(r);
    this->m_allocatedIds.push_back(rec);
    return r;
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
    Relation * Transaction::FindRelationById(gid id) {
      if(!this->IsReadable()) {
        std::cout << "[TX] Error - transaction is not readable." << std::endl;
        return 0x0;
      }

      // is the relation in the transaction cache?
      if(this->m_transactionCacheManager.Contains(Storeable::CRelation, id)) {
        return (Relation*)this->m_transactionCacheManager.Get(Storeable::CRelation, id);
      }


      ByteBuffer *b = this->CacheMan()->GetStoreableBuffer(Storeable::Concept::CRelation, id);
      if(b == 0x0) {
        std::cout << "[TX] Error - failed to load relation from cache." << std::endl;
        return 0x0;
      }
      Relation *r = new Relation(id, b);
      r->SetTransaction(this);

      this->m_transactionCacheManager.Add(r);
      //this->m_allocatedObjects.push_back(r);
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

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  void Transaction::ReleaseResources() {

    // allocated object are deleted when the TransactionCacheManage is destroyed

    /*for(auto obj : this->m_allocatedObjects) {
      delete obj;
    }*/

    for(auto obj : this->m_attributeCollections) {
      delete obj;
    }
  }

}

