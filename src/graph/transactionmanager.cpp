#include "transactionmanager.h"


namespace graph {


  TransactionManager::TransactionManager(Log *log, CacheManager *cacheManager) :
    m_mutex(0x0), m_log(log), m_cacheManager(cacheManager) {
    this->m_mutex = new std::shared_mutex();
  }

  TransactionManager::~TransactionManager() {
    // check that there are no locks held

    delete this->m_mutex;
  }


  /* ----------------------------------------------------------------------------------------
   * This begins a readonly transaction. Any storable objects created during the scope of the
   * transaction belong to the transaction. Any modifications to objects will not be persisted
   * as this is a readonly transaction. When the caller is finished with the transaction
   * they must call Done() on the transaction to free its resources
   * --------------------------------------------------------------------------------------*/
  Tx *TransactionManager::ReadOnlyTransaction() {
    // Lock the mutex in shared mode for read transaction
    return new Tx(this,true);
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  Tx *TransactionManager::ReadWriteTransaction() {
    // Lock the mutex in exclusive mode for read/write transaction
    return new Tx(this,false);
  }

  bool TransactionManager::Commit(Tx *tx){
    // Write the transaction to the log  & ensure sync to disk

    // Modify the appropriate cache pages

    // Notify the transaction to delete any storable objects it created

    // delete the transaction
    delete tx;

    // adjust the mutex


  }

  void TransactionManager::Rollback(Tx *tx) {

  }

  void TransactionManager::Finished(Tx *tx) {

  }



}
