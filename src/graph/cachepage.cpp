#include "cachepage.h"

namespace graph {
  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  CachePage::CachePage(int no, std::size_t pagesize) : m_no(no),
    m_lastAccessed(std::chrono::steady_clock::now()),m_data(0x0), m_pagesize(pagesize), m_dirty(false) {
    // Construct the buffer to hold the page data and set its values to 0x0
    this->m_data = new std::vector<char>(this->m_pagesize,0x0);

  }

  CachePage::~CachePage() {
    // Delete the page buffer
    delete this->m_data;
  }
}
