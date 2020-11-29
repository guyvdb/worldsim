#include "transaction.h"

#include <types.h>
#include <transactionmanager.h>
#include <cache.h>

#include <entity.h>
#include <type.h>
#include <relation.h>
#include <attribute.h>
#include <type.h>

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
  Entity *Transaction::CopyEntity(Entity *src) {
    if(this->m_state != Started) {
      std::cout << "[TX] Error - transaction in wrong state to copy entity." << std::endl;
      return 0x0;
    }
    StoreableId rec = this->AllocateId(Storeable::Concept::Entity);
    Entity *e = new Entity(rec.Id, src->Buffer());
    this->m_createdObjects.push_back(e);
    this->m_allocatedIds.push_back(rec);
    return e;
  }

  /* ----------------------------------------------------------------------------------------
   * Create a new entity.
   * --------------------------------------------------------------------------------------*/
  Entity *Transaction::CreateEntity(gid type) {

    if (this->m_state != Started) {
      std::cout << "[TX] Error - transaction in wrong state to create entity." << std::endl;
      return 0x0;
    }

    StoreableId rec = this->AllocateId(Storeable::Concept::Entity);
    Entity *e = new Entity(rec.Id);
    this->m_createdObjects.push_back(e);
    this->m_allocatedIds.push_back(rec);
    return e;
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  StoreableId Transaction::AllocateId(Storeable::Concept concept) {
    return this->m_transactionManager->AllocateId(concept);
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  bool Transaction::ReclaimId(StoreableId id) {
    return this->m_transactionManager->ReclaimId(id);
  }


  /* ----------------------------------------------------------------------------------------
   * A new graph id is needed for a given storable type. This id is either going to be a new
   * id for the given type or a reclaimed one.
   * --------------------------------------------------------------------------------------*/
  /*gid Transaction::NextGraphId(Storeable::Type type) {
    std::cout << "Warning: Tx::NextGraphId is returning a temporary rolling sequence" << std::endl;
    gid id = this->m_counter;
    std::cout << "[TX] Graphid will be " << id << std::endl;
    this->m_counter++;
    return id;
  }*/

  void Transaction::ReleaseResources() {
    for(auto obj : this->m_createdObjects) {
      delete obj;
    }
  }

}

