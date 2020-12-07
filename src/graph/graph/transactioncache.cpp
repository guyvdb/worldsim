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
    for (auto const& item : this->m_cache) {
      delete item.second;
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
