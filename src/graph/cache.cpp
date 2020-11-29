#include "cache.h"
#include "cachemanager.h"


namespace graph {



  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  Cache::Cache(CacheManager *manage, Storeable::Concept concept, std::size_t recordsize, std::size_t pagesize) :
    m_cacheManager(manage), m_concept(concept), m_recsize(recordsize), m_pagesize(pagesize) {

  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  bool Cache::Flush() {
    return true;
  }

  /* ----------------------------------------------------------------------------------------
   * Where is the data for this object
   * --------------------------------------------------------------------------------------*/
  ObjectCacheInfo Cache::ObjectInfo(gid id) {
    ObjectCacheInfo info;

    info.FileOffset = ((long)id-1) * (long)this->m_recsize;
    info.FileEndset = info.FileOffset + ((long)this->m_recsize-1);
    info.PageStart = (int)info.FileOffset / (int)this->m_pagesize;
    info.PageEnd = (int)info.FileEndset / (int)this->m_pagesize;
    info.PageOffset = info.FileOffset - (info.PageStart* (long)this->m_pagesize);
    info.Len = (int)this->m_recsize;




    return info;
  }

  /* ----------------------------------------------------------------------------------------
   * On which page does this byte fall
   * --------------------------------------------------------------------------------------*/
  int Cache::BytePageNo(long offset) {
    return ((int) (offset / (long)this->m_pagesize));
  }

}
