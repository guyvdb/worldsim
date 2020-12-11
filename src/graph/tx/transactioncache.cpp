#include "transactioncache.h"


namespace graph {

  namespace tx {


    /* ----------------------------------------------------------------------------------------
     *
     * --------------------------------------------------------------------------------------*/
    TransactionCache::TransactionCache(Storeable::Concept concept) : m_concept(concept) {

    }

    /* ----------------------------------------------------------------------------------------
     *
     * --------------------------------------------------------------------------------------*/
    void TransactionCache::Add(Storeable *storeable){
      this->m_cache[storeable->GetGraphId()] = storeable;
    }

    /* ----------------------------------------------------------------------------------------
     *
     * --------------------------------------------------------------------------------------*/
    bool TransactionCache::Contains(type::gid id) {
      return this->m_cache.find(id) != this->m_cache.end();
    }

    /* ----------------------------------------------------------------------------------------
     *
     * --------------------------------------------------------------------------------------*/
    Storeable* TransactionCache::Get(type::gid id) {
      if(this->Contains(id)) {
        return this->m_cache[id];
      } else {
        return 0x0;
      }
    }

    /* ----------------------------------------------------------------------------------------
     *
     * --------------------------------------------------------------------------------------*/
    TransactionCacheManager::TransactionCacheManager() {

    }

    /* ----------------------------------------------------------------------------------------
     *
     * --------------------------------------------------------------------------------------*/
    TransactionCacheManager::~TransactionCacheManager() {
      // delete all the TransactionCache * ptrs
      for (auto const& c : this->m_cache) {
        for(auto const &item : *c.second->GetCache()) {
          delete item.second;
        }
        delete c.second;
      }
    }

    /* ----------------------------------------------------------------------------------------
     *
     * --------------------------------------------------------------------------------------*/
    void TransactionCacheManager::Add(Storeable *storeable) {
      TransactionCache *c;

      if(!this->Contains(storeable->GetConcept())) {
        c = new TransactionCache(storeable->GetConcept());
        this->m_cache[storeable->GetConcept()] = c;
      } else {
        c = this->m_cache[storeable->GetConcept()];
      }
      c->Add(storeable);
    }

    /* ----------------------------------------------------------------------------------------
     *
     * --------------------------------------------------------------------------------------*/
    bool TransactionCacheManager::Contains(Storeable::Concept concept, type::gid id) {
      if(this->Contains(concept)) {
        return this->m_cache[concept]->Contains(id);
      } else {
        return false;
      }
    }

    /* ----------------------------------------------------------------------------------------
     *
     * --------------------------------------------------------------------------------------*/
    bool TransactionCacheManager::Contains(Storeable::Concept concept) {
      return this->m_cache.find(concept) != this->m_cache.end();
    }

    /* ----------------------------------------------------------------------------------------
     *
     * --------------------------------------------------------------------------------------*/
    Storeable* TransactionCacheManager::Get(Storeable::Concept concept, type::gid id) {
      if(this->Contains(concept, id)) {
        return this->m_cache[concept]->Get(id);
      } else {
        return 0x0;
      }
    }

    /* ----------------------------------------------------------------------------------------
     *
     * --------------------------------------------------------------------------------------*/
    std::size_t TransactionCacheManager::Size() {
      std::size_t count = 0;
      for(auto const &item : this->m_cache) {
        count += item.second->Size();
      }
      return count;
    }

    /* ----------------------------------------------------------------------------------------
     *
     * --------------------------------------------------------------------------------------*/
    std::vector<Storeable*> TransactionCacheManager::GetModifiedObjects() {
      std::vector<Storeable*> v;
      v.reserve(this->Size());
      for(auto const &c : this->m_cache) {
        for(auto const &item : *c.second->GetCache()) {
          if(item.second->IsDirty()) {
            v.push_back(item.second);
          }
        }
      }
      return v;
    }



  }
}
