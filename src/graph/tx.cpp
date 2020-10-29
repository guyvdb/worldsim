#include "tx.h"

#include <gid.h>
#include <transactionmanager.h>
#include <cache.h>
#include <cassert>
#include <iostream>

namespace graph {

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  Tx::Tx(TransactionManager *manager, bool readonly) :
   m_readonly(readonly), m_transactionManager(manager),
    m_lastError(ErrorNone), m_modified(0x0), m_counter((gid)10) {

    // Create the last modified list. These are storables that need to be written back to the
    // cache on a successful sync of the log.
    this->m_modified = new std::vector<Storeable*>();
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  Tx::~Tx() {
    // the modified list should be empty
    assert(this->m_modified->size() == 0);
    delete this->m_modified;
  }


  /* ----------------------------------------------------------------------------------------
   * A transaction tracks the state of all data objects that are creates/modified/deleted within
   * its scope. On commit, a transaction frame is created in the log. Each modification is recorded
   * in the log. The frame is commited to the log and flushed to disk. Once the frame has been
   * successfully flushed, the changes are applied to the cache and the appropriate pages are
   * marked as dirty.
   * --------------------------------------------------------------------------------------*/
  bool Tx::Commit() {
    // do log commit

    // do cache commit

    // release resources
    this->ReleaseModifiedResource();

    return true;
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  Thing *Tx::NewThing() {

    gid id = this->NextGraphId(Storeable::Type::Thing);
    std::cout << "[TX] Assign graphid " << id << std::endl;

    Thing *t = new Thing(id);
    std::cout << "[TX] Thing created" << std::endl;

    this->m_modified->push_back(t);
    std::cout << "[TX] Thing added to modified" << std::endl;
    return t;
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  void Tx::ReleaseModifiedResource() {
    for(auto t : *this->m_modified) {
      delete t;
    }
    this->m_modified->clear();
  }

  /* ----------------------------------------------------------------------------------------
   * A new graph id is needed for a given storable type. This id is either going to be a new
   * id for the given type or a reclaimed one.
   * --------------------------------------------------------------------------------------*/
  gid Tx::NextGraphId(Storeable::Type type) {
    std::cout << "Warning: Tx::NextGraphId is returning a temporary rolling sequence" << std::endl;


    gid id = this->m_counter;

    std::cout << "[TX] Graphid will be " << id << std::endl;

    this->m_counter++;



    return id;
    /*
    IdCache *cache = this->m_transactionManager->GetCacheManager()->GetIdCache();

    GraphId* id = cache->FindReclaimedId(type);
    if (id == 0x0) {
      // There is no reclaimed GraphId
      id = cache->LastId(type);

      // increment the id and place it in the modified list
    }
    */
  }

}

