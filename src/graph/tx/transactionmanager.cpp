#include "transactionmanager.h"


namespace graph {

  namespace tx {


    /* ----------------------------------------------------------------------------------------
     *
     * --------------------------------------------------------------------------------------*/
    TransactionManager::TransactionManager(TransactionLog *log, cache::CacheManager *cacheManager,
                                           id::IdManager *idManager, type::Registry *registry) :
      m_mutex(0x0), m_log(log), m_cacheManager(cacheManager), m_idManager(idManager), m_typeRegistry(registry) {
      this->m_mutex = new std::shared_mutex();
    }

    /* ----------------------------------------------------------------------------------------
     *
     * --------------------------------------------------------------------------------------*/
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
      type::txid id = this->m_log->FrameStart();
      tx.SetTxId(id);


      std::vector<Storeable*> modified = tx.ModifiedObjects();

      // write a frame for every created object
      for(auto obj : modified){
        this->m_log->FrameAppend(obj->GetGraphId(),obj->GetConcept(),TransactionOp::Create,obj->Buffer());
      }
      this->m_log->FrameEnd();
      this->m_log->Release();


      // now check which objects need to be written back to the cach
      for(auto obj : modified) {
        this->GetCacheManager()->SetStoreable(obj);
        std::cout << "Need to save object type=" << obj->GetConceptString() << ", id=" << obj->GetGraphId() << std::endl;
      }

      tx.ChangeState(Transaction::Committed);

      // the log is in locked state
      // add frame records to the log

      // end the transaction on the log
      //if(this->m_log->TransactionEnd(Committed)) {
      //  result = true;
      //}


      //this->m_log->TransactionRelease();
      return result;

    }

    void TransactionManager::Rollback(Transaction &tx) {
      //this->m_log->TransactionEnd(RolledBack);
      //this->m_log->TransactionRelease();
    }

    StoreableId TransactionManager::AllocateId(Storeable::Concept concept) {
      StoreableId rec;
      rec.Id = (type::gid)this->m_idManager->NextGraphId(concept);
      rec.Type = concept;
      return rec;
    }

    bool TransactionManager::ReclaimId(StoreableId rec) {
      this->m_idManager->Reclaim((type::gid)rec.Id, rec.Type);
      return true;
    }


  }

}
