#include "page.h"

namespace graph {

  namespace cache {



    /* ----------------------------------------------------------------------------------------
     *
     * --------------------------------------------------------------------------------------*/
    Page::Page(int no, std::size_t pagesize) : m_pageNo(no),
      m_pagesize(pagesize), m_counter(0), m_locked(false), m_dirty(false)  {
      this->m_buffer = new graph::type::ByteBuffer(this->m_pagesize);
    }

    /* ----------------------------------------------------------------------------------------
     *
     * --------------------------------------------------------------------------------------*/
    Page::~Page() {
      delete this->m_buffer;
    }

    /* ----------------------------------------------------------------------------------------
     *
     * --------------------------------------------------------------------------------------*/
    void Page::Lock() {
      this->m_mutex.lock();
      this->m_locked = true;
    }

    /* ----------------------------------------------------------------------------------------
     *
     * --------------------------------------------------------------------------------------*/
    void Page::Unlock() {
      this->m_locked = false;
      this->m_mutex.unlock();
    }

    void Page::MarkAccessed() {

      //std::chrono::time_point tp = std::chrono::system_clock::now();

      //this->m_lastAccessed = tp;

      //std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    }

  }
}
