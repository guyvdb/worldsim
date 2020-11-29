#ifndef CACHE_PAGE_H
#define CACHE_PAGE_H


#include <graph_types.h>
#include <cstdint>
#include <chrono>

namespace graph {

  class Cache;



  class CachePage {
    public:
      friend Cache;

      CachePage(int no, std::size_t pagesize);
      ~CachePage();
      int No() { return m_no; }
      bool Dirty() { return m_dirty;}
      std::size_t PageSize() { return m_pagesize; }

      // read only version of the data
      const char * Buffer() {return m_data->data();}

      // update the data. this marks the page dirty
      bool Update(const char *data, std::size_t len);

      int Len() {return m_data->size();}

    private:
      bool LoadFromDisk(const char *buffer, size_t len);

      int m_no;
      std::chrono::steady_clock::time_point m_lastAccessed;
      std::vector<char> *m_data;
      std::size_t m_pagesize;
      bool m_dirty;
      void MarkAccessed();
  };
}


#endif // CACHE_PAGE_H
