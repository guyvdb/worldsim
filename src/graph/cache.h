#ifndef CACHE_H
#define CACHE_H


#include <cstdint>
#include <chrono>
#include <map>

#include <graph_types.h>
#include <cachepage.h>
#include <storeable.h>


namespace graph {


  /* The stores read data from disk in pages. The pages are disk block size aligned. The recods
   * are contained on pages. An individual record can be contained on a single page or split across
   * two pages. Pages can be locked for with a read/write lock.
   */


  class CacheManager;

  struct ObjectCacheInfo {
      long FileOffset;
      long FileEndset;
      int PageStart;
      int PageEnd;
      int PageOffset;
      std::size_t Len;
  };
  /*
  foff=(id-1)*recsize
  fend=(foff + (recsize-1))
  pstart=rounddown(foff/pagesize))
  pend=rounddown(fend/pagesize))
  poff=(foff-(pstart*pagesize))
      */

  // Need to layout the eviction policy

  /*
   * 2Q - pages are kept in a FIFO queue when loaded. On second access they are
   * moved into a hot queue. Pages are evicted from the first queue.
   * */

  class Cache {
    public:
      Cache(CacheManager *manage, Storeable::Concept concept, std::size_t recordsize, std::size_t pagesize);
      bool Flush();

      ObjectCacheInfo ObjectInfo(gid id);

    protected:
    private:
      int BytePageNo(long offset);

      CacheManager *m_cacheManager;
      Storeable::Concept m_concept;
      std::size_t m_recsize;
      std::size_t m_pagesize;


      std::map<int, CachePage*> m_pages;
  };
}
#endif // CACHE_H
