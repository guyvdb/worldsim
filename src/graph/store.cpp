#include "store.h"
#include <iostream>
#include <cerrno>


namespace graph {

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  Store::Store(const char *filename/*std::filesystem::path filename*/, std::size_t pagesize, std::size_t recordsize, ObjectFactory *factory) :
    m_filename(filename), m_pagesize(pagesize), m_recordsize(recordsize), m_factory(factory),
    m_isopen(false), m_lastError(ErrorNone), m_file(0x0),m_accumulator(0x0) {
    std::filesystem::path fn(filename);

    this->m_file = new File(fn);

  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  Store::~Store() {
    delete this->m_file;
    delete this->m_factory;
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  bool Store::Open() {

    std::cout << "[STORE] Open filename: " << this->m_filename << std::endl;

    // open the file
    if(this->m_file->Open()) {
      this->m_isopen = true;
      return true;
    }
    return false;
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  void Store::Close() {
    if(this->m_isopen) {
      this->m_file->Close();
      this->m_isopen = false;
    }
  }

  /* ----------------------------------------------------------------------------------------
   * This can only be called once an accumulator is set
   * --------------------------------------------------------------------------------------*/
  bool Store::GrowStorage(int pagecount) {
    if(!this->m_isopen || this->m_accumulator == 0x0) {
      return false;
    }



  }


  /* ----------------------------------------------------------------------------------------
   * The data pointer needs to be m_pagesize size. Read the given page from the file
   * --------------------------------------------------------------------------------------*/
  bool Store::ReadPage(pid page, char *data) {
    long offset = (long)page * (long)this->m_pagesize;
    return this->m_file->Read(offset, data, this->m_pagesize);
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  bool Store::WritePage(pid page, const char *data) {
    long offset = (long)page * (long)this->m_pagesize;
    return this->m_file->Write(offset, data,this->m_pagesize);
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  bool Store::ReadRecord(gid id, Storeable **result) {
    long offset = (long)(id-1) * (long)this->m_recordsize;
    std::vector<char> buffer(this->m_recordsize);
    if(!this->m_file->Read(offset,buffer.data(), this->m_recordsize)) {
      return false;
    }

    *result = this->m_factory->CreateObject(id, buffer.data());
    return true;

  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  bool Store::WriteRecord(Storeable *rec) {
    long offset = (long)(rec->GetId()-1) * (long)this->m_recordsize;
    return this->m_file->Write(offset, rec->Data(), this->m_recordsize);
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  bool Store::ScanIds(IdAccumulator *accumulator) {
    // need to walk the whole store searching for reclaimable ids and the max id.
    // set the values onto the accumulator
    long filesize = this->m_file->Size(); // FileSize();
    char buf[1];

    //if(filesize % (long)this->m_recordsize != 0) {
      // we have a problem....
    //}
    long count = filesize / (long) this->m_recordsize;

    for(long id = 1; id <= count; id++) {
      long offset = (id - 1) *  (long)this->m_recordsize;

      if(!this->m_file->Read(offset,buf,1)) {
        return false;
      }

      if(buf[0] != 0x0) {
        accumulator->Reclaim((aid)id);
      }
    }

    accumulator->SetCounter((aid)count+1);

    std::cout << "[STORE] Id scan complete." << std::endl;

    return true;
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
//  bool Store::Read(char *data, std::size_t size) {
//    std::size_t read = std::fread((void*)data,1,size,this->m_fd);
//    return read == size;
//  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
//  bool Store::Read(long pos, char *data, std::size_t size) {
//    if(!this->Seek(pos)) {
//      return false;
//    }
//    return this->Read(data,size);
//  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
//  bool Store::Write(const char *data, std::size_t size) {
//    std::size_t written = std::fwrite((void*)data,1,size,this->m_fd);
//    return written == size;
//  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
//  bool Store::Write(long pos, const char *data, std::size_t size) {
//    if(!this->Seek(pos)) {
//      return false;
//    }
//    return this->Write(data,size);
//  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
//  bool Store::Seek(long pos) {
//    return std::fseek(this->m_fd,pos,SEEK_SET) == 0;
//  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
//  bool Store::Flush() {
//    return std::fflush(this->m_fd) == 0;
//  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
//  long Store::Tell() {
//    return std::ftell(this->m_fd);
//  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
//  long Store::FileSize() {
//    // keep point to return to
//    long pos = this->Tell();

//    // seek to eof
//    std::fseek(this->m_fd,0,SEEK_END);

//    // tell position
//    long result = this->Tell();

//    // seek back to where we where
//    this->Seek(pos);

//    return result;
//  }

}

