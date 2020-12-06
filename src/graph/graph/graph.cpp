#include "graph.h"

#include <iostream>




namespace graph {


  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  Graph::Graph(Config &config) :
    m_path(std::filesystem::path(config.Path())),
    m_lastError(ErrorNone), m_isOpen(false),
    m_config(config)  {

    //std::cout << "Create id manager\n";
    this->m_idManager = new IdManager(config.DataDirectory());
    //std::cout << "Create store manager\n";
    this->m_storeManager = new StoreManager(config.DataDirectory(), config.PageSize());
    //std::cout << "Create cache manager\n";
    this->m_cacheManager = new CacheManager(this->m_storeManager,config);
    //std::cout << "Create log\n";
    this->m_log = new TransactionLog(config.LogDirectory());

    //std::cout << "Register Stores \n";
    // Register all the stores with the id manager
    for(auto &store : *this->m_storeManager->Stores()) {
      this->m_idManager->Register(store,store->GetConcept());
    }
    //std::cout << "Create complete\n";


    // Create the transaction manager
    this->m_transactionManager = new TransactionManager(this->m_log, this->m_cacheManager, this->m_idManager);
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

    delete this->m_transactionManager;
    delete this->m_idManager;
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

   // std::cout << "Open log \n";
    if(!this->m_log->Open()) {
      std::cout << "[GRAPH] Failed to open transaction log." << std::endl;
    }

    //std::cout << "Open  store manager\n";
    if(!this->m_storeManager->Open()) {
      std::cout << "[GRAPH] Failed to open store manager." << std::endl;
      this->m_log->Close();
      return false;
    }

    // replay the transaction log here if needed
    //std::cout << "Open  id manager: pointer = " << this->m_idManager << std::endl;

    if(!this->m_idManager->Open()) {
      std::cout << "[GRAPH] Failed to open id manager." << std::endl;
      this->m_log->Close();
      this->m_storeManager->Close();
      return false;
    }

    // open the cache manager

   // std::cout << "Open  complete\n";

    this->m_isOpen = true;
    return true;
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  void Graph::Close() {
    this->m_isOpen = false;

    // flush the cache

    this->m_log->Close();
    this->m_storeManager->Close();
    this->m_idManager->Close();


  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  bool Graph::Flush() {
    this->m_cacheManager->Flush();
    return true;
  }

  /* ----------------------------------------------------------------------------------------
   * A call to Read() creates a new readonly transaction via the transaction manager. The caller
   * MUST call Commit() or Rollback() on the transaction in order for the memory of the transaction
   * to be released
   * --------------------------------------------------------------------------------------*/
  bool Graph::Read(Transaction &tx) {
    return this->m_transactionManager->StartReadOnlyTransaction(tx);
  }
  //Tx *Graph::Read() {
  //  return this->m_transactionManager->ReadOnlyTransaction();
  //}

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  bool Graph::Update(Transaction &tx) {
    std::cout << "Graph Update: ->\n";
    return this->m_transactionManager->StartReadWriteTransaction(tx);
  }
  //Tx *Graph::Update() {
  //  return this->m_transactionManager->ReadWriteTransaction();
  //}

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
