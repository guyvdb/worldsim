#include "graph.h"

#include <iostream>


#include <gerror.h>

namespace graph {


  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  Graph::Graph(Config &config) :
    m_path(std::filesystem::path(config.Path())),
    m_lastError(ErrorNone), m_isOpen(false),
    m_config(config)  {


    this->m_storeManager = new StoreManager(config.DataDirectory(), config.PageSize());
    this->m_cacheManager = new CacheManager();
    this->m_log = new Log(config.LogDirectory());
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  Graph::~Graph() {
    // Flush all caches

    // Flush all datastores

    // Close all datastores

    // delete all caches

    // delete all datastores

    delete this->m_cacheManager;
    delete this->m_storeManager;
    delete this->m_log;
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  ErrorNo Graph::LastError() {
    return this->m_lastError;
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  void Graph::SetError(ErrorNo no) {
    this->m_lastError = no;
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  bool Graph::Open() {

    this->m_storeManager->Open();
    this->m_cacheManager->Open();
    this->m_log->Open();

    this->m_isOpen = true;
    return true;
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  bool Graph::Close() {
    if(!this->Flush()) {
      this->m_lastError = ErrorFileFlushError;
      return false;
    }


    this->m_log->Close();            // should force a shutdown checkpoint calculation
    this->m_cacheManager->Close();   // all pages should be fsynced via above checkpoint
    this->m_storeManager->Close();   // close all the stores

    this->m_isOpen = false;
    return true;
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  bool Graph::Flush() {
    return true;
  }

  /* ----------------------------------------------------------------------------------------
   * A call to Read() creates a new readonly transaction via the transaction manager. The caller
   * MUST call Commit() or Rollback() on the transaction in order for the memory of the transaction
   * to be released
   * --------------------------------------------------------------------------------------*/
  Tx *Graph::Read() {
    return this->m_transactionManager->ReadOnlyTransaction();
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  Tx *Graph::Update() {
    return this->m_transactionManager->ReadWriteTransaction();
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  /*Entity* Graph::NewEntity() {
    if(!this->m_isOpen) {
      this->SetError(ErrorFileNotOpen);
      return 0x0;
    }

    Entity *e = new Entity(this);
    return e;
  }*/

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  /*Relation* Graph::NewRelation() {
    if(!this->m_isOpen) {
      this->SetError(ErrorFileNotOpen);
      return 0x0;
    }
    Relation *r = new Relation(this);
    return r;
  }*/



  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
 /* void Graph::CloseAllStores() {
    // Iterate and print values of vector
    for(Store *s : *this->m_dataStores) {
      if(s->IsOpen()) {
        s->Close();
      }
    }
  }*/

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
/*  void Graph::FlushAllCaches() {
    for(Cache *c : *this->m_caches) {
      c->Flush();
    }
  }*/
}
