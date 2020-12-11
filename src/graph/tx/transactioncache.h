#ifndef TRANSACTIONCACHE_H
#define TRANSACTIONCACHE_H

#include <map>
#include <storeable.h>

namespace graph {
  namespace tx {
    class TransactionCache {
      public:
        TransactionCache(Storeable::Concept concept);
        void Add(Storeable *storeable);
        bool Contains(type::gid id);
        Storeable* Get(type::gid id);
        Storeable::Concept GetConcept() { return this->m_concept; }
        std::size_t Size() { return this->m_cache.size(); }
        std::map<type::gid, Storeable*>* GetCache() { return &this->m_cache; }
      private:
        Storeable::Concept m_concept;
        std::map<type::gid, Storeable*> m_cache;
    };

    class TransactionCacheManager {
      public:
        TransactionCacheManager();
        ~TransactionCacheManager();
        void Add(Storeable *storeable);
        bool Contains(Storeable::Concept concept, type::gid id);
        Storeable* Get(Storeable::Concept concept, type::gid id);
        std::vector<Storeable*> GetModifiedObjects();
        std::size_t Size();
      private:
        bool Contains(Storeable::Concept concept);
        std::map<Storeable::Concept, TransactionCache*> m_cache;
    };
  }
}
#endif // TRANSACTIONCACHE_H
