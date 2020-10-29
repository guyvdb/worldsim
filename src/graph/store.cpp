#include "store.h"
#include <iostream>

namespace graph {

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  Store::Store(std::filesystem::path filename, std::size_t pagesize, std::size_t recordsize) :
    m_filename(filename), m_pagesize(pagesize), m_recordsize(recordsize), m_isopen(false), m_lastError(ErrorNone), m_file(0x0) {

  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  bool Store::Open() {
    if (this->m_isopen) {
      this->m_lastError = ErrorFileAlreadyOpen;
      return false;
    }



    std::cout << "[STORE] Will open  - filename = " << this->m_filename.native() << std::endl;


    this->m_file = std::fopen(this->m_filename.c_str(), "rwab");
    if (this->m_file == 0x0) {
      this->m_lastError = ErrorFileFailedToOpen;
      return false;
    }

    std::cout << "[STORE] File opened - file = " << this->m_file << std::endl;

    this->m_isopen = true;
    return true;
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  void Store::Close() {
    if(this->m_isopen) {
      std::cout << "[STORE] Will flush" << std::endl;
      this->Flush();
      std::cout << "[STORE] Flushed" << std::endl;

      std::cout << "[STORE] Will close file: file=" << this->m_file << std::endl;

      std::fclose(this->m_file);
      std::cout << "[STORE] Closed" << std::endl;

      this->m_file = 0x0;
      this->m_isopen = false;
    }
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  bool Store::Flush() {
    if(this->m_isopen) {
      std::fflush(this->m_file);
      return true;
    }

    this->m_lastError = ErrorFileNotOpen;
    return false;
  }


  /* ----------------------------------------------------------------------------------------
   * The data pointer needs to be m_pagesize size. Read the given page from the file
   * --------------------------------------------------------------------------------------*/
  std::size_t Store::Read(pid page, char *data) {
    if(!this->m_isopen){
      this->m_lastError = ErrorFileNotOpen;
      return -1;
    }

    // Seek to the correct spot in the file
    double offset = (double)page * (double)this->m_pagesize;
    if (fseek(this->m_file, offset, SEEK_SET) != 0) {
      this->m_lastError = ErrorFileSeekError;
      return -1;
    }

    void *ptr = (void*)data;
    return std::fread(ptr,1,this->m_pagesize,this->m_file);
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  std::size_t Store::Write(pid page, const char *data) {
    if(!this->m_isopen){
      this->m_lastError = ErrorFileNotOpen;
      return -1;
    }

    // Seek to the correct spot in the file
    double offset = (double)page * (double)this->m_pagesize;
    if (fseek(this->m_file, offset, SEEK_SET) != 0) {
      this->m_lastError = ErrorFileSeekError;
      return -1;
    }

    void *ptr = (void*)data;
    return std::fwrite(ptr,1,this->m_pagesize,this->m_file);

  }
}

