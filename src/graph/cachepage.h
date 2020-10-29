#ifndef CACHE_PAGE_H
#define CACHE_PAGE_H


#include <types.h>
#include <cstdint>
#include <chrono>

namespace graph {
  class CachePage {
    public:
      CachePage(int no, std::size_t pagesize);
      ~CachePage();
      int No() { return m_no; }
      bool Dirty() { return m_dirty;}
      std::size_t PageSize() { return m_pagesize; }
      char * Buffer() {return m_data->data();}
      int Len() {return m_data->size();}
    private:
      int m_no;
      std::chrono::steady_clock::time_point m_lastAccessed;
      std::vector<char> *m_data;
      std::size_t m_pagesize;
      bool m_dirty;
      void MarkAccessed();
  };
}


#endif // CACHE_PAGE_H
