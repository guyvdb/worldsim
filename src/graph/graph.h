#ifndef GRAPH_H
#define GRAPH_H

#include "graph_global.h"

#include <grapherrors.h>
#include <string>
#include <filesystem>

#include <type/base.h>
#include <type/registry.h>

#include <config.h>

#include <store/storemanager.h>
#include <id/idmanager.h>

#include <wal/writeaheadlog.h>
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

      void RegisterType(type::TypeDefinition definition);

      bool Read(tx::Transaction &tx);
      bool Update(tx::Transaction &tx);


    private:

      void EnsureBaseTypes();
      void SetError(ErrorNo no);
      //void CloseAllStores();
      //void FlushAllCaches();

      std::filesystem::path m_path;
      ErrorNo m_lastError;
      bool m_isOpen;
      Config &m_config;
      id::IdManager *m_idManager;
      store::StoreManager *m_storeManager;
      tx::TransactionManager *m_transactionManager;
      cache::CacheManager *m_cacheManager;
      tx::TransactionLog *m_log;
      type::Registry *m_registry;



      // the indexes




  };

}
#endif // GRAPH_H
