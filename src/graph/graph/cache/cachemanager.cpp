#include "cachemanager.h"
#include <entity.h>
#include <relation.h>
#include <cassert>

namespace graph {

  namespace cache {


    /* ----------------------------------------------------------------------------------------
     *
     * --------------------------------------------------------------------------------------*/
    CacheManager::CacheManager(store::StoreManager *storeManager, Config &config) : m_storeManager(storeManager){
      // we need to create a cache for all the stores
      for(auto &store : storeManager->GetStores()) {
        //std::cout << "[CACHE] Load cache for: " << store->Filename() << std::endl;
        std::size_t max = config.GetCacheMaxPages(store->GetConcept());
        Cache *c = new Cache(this,store, max);
        this->m_caches.push_back(c);
        this->m_cacheIndex[store->GetConcept()] = c;
      }
    }

    /* ----------------------------------------------------------------------------------------
     *
     * --------------------------------------------------------------------------------------*/
    CacheManager::~CacheManager() {
      for(auto &cache : this->m_caches) {
        delete cache;
      }
    }

    /* ----------------------------------------------------------------------------------------
     *
     * --------------------------------------------------------------------------------------*/
    bool CacheManager::Open() {
      return true;
    }


    /* ----------------------------------------------------------------------------------------
     *
     * --------------------------------------------------------------------------------------*/
    bool CacheManager::Close() {
      this->Flush();
      return true;
    }

    /* ----------------------------------------------------------------------------------------
     *
     * --------------------------------------------------------------------------------------*/
    void CacheManager::Flush() {
      for(auto cache : this->m_caches) {
        cache->Flush();
      }
    }

    /* ----------------------------------------------------------------------------------------
     *
     * --------------------------------------------------------------------------------------*/
    Cache *CacheManager::GetCache(Storeable::Concept concept) {
      std::map<Storeable::Concept,Cache*>::iterator it = this->m_cacheIndex.find(concept);
      if(it != this->m_cacheIndex.end()) {
        return it->second;
      }
      return 0x0;
    }

    /* ----------------------------------------------------------------------------------------
     *
     * --------------------------------------------------------------------------------------*/
    graph::type::ByteBuffer* CacheManager::CopyBytesFromPage(Storeable::Concept concept, type::gid id) {
      Cache *c = this->GetCache(concept);
      if(c == 0x0) {
        std::cout << "[CACHEMAN] Error - failed to find cache for concept " << Storeable::ConceptToString(concept) << std::endl;
        return 0x0;
      }
      return c->CopyBytesFromPage(id);
    }

    /* ----------------------------------------------------------------------------------------
     *
     * --------------------------------------------------------------------------------------*/
    bool CacheManager::WriteBytesToPage(Storeable *storeable) {
      Cache *c = this->GetCache(storeable->GetConcept());
      if(c == 0x0) {
        std::cout << "[CACHEMAN] Error - failed to find cache for concept " << storeable->GetConceptString() << std::endl;
        return false;
      }
      return c->WriteBytesToPage(storeable);
    }



  }


}
