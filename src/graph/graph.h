#ifndef GRAPH_H
#define GRAPH_H

#include "global.h"

#include "type/errors.h"
#include <string>
#include <filesystem>

#include "type/base.h"
#include "type/registry.h"

#include "config.h"

#include "store/storemanager.h"
#include "id/idmanager.h"

#include "wal/writeaheadlog.h"
#include "tx/transactionmanager.h"
#include "transaction.h"


namespace graph {

  class GRAPH_EXPORT Graph {
    public:
      Graph(Config &config);
      ~Graph();
      bool Open();
      void Close();
      bool Flush();
      graph::type::ErrorNo LastError();
      void RegisterClass(type::ClassDefinition definition);
      bool Read(Transaction &tx);
      bool Update(Transaction &tx);
    private:
      void RegisterBaseClasses();
      void SetError(graph::type::ErrorNo no);
      std::filesystem::path m_path;
      graph::type::ErrorNo m_lastError;
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
