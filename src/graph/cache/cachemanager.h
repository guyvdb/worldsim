#ifndef CACHEMANAGER_H
#define CACHEMANAGER_H

#include <type/base.h>
#include <storeable.h>
#include <storemanager.h>
#include <cache/cache.h>
#include <config.h>

namespace graph {

  class Entity;
  class Relation;
  class AttributeBucket;

  namespace cache {



    class CacheManager {
      public:
        CacheManager(StoreManager *storeManager, Config &config);
        ~CacheManager();
        bool Open();
        bool Close();
        Cache *GetCache(Storeable::Concept concept);
        ByteBuffer* GetStoreableBuffer(Storeable::Concept concept, type::gid id);
        bool SetStoreable(Storeable *storeable);

        void Flush();

        //Entity *FindEntityById(gid id);
        //Relation *FindRelationById(gid id);
        //AttributeBucket *FindAttributeBucketById(gid id);
      private:
        Storeable *FindObjectById(Cache *cache, type::gid id);
        StoreManager *m_storeManager;
        std::vector<Cache*> m_caches;
        std::map<Storeable::Concept, Cache*> m_cacheIndex;
    };


  }
}
#endif // CACHEMANAGER_H
