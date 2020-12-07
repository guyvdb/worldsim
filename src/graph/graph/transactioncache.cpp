#include "transactioncache.h"


namespace graph {

  TransactionCache::TransactionCache(Storeable::Concept concept) : m_concept(concept) {

  }

  void TransactionCache::Add(Storeable *storeable){
    this->m_cache[storeable->GetGraphId()] = storeable;
  }

  bool TransactionCache::Contains(gid id) {
    return this->m_cache.find(id) != this->m_cache.end();
  }

  Storeable* TransactionCache::Get(gid id) {
    if(this->Contains(id)) {
      return this->m_cache[id];
    } else {
      return 0x0;
    }
  }

  TransactionCacheManager::TransactionCacheManager() {

  }

  TransactionCacheManager::~TransactionCacheManager() {
    // delete all the TransactionCache * ptrs
    for (auto const& c : this->m_cache) {
      for(auto const &item : *c.second->GetCache()) {
        delete item.second;
      }
      delete c.second;
    }
  }

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

  bool TransactionCacheManager::Contains(Storeable::Concept concept, gid id) {
    if(this->Contains(concept)) {
      return this->m_cache[concept]->Contains(id);
    } else {
      return false;
    }
  }

  bool TransactionCacheManager::Contains(Storeable::Concept concept) {
    return this->m_cache.find(concept) != this->m_cache.end();
  }

  Storeable* TransactionCacheManager::Get(Storeable::Concept concept, gid id) {
    if(this->Contains(concept, id)) {
      return this->m_cache[concept]->Get(id);
    } else {
      return 0x0;
    }
  }

  std::size_t TransactionCacheManager::Size() {
    std::size_t count = 0;
    for(auto const &item : this->m_cache) {
      count += item.second->Size();
    }
    return count;
  }

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



  /*
    std::vector<Storeable*> v;
    v.reserve(this->m_allocatedObjects.size());

    for(auto obj : this->m_allocatedObjects) {
      if(obj->IsDirty()) {
        v.push_back(obj);
      }
    }
    */

}


/*

  c++ 11
for (auto const& x : symbolTable)
{
    std::cout << x.first  // string (key)
              << ':'
              << x.second // string's value
              << std::endl ;
}



c++ 17
for( auto const& [key, val] : symbolTable )
{
    std::cout << key         // string (key)
              << ':'
              << val        // string's value
              << std::endl ;
}
*/
