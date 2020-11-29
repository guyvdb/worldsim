#include "transactionmanager.h"


namespace graph {


  TransactionManager::TransactionManager(TransactionLog *log, CacheManager *cacheManager, IdManager *idManager) :
    m_mutex(0x0), m_log(log), m_cacheManager(cacheManager), m_idManager(idManager) {
    this->m_mutex = new std::shared_mutex();
  }

  TransactionManager::~TransactionManager() {
    // check that there are no locks held

    delete this->m_mutex;
  }


  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  bool TransactionManager::StartReadOnlyTransaction(Transaction &tx) {

    // aquire a read mutext
    tx.ChangeState(Transaction::Started);
    tx.SetTransactionManager(this);
    tx.SetReadOnly(true);

    return true;
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  bool TransactionManager::StartReadWriteTransaction(Transaction &tx) {
    //txid id;
    //if(this->m_log->TransactionBegin(&id)) {
      tx.ChangeState(Transaction::Started);
      tx.SetTransactionManager(this);
      tx.SetReadOnly(false);
      //tx.SetTxId(id);
      //return true;
    //} else {
    //  return false;
    //}
      return true;
  }


  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  bool TransactionManager::Commit(Transaction &tx) {
    bool result = false;

    std::cout << "[TXMANAGER] Commit called" << std::endl;

    this->m_log->Lock();
    txid id = this->m_log->FrameStart();
    tx.SetTxId(id);

    // write a frame for every created object
    for(auto obj : *tx.CreatedObjects()){
      this->m_log->FrameAppend(obj->GetId(),obj->Type(),TransactionOp::Create,obj->Buffer());
    }

    // write a frame for every updated object

    // write a frame for every deleted objecgt

    //this->m_log->FrameAppend()
    // ..
    //this->m_log->FrameAppend();
    this->m_log->FrameEnd();

    this->m_log->Release();


    // the log is in locked state
    // add frame records to the log

    // end the transaction on the log
    //if(this->m_log->TransactionEnd(Committed)) {
    //  result = true;
    //}


    //this->m_log->TransactionRelease();
    //return result;

  }

  void TransactionManager::Rollback(Transaction &tx) {
    //this->m_log->TransactionEnd(RolledBack);
    //this->m_log->TransactionRelease();
  }

  StoreableId TransactionManager::AllocateId(Storeable::Concept concept) {
    StoreableId rec;
    rec.Id = (gid)this->m_idManager->NextGraphId(concept);
    rec.Type = concept;
    return rec;
  }

  bool TransactionManager::ReclaimId(StoreableId rec) {
    this->m_idManager->Reclaim((gid)rec.Id, rec.Type);
    return true;
  }



}
