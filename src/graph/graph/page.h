#ifndef CACHE_PAGE_H
#define CACHE_PAGE_H


#include <types.h>
#include <cstdint>
#include <chrono>
#include <buffer.h>
#include <mutex>

namespace graph {

  class Cache;



  class Page {
    public:
      friend Cache;

      Page(int no, std::size_t pagesize);
      ~Page();
      int Number() { return m_pageNo; }
      bool IsDirty() { return m_dirty;}
      void SetDirty(bool value) { this->m_dirty = value; }
      std::size_t PageSize() { return m_pagesize; }
      std::size_t Size() {return this->m_buffer->Size(); }
      ByteBuffer *Buffer() { return this->m_buffer; }
      std::uint8_t operator[](int index) { return this->m_buffer->At(index); }
      bool Locked() { return this->m_locked; }
      void Lock();
      void Unlock();
      void MarkAccessed();

    private:
      //bool LoadFromDisk(const char *buffer, size_t len);

      int m_pageNo;
      //std::chrono::steady_clock::time_point m_lastAccessed;
      //std::vector<char> *m_data;
      ByteBuffer *m_buffer;
      std::size_t m_pagesize;
      std::uint16_t m_counter;

      std::mutex m_mutex;
      bool m_locked;
      bool m_dirty;

  };
}


#endif // CACHE_PAGE_H
