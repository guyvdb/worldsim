#ifndef GRAPH_H
#define GRAPH_H

#include "graph_global.h"

#include <grapherrors.h>
#include <string>
#include <filesystem>

#include <type/base.h>
#include <config.h>

#include <storemanager.h>

#include <idmanager.h>
#include <tx/transactionlog.h>
#include <tx/transactionmanager.h>
#include <tx/transaction.h>


namespace graph {

  class GRAPH_EXPORT Graph {
    public:
      Graph(Config &config);
      ~Graph();
      bool Open();
      void Close();
      bool Flush();
      ErrorNo LastError();

      bool Register(type::Type *type);
      bool Register(std::vector<type::Type*> types);

      bool Read(tx::Transaction &tx);
      bool Update(tx::Transaction &tx);


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
      tx::TransactionManager *m_transactionManager;
      cache::CacheManager *m_cacheManager;
      tx::TransactionLog *m_log;



      // the indexes




  };

}
#endif // GRAPH_H
