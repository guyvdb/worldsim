#ifndef TRANSACTIONCACHE_H
#define TRANSACTIONCACHE_H

#include <map>
#include <storeable.h>

namespace graph {

  class TransactionCache {
    public:
      TransactionCache(Storeable::Concept concept);
      void Add(Storeable *storeable);
      bool Contains(gid id);
      Storeable* Get(gid id);
      Storeable::Concept GetConcept() { return this->m_concept; }
    private:
      Storeable::Concept m_concept;
      std::map<gid, Storeable*> m_cache;
  };


  class TransactionCacheManager {
    public:
      TransactionCacheManager();
      ~TransactionCacheManager();
      void Add(Storeable *storeable);
      bool Contains(Storeable::Concept concept, gid id);
      Storeable* Get(Storeable::Concept concept, gid id);
    private:
      bool Contains(Storeable::Concept concept);
      std::map<Storeable::Concept, TransactionCache*> m_cache;
  };

}
#endif // TRANSACTIONCACHE_H
