#ifndef CACHE_H
#define CACHE_H

#include <types.h>
#include <cstdint>
#include <chrono>
#include <map>

#include <store.h>
#include <cachepage.h>
#include <gid.h>

namespace graph {


  /* The stores read data from disk in pages. The pages are disk block size aligned. The recods
   * are contained on pages. An individual record can be contained on a single page or split across
   * two pages. Pages can be locked for with a read/write lock.
   */


  struct StorageInfo {
      int FileOffset;
      int PayloadSize;
      int StartPageNo;
      int StartPageOffset;
  };







  // Need to layout the eviction policy

  /*
   * 2Q - pages are kept in a FIFO queue when loaded. On second access they are
   * moved into a hot queue. Pages are evicted from the first queue.
   * */

  class Cache {
    public:
      Cache(Store *store, std::size_t recsize);


      // need to implement Lock / Unlock of pages


      //bool Get(gid id, std::vector<std::uint8_t> &data);
      //bool Put(gid id, std::vector<std::uint8_t> &data);
      //bool Delete(gid id);

      //StorageInfo GetStorageInfo(gid id);


      Store* GetStore() { return m_store; };

      // flush all dirty pages to disk
      bool Flush();

    protected:



      //PageLocation Location(GraphId id);
    private:
      int StorageFileOffset(gid id);



      Store *m_store;
      std::size_t m_recsize;
      std::map<int, CachePage*> m_pages;
  };



  // The id cache is a specialized cache that loades all of its records into memory
  // and maintains them there.
  class IdCacheItem : public Cache {
    public:
      IdCacheItem(Store *store, std::size_t recsize) : Cache(store, recsize) {}

      GraphId* FindReclaimedId(Storeable::Type type);
      GraphId* LastId(Storeable::Type type);
  };


}
#endif // CACHE_H
