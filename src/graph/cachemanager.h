#ifndef CACHEMANAGER_H
#define CACHEMANAGER_H

#include <types.h>
#include <storeable.h>

namespace graph {

  class Cache;
  class IdCacheItem;

  class CacheManager {
    public:
      CacheManager();

      bool Open();
      bool Close();

      IdCacheItem *GetIdCache();
      Cache *GetCache(Storeable::Type type);

    private:
      // the caches
      Cache *m_idStoreCache;

      Cache *m_thingStoreCache;
      Cache *m_thingTypeStoreCache;
      Cache *m_thingPropertyStoreCache;
      Cache *m_thingPropertyTypeStoreCache;

      Cache *m_relationStoreCache;
      Cache *m_relationTypeStoreCache;
      Cache *m_relationPropertyStoreCache;
      Cache *m_relationPropertyTypeStoreCache;

      std::vector<Cache*> *m_caches;
  };

}
#endif // CACHEMANAGER_H
