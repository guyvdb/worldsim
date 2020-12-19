#include "config.h"



namespace graph {
  std::size_t Config::GetCacheMaxPages(Storeable::Concept concept) {
    if(this->m_CacheMaxPages.find(concept) == this->m_CacheMaxPages.end()) {
      return Config::DefaultMaxCachePages;
    } else {
      return this->m_CacheMaxPages[concept];
    }
  }

  void Config::SetCacheMaxPages(Storeable::Concept concept, std::size_t max) {
    this->m_CacheMaxPages[concept] = max;
  }
}
