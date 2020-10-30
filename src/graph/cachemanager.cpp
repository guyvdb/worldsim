#include "cachemanager.h"

namespace graph {


  CacheManager::CacheManager(){

  }

  bool CacheManager::Open() {
    return true;
  }

  bool CacheManager::Close() {
    // All pages should have already been flushed ... assert that here

    // release all resources

    return true;
  }

  IdCacheItem *CacheManager::GetIdCache() {
    return 0x0;
  }

  Cache *CacheManager::GetCache(Storeable::Type type) {
    return 0x0;
  }

}
