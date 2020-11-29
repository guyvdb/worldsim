#ifndef GRAPH_H
#define GRAPH_H

#include "graph_global.h"


#include <string>
#include <filesystem>

#include <types.h>
#include <config.h>
#include <transaction.h>
#include <storemanager.h>
#include <transactionmanager.h>
#include <idmanager.h>
#include <transactionlog.h>




namespace graph {

  class GRAPH_EXPORT Graph {
    public:
      Graph(Config &config);
      ~Graph();
      bool Open();
      void Close();
      bool Flush();
      ErrorNo LastError();


      bool Read(Transaction &tx);
      bool Update(Transaction &tx);


      //Tx *Read();
      //Tx *Update();


    private:

      void SetError(ErrorNo no);
      //void CloseAllStores();
      //void FlushAllCaches();

      std::filesystem::path m_path;
      ErrorNo m_lastError;
      bool m_isOpen;
      Config &m_config;
      IdManager *m_idManager;
      StoreManager *m_storeManager;
      TransactionManager *m_transactionManager;
      CacheManager *m_cacheManager;
      TransactionLog *m_log;



      // the indexes




  };

}
#endif // GRAPH_H
