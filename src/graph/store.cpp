#include "store.h"
#include <iostream>
#include <idmanager.h>

namespace graph {

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  Store::Store(std::filesystem::path filename, std::size_t pagesize, std::size_t recordsize, ObjectFactory *factory) :
    m_filename(filename), m_pagesize(pagesize), m_recordsize(recordsize), m_factory(factory),
    m_isopen(false), m_lastError(ErrorNone), m_file(0x0) {

    std::cout << "[STORE] Creating store - pagesize % recordsize: " << (pagesize % recordsize) << std::endl;
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  Store::~Store() {
    std::cout << "[STORE] Release ObjectFactory" << std::endl;
    delete this->m_factory;
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  bool Store::Open() {
    if (this->m_isopen) {
      this->m_lastError = ErrorFileAlreadyOpen;
      return false;
    }

    this->m_file = new std::fstream();
    std::cout << "[STORE] Will open  - filename = " << this->m_filename.native() << std::endl;
    this->m_file->open(this->m_filename.native(), std::ios::binary | std::ios::in | std::ios::out | std::ios::app);

    if(!this->m_file->is_open()) {
      std::cout << "[STORE] Failed to open " << this->m_filename.native() << std::endl;
      this->m_lastError = ErrorFileFailedToOpen;
      return false;
    }

    std::cout << "[STORE] File is open" << std::endl;

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

      std::cout << "[STORE] Will close " << std::endl;
      this->m_file->close();
      std::cout << "[STORE] File is closed" << std::endl;

      delete this->m_file;

      this->m_file = 0x0;
      this->m_isopen = false;
    }
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  bool Store::Flush() {
    if(this->m_isopen) {
      this->m_file->flush();
      return true;
    }

    this->m_lastError = ErrorFileNotOpen;
    return false;
  }


  /* ----------------------------------------------------------------------------------------
   * The data pointer needs to be m_pagesize size. Read the given page from the file
   * --------------------------------------------------------------------------------------*/
  void Store::ReadPage(pid page, char *data) {
    if(!this->m_isopen){
      this->m_lastError = ErrorFileNotOpen;
      return;
    }

    // Seek to the correct spot in the file
    double offset = (double)page * (double)this->m_pagesize;
    this->m_file->seekg(offset);
    this->m_file->read(data,this->m_pagesize);
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  void Store::WritePage(pid page, const char *data) {
    if(!this->m_isopen){
      this->m_lastError = ErrorFileNotOpen;
      return;
    }

    // Seek to the correct spot in the file
    double offset = (double)page * (double)this->m_pagesize;
    this->m_file->seekg(offset);
    this->m_file->write(data, this->m_pagesize);
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  bool Store::WriteRecord(Storeable *rec) {
    if(!this->m_factory->CanCreateObjects()) {
      return false;
    }

    long offset = (long)rec->GetId() * (long)this->RecordSize();
    this->m_file->seekp(offset);

    long position = this->m_file->tellp();

    //this->m_file->eof();

    std::cout << "[STORE] seek = " << offset << ", tell = " << position << std::endl;

    this->m_file->write(rec->Data(), this->RecordSize());
    // if the store is not big enough... ie. this rec is leaving holes, pad the store

    return true;
  }

  bool Store::ScanIds(IdAccumulator *accumulator) {
    // need to walk the whole store searching for reclaimable ids and the max id.
    // set the values onto the reader

  }
}

