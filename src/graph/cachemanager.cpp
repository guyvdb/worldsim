#include "cachemanager.h"

namespace graph {


  CacheManager::CacheManager(StoreManager *storeManager) : m_storeManager(storeManager){
    // we need to create a cache for all the stores
    for(auto &store : *storeManager->Stores()) {
      Cache *c = new Cache(this,store->Type(),store->RecordSize(), store->PageSize());
      this->m_caches.push_back(c);
      this->m_cacheIndex[store->Type()] = c;
    }
  }

  CacheManager::~CacheManager() {
    for(auto &cache : this->m_caches) {
      delete cache;
    }
  }

  bool CacheManager::Open() {
    return true;
  }


  bool CacheManager::Close() {
    // All pages should have already been flushed ... assert that here

    // release all resources

    return true;
  }


  Cache *CacheManager::GetCache(Storeable::Concept concept) {
    std::map<Storeable::Concept,Cache*>::iterator it = this->m_cacheIndex.find(concept);
    if(it != this->m_cacheIndex.end()) {
      return it->second;
    }
    return 0x0;
  }

  Storeable *CacheManager::FindObjectById(Cache *cache, gid id) {
    // Pull out a storeable by id

    // compute the pageid for the gid

    // get that page



  }

  Entity *CacheManager::FindEntityById(gid id) {
    // find the store for entities

  }

  Relation *CacheManager::FindRelationById(gid id) {

  }

}
