#ifndef GRAPH_H
#define GRAPH_H

#include "graph_global.h"

#include <string>
#include <filesystem>
#include <gerror.h>
#include <config.h>
#include <tx.h>
#include <storemanager.h>
#include <transactionmanager.h>
#include <log.h>




namespace graph {

  class GRAPH_EXPORT Graph {
    public:
      Graph(Config &config);
      ~Graph();
      bool Open();
      bool Close();
      bool Flush();
      ErrorNo LastError();



      Tx *Read();
      Tx *Update();


    private:

      void SetError(ErrorNo no);
      //void CloseAllStores();
      //void FlushAllCaches();

      std::filesystem::path m_path;
      ErrorNo m_lastError;
      bool m_isOpen;
      Config &m_config;

      StoreManager *m_storeManager;
      TransactionManager *m_transactionManager;
      CacheManager *m_cacheManager;
      Log *m_log;



      // the indexes




  };

}
#endif // GRAPH_H
