#include "graph.h"

#include <iostream>

#include "entity.h"
#include "relation.h"


namespace graph {


  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  Graph::Graph(Config &config) : m_path(std::filesystem::path(config.Path())),
    m_lastError(graph::type::ErrorNone), m_isOpen(false), m_config(config)  {

    this->m_idManager = new id::IdManager(config.DataDirectory());
    this->m_storeManager = new store::StoreManager(config.DataDirectory(), config.PageSize());
    this->m_cacheManager = new cache::CacheManager(this->m_storeManager,config);
    this->m_log = new tx::TransactionLog(config.LogDirectory());
    for(auto &store : this->m_storeManager->GetStores()) {
      this->m_idManager->Register(store,store->GetConcept());
    }
    this->m_registry = new type::Registry(this,this->m_storeManager);
    this->m_transactionManager = new tx::TransactionManager(this->m_log, this->m_cacheManager,
                                                            this->m_idManager, this->m_registry);
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  Graph::~Graph() {
    delete this->m_transactionManager;
    delete this->m_registry;
    delete this->m_idManager;
    delete this->m_cacheManager;
    delete this->m_storeManager;
    delete this->m_log;
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  graph::type::ErrorNo Graph::LastError() {
    return this->m_lastError;
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  void Graph::SetError(graph::type::ErrorNo no) {
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

    if(!this->m_registry->Open()) {
      std::cout << "[GRAPH] Failed to open registry." << std::endl;
      this->m_log->Close();
      this->m_storeManager->Close();
      this->m_idManager->Close();
      return false;
    }


    // ensure the entity and relation types exist
    this->RegisterBaseClasses();

    this->m_isOpen = true;
    return true;
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  void Graph::Close() {
    this->m_isOpen = false;

    this->m_cacheManager->Flush();

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

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  bool Graph::Update(Transaction &tx) {
   // std::cout << "Graph Update: ->\n";
    return this->m_transactionManager->StartReadWriteTransaction(tx);
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  void Graph::RegisterClass(type::ClassDefinition definition) {
    this->m_registry->RegisterClass(definition);

  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  void Graph::RegisterBaseClasses() {
    bool entity = this->m_registry->ClassExists("Entity");
    bool relation = this->m_registry->ClassExists("Relation");

    if(!entity || !relation) {
      Transaction tx;
      if(this->Update(tx)) {
        if(!entity) {
          tx.CreateClass(Storeable::Concept::EntityConcept,"Entity",0x0);
        }
        if(!relation) {
          tx.CreateClass(Storeable::Concept::RelationConcept,"Relation",0x0);
        }
        if(!tx.Commit()) {
          std::cout << "[GRAPH] Error - failed to commit base type create transaction." << std::endl;
        }
      } else {
        std::cout << "[GRAPH] Error - failed to begin base type create transaction." << std::endl;
      }
    }

    // register the Factory Functions
    this->m_registry->RegisterFactoryFunction("Entity", Entity::GetFactoryFunc());
    this->m_registry->RegisterFactoryFunction("Relation",Relation::GetFactoryFunc());


  }

}
