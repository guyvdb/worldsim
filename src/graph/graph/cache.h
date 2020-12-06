#ifndef CACHE_H
#define CACHE_H


#include <cstdint>
#include <chrono>
#include <map>

#include <types.h>
#include <page.h>
#include <storeable.h>
#include <store.h>
#include <mutex>

namespace graph {


  /* The stores read data from disk in pages. The pages are disk block size aligned. The recods
   * are contained on pages. An individual record can be contained on a single page or split across
   * two pages. Pages can be locked for with a read/write lock.
   */


  class CacheManager;


//  File Start	File End	Bytes	Page Start	Page End	Page Offset	Object Id



  struct CacheOffset {
      long FileStart;
      long FileEnd;
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
      Cache(CacheManager *manage, Store *store, std::size_t maxpages); // Storeable::Concept concept, std::size_t recordsize, std::size_t pagesize);
      bool Flush();

      CacheOffset GetCacheOffset(gid id);

      // Return an object from the cache ...
      // the caller needs to free the byte buffer
      ByteBuffer* GetStoreableBuffer(gid id);
      bool SetStoreable(Storeable *storeable);


      Page *LockPage(int no);
      void UnlockPage(Page *page);


    protected:
    private:
      int BytePageNo(long offset);
      long PageFileOffset(int no);

      void FetchPageFromDisk(int pageno);
      void ReduceCachePageCount();

      CacheManager *m_cacheManager;
      Store *m_store;
      Storeable::Concept m_concept;
      std::size_t m_maxPages;
      std::size_t m_recsize;
      std::size_t m_pagesize;

      std::mutex m_mutex;

      std::map<int, Page*> m_pageIndex;
      std::vector<Page*> m_pageQueue;
      std::vector<Page*> m_pageHotQueue;




  };
}
#endif // CACHE_H
