#include "cache.h"
#include "cachemanager.h"
#include <stdlib.h>
#include <cstring>

namespace graph {



  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/

  Cache::Cache(CacheManager *manage, Store *store, std::size_t maxpages) : m_cacheManager(manage), m_store(store), m_maxPages(maxpages) {
    this->m_concept = store->GetConcept();
    this->m_recsize = store->RecordSize();
    this->m_pagesize = store->PageSize();
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  void Cache::Flush() {

    this->m_mutex.lock();
    for(auto page : this->m_pageQueue) {
      if(page->IsDirty()) {
        if(!page->Locked()) {
          page->Lock();
          this->Flush(page);
          page->Unlock();
        }
      }
    }
    this->m_mutex.unlock();
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  void Cache::Flush(Page *page) {
    this->GetStore()->WritePage(page->Number(), page->Buffer());
  }

  /* ----------------------------------------------------------------------------------------
   * Where is the data for this object
   * --------------------------------------------------------------------------------------*/
  CacheOffset Cache::GetCacheOffset(gid id) {
    CacheOffset info;
    info.ObjectFileStartOffset = ((long)id-1) * (long)this->m_recsize;
    info.ObjectFileEndOffset = info.ObjectFileStartOffset + ((long)this->m_recsize-1);
    info.PageStartNo = (int)info.ObjectFileStartOffset / (int)this->m_pagesize;
    info.PageEndNo = (int)info.ObjectFileEndOffset / (int)this->m_pagesize;
    info.ObjectPageStartOffset = info.ObjectFileStartOffset - (info.PageStartNo* (long)this->m_pagesize);
    info.PageStartFileOffset = info.PageStartNo * this->m_pagesize;
    info.PageEndFileOffset = ((info.PageEndNo + 1) * this->m_pagesize) - 1;
    info.Len = (int)this->m_recsize;
/*
    std::cout << "--------------------------------------\n";
    std::cout << "GET CACHE OFFSET: id=" << id;
    std::cout << ", ObjectFileStartOffset=" << info.ObjectFileStartOffset;
    std::cout << ", ObjectFileEndOffset=" << info.ObjectFileEndOffset;
    std::cout << ", PageStartNo=" << info.PageStartNo;
    std::cout << ", PageEndNo=" << info.PageEndNo;
    std::cout << ", ObjectPageStartOffset=" << info.ObjectPageStartOffset;
    std::cout << ", PageStartFileOffset=" << info.PageStartFileOffset;
    std::cout << ", PageEndFileOffset=" << info.PageEndFileOffset;
    std::cout << ", Len=" << info.Len;
    std::cout << std::endl;
    std::cout << "--------------------------------------\n";

*/

    return info;
  }

  /* ----------------------------------------------------------------------------------------
   * On which page does this byte fall
   * --------------------------------------------------------------------------------------*/
  int Cache::BytePageNo(long offset) {
    return ((int) (offset / (long)this->m_pagesize));
  }

  /* ----------------------------------------------------------------------------------------
   * What is the file offset for the start of the page
   * --------------------------------------------------------------------------------------*/
  long Cache::PageFileOffset(int pageno) {
    return (long)((long)pageno * (long)this->m_store->PageSize());
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  bool Cache::IsPageCached(int no) {
    this->m_mutex.lock();
    bool found = !(this->m_pageIndex.find(no) == this->m_pageIndex.end());
    this->m_mutex.unlock();
    return found;
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  Page* Cache::LockPage(int no) {
    Page *page = 0x0;

    // is the page in the cache
    bool exists = this->IsPageCached(no);

    if(!exists) {
      // check if the page actually exists in the store
      long reqsize = ((no+1) * this->m_pagesize);
      long storesize = this->GetStore()->Size();

      this->m_mutex.lock();

      page = new Page(no, this->m_pagesize);

      if(reqsize > storesize) {
        // new page create in file
        if(!this->GrowStore(reqsize - storesize)) {
          std::cout << "[CACHE] Error - failed to grow the store." << std::endl;
          this->m_mutex.unlock();
          return 0x0;
        }
      } else {
        // old page read from file
        if(!this->GetStore()->ReadPage(no, page->Buffer())) {
          std::cout << "[CACHE] Error - failed to read page from file." << std::endl;
          delete page;
          this->m_mutex.unlock();
          return 0x0;
        }
      }


      this->m_pageIndex[no] = page;
      this->m_pageQueue.push_back(page);
      page->MarkAccessed();
      page->Lock();

      this->m_mutex.unlock();
      return page;


    } else {
      // return page from the cache...
      this->m_mutex.lock();
      page = this->m_pageIndex[no];
      this->m_mutex.unlock();
      page->Lock();
      return page;
    }



/*

    // lock the cache mutex
    this->m_mutex.lock();

    if(this->m_pageIndex.find(no) == this->m_pageIndex.end()) {
      // page not found
      std::cout << "[CACHE] Miss - page no=" << no << std::endl;

      // load from store
      Page *page = new Page(no, this->m_store->PageSize());
      if(!this->m_store->ReadPage(no, page->Buffer())) {
        // failed to read data from the store.... Very bad situation...
        std::cout << "[CACHE] Error - failed to read page from file." << std::endl;
        this->m_mutex.unlock();
        return 0x0;
      } else {
        page->Lock();
        this->m_pageIndex[no] = page;
        this->m_pageQueue.push_back(page);
        this->m_mutex.unlock();
        return page;
      }
    } else {
      // page found
      std::cout << "[CACHE] Hit - page no=" << no << std::endl;
      Page *page = this->m_pageIndex[no];
      page->Lock();  // should this be locked inside the cache mutex or not???
      this->m_mutex.unlock();
      return page;
    }
    */
  }

  void Cache::UnlockPage(Page *page) {
    page->Unlock();
  }

  bool Cache::GrowStore(long amount) {
    // We are going to write amount bytes of 0x0 to the end of the store file.
    long pos = this->GetStore()->Size();
    void *ptr = malloc(amount);
    std::memset(ptr,0x0,(std::size_t)amount);
    return this->GetStore()->Write(pos, ptr, (std::size_t)amount);
  }

  ByteBuffer* Cache::GetStoreableBuffer(gid id) {
    int bytecount = 0;
    CacheOffset offset = this->GetCacheOffset(id);
    ByteBuffer *result = new ByteBuffer(this->m_recsize);
    int pageOffset = offset.ObjectPageStartOffset;

    for(int i = offset.PageStartNo; i <= offset.PageEndNo; i++) {
      Page *page = this->LockPage(i);
      if(page != 0x0) {
        for(int pagePtr = pageOffset; pagePtr < (int)this->m_pagesize; pagePtr++) {
          result->Set(bytecount, page->Buffer()->At(pagePtr));
          bytecount++;
          if(bytecount == (int)this->m_recsize) {
            break;
          }
        }
        page->MarkAccessed();
        page->Unlock();
      } else {
        // major problem could not get the page
        std::cout << "[CACHE] Error - failed to lock page." << std::endl;
        delete result;
        return 0x0;
      }
      // second page and on will be page offset 0
      pageOffset = 0;
    }
    return result;
  }

  // set the bytes back into the cache and mark page(s) dirty
  bool Cache::SetStoreable(Storeable *storeable) {
    // is this storeable the right concept ???
    if(this->m_concept != storeable->GetConcept()) {
      std::cout << "[CACHE] Error - trying to set incorrect concept to cache." << std::endl;
      return false;
    }


    CacheOffset offset = this->GetCacheOffset(storeable->GetGraphId());
    int pageOffset = offset.ObjectPageStartOffset;
    int bytecount = 0;

    for(int i = offset.PageStartNo; i <= offset.PageEndNo; i++) {
      Page *page = this->LockPage(i);
      if(page != 0x0) {
        for(int pagePtr = pageOffset; (int)this->m_pagesize; pagePtr++) {
          page->Buffer()->Set(pagePtr, storeable->Buffer()->At(bytecount));
          bytecount++;
          if(bytecount == (int)this->m_recsize) {
            // we are done
            break;
          }
          // getting bytes of the page
        }
        page->SetDirty(true);
        page->MarkAccessed();
        page->Unlock();
      } else {
        std::cout << "[CACHE] Error -failed to lock page." << std::endl;
        return false;
      }
      pageOffset = 0;
    }
  }



}
