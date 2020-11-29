#ifndef TRANSACTIONMANAGER_H
#define TRANSACTIONMANAGER_H

#include <shared_mutex>

#include <transaction.h>
#include <transactionlog.h>
#include <cachemanager.h>
#include <idmanager.h>

namespace graph {





  class TransactionManager {
    friend Transaction;
    public:
      TransactionManager(TransactionLog *log, CacheManager *cacheManager, IdManager *idManager);
      ~TransactionManager();

      bool StartReadOnlyTransaction(Transaction &tx);
      bool StartReadWriteTransaction(Transaction &tx);
      bool Commit(Transaction &tx);
      void Rollback(Transaction &tx);

      CacheManager *GetCacheManager() { return this->m_cacheManager; }
      TransactionLog *GetLog() { return this->m_log; }

    protected:

      StoreableId AllocateId(Storeable::Concept concept);

      // Allow the id manager to reclaim an id that was not used
      bool ReclaimId(StoreableId id);

    private:
      std::shared_mutex *m_mutex;
      TransactionLog* m_log;
      CacheManager* m_cacheManager;
      IdManager *m_idManager;




      //std::vector<Tx&> m_currentTransactions;
  };

}
#endif // TRANSACTIONMANAGER_H
