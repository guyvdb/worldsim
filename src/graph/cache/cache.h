#ifndef CACHE_H
#define CACHE_H


#include <cstdint>
#include <chrono>
#include <map>

#include <type/base.h>
#include <page.h>
#include <storeable.h>
#include <store/store.h>
#include <mutex>

namespace graph {

  namespace cache {



    /* The stores read data from disk in pages. The pages are disk block size aligned. The recods
     * are contained on pages. An individual record can be contained on a single page or split across
     * two pages. Pages can be locked for with a read/write lock.
     */


    class CacheManager;


    //  File Start	File End	Bytes	Page Start	Page End	Page Offset	Object Id
    struct CacheOffset {
        long ObjectFileStartOffset;  // the position in the file of the first byte of the object
        long ObjectFileEndOffset;    // the position in the file of the last byte of the object
        int PageStartNo;             // the page number where the first byte of the object is located
        int PageEndNo;               // the page number where the last byte of the object is located
        int ObjectPageStartOffset;   // the position of the first byte of the object in the first page buffer
        long PageStartFileOffset;    // the positon of the first byte of the first page in the file
        long PageEndFileOffset;      // the position of the last byte of the last page in the file
        std::size_t Len;             // the length of the object in bytes
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
        Cache(CacheManager *manage, store::Store *store, std::size_t maxpages); // Storeable::Concept concept, std::size_t recordsize, std::size_t pagesize);


        CacheOffset GetCacheOffset(type::gid id);

        // Return an object from the cache ...
        // the caller needs to free the byte buffer
        ByteBuffer* GetStoreableBuffer(type::gid id);
        bool SetStoreable(Storeable *storeable);


        Page *LockPage(int no);
        void UnlockPage(Page *page);
        bool IsPageCached(int no);

        void Flush();

        store::Store* GetStore() { return this->m_store; }

      protected:
      private:
        void Flush(Page *page);
        int BytePageNo(long offset);
        long PageFileOffset(int no);

        bool GrowStore(long amount);

        void FetchPageFromDisk(int pageno);
        void ReduceCachePageCount();

        CacheManager *m_cacheManager;
        store::Store *m_store;
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
}
#endif // CACHE_H
