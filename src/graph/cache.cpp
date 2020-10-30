#include "cache.h"

#include <QDebug>

namespace graph {



  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  Cache::Cache(Store *store, std::size_t recsize) : m_store(store), m_recsize(recsize) {

  }

  //bool Cache::Close() {
    // The pages should be
  //}

  bool Cache::Flush() {
    return false;
  }


  GraphId* IdCacheItem::FindReclaimedId(Storeable::Type type) {
    return 0x0;
  }

  GraphId* IdCacheItem::LastId(Storeable::Type type) {
    return 0x0;
  }
}
