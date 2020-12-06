#include "cache.h"
#include "cachemanager.h"


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
  bool Cache::Flush() {
    return true;
  }

  /* ----------------------------------------------------------------------------------------
   * Where is the data for this object
   * --------------------------------------------------------------------------------------*/
  CacheOffset Cache::GetCacheOffset(gid id) {
    CacheOffset info;
    info.FileStart = ((long)id-1) * (long)this->m_recsize;
    info.FileEnd = info.FileStart + ((long)this->m_recsize-1);
    info.PageStart = (int)info.FileStart / (int)this->m_pagesize;
    info.PageEnd = (int)info.FileEnd / (int)this->m_pagesize;
    info.PageOffset = info.FileStart - (info.PageStart* (long)this->m_pagesize);
    info.Len = (int)this->m_recsize;
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
  Page* Cache::LockPage(int no) {
    // is the page in the cache

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
  }

  void Cache::UnlockPage(Page *page) {
    page->Unlock();
  }

  ByteBuffer* Cache::GetStoreableBuffer(gid id) {
    int bytecount = 0;
    CacheOffset offset = this->GetCacheOffset(id);
    ByteBuffer *result = new ByteBuffer(this->m_recsize);
    int pageOffset = offset.PageOffset;

    for(int i = offset.PageStart; i <= offset.PageEnd; i++) {
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
    int pageOffset = offset.PageOffset;
    int bytecount = 0;

    for(int i = offset.PageStart; i <= offset.PageEnd; i++) {
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
