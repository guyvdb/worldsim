#ifndef CACHEMANAGER_H
#define CACHEMANAGER_H

#include <types.h>
#include <storeable.h>
#include <storemanager.h>
#include <cache.h>

namespace graph {

  class Entity;
  class Relation;


  class CacheManager {
    public:
      CacheManager(StoreManager *storeManager);
      ~CacheManager();
      bool Open();
      bool Close();

      Cache *GetCache(Storeable::Concept concept);


      Entity *FindEntityById(gid id);
      Relation *FindRelationById(gid id);

    private:
      Storeable *FindObjectById(Cache *cache, gid id);

      StoreManager *m_storeManager;

      // the caches
      /*
      Cache *m_idStoreCache;

      Cache *m_thingStoreCache;
      Cache *m_thingTypeStoreCache;
      Cache *m_thingPropertyStoreCache;
      Cache *m_thingPropertyTypeStoreCache;

      Cache *m_relationStoreCache;
      Cache *m_relationTypeStoreCache;
      Cache *m_relationPropertyStoreCache;
      Cache *m_relationPropertyTypeStoreCache;
*/
      std::vector<Cache*> m_caches;
      std::map<Storeable::Concept, Cache*> m_cacheIndex;
  };

}
#endif // CACHEMANAGER_H
