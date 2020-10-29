#ifndef TRANSACTIONMANAGER_H
#define TRANSACTIONMANAGER_H

#include <shared_mutex>

#include <tx.h>
#include <log.h>
#include <cachemanager.h>

namespace graph {





  class TransactionManager {
    public:
      TransactionManager(Log *log, CacheManager *cacheManager);
      ~TransactionManager();

      Tx *ReadOnlyTransaction();
      Tx *ReadWriteTransaction();

      bool Commit(Tx *tx);
      void Rollback(Tx *tx);
      void Finished(Tx *tx);


      CacheManager *GetCacheManager() { return this->m_cacheManager; }
      Log *GetLog() { return this->m_log; }

    protected:

    private:
      std::shared_mutex *m_mutex;
      Log* m_log;
      CacheManager* m_cacheManager;
  };

}
#endif // TRANSACTIONMANAGER_H
