#include "store.h"
#include <iostream>
#include <cerrno>
#include <buffer.h>

namespace graph {

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  Store::Store(std::string filename, std::size_t pagesize, std::size_t recordsize, Decoder *factory, Storeable::Concept concept) :
    m_filename(filename), m_pagesize(pagesize), m_recordsize(recordsize), m_factory(factory),    
    m_isopen(false), m_lastError(ErrorNone),m_concept(concept), m_file(0x0),m_accumulator(0x0) {
    std::filesystem::path fn(filename);

    std::cout << "[STORE] Create - filename = " << this->m_filename <<
                 ", pagesize = " << this->m_pagesize <<
                 ", recordsize = " << this->m_recordsize <<
                 ", type = " << (int)this->m_concept <<
                 ", factory - " << this->m_factory << std::endl;


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
      std::cout << "[STORE] File " << this->m_filename << " is open" << std::endl;
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
  bool Store::ReadPage(int page, ByteBuffer *buffer) {
    long offset = (long)page * (long)this->m_pagesize;


    // if the file is not big enough


    return this->m_file->Read(offset, buffer->Data(), this->m_pagesize);
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  bool Store::WritePage(int page, ByteBuffer *buffer) {
    long offset = (long)page * (long)this->m_pagesize;
    return this->m_file->Write(offset, buffer->Data(),this->m_pagesize);
  }

  bool Store::Write(long pos, void* ptr, std::size_t size) {
    return this->m_file->Write(pos, ptr, size);
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  /*bool Store::ReadRecord(gid id, Storeable **result) {
    long offset = (long)(id-1) * (long)this->m_recordsize;
    ByteBuffer b = ByteBuffer(this->m_recordsize);

    if(!this->m_file->Read(offset,b.CharData(), this->m_recordsize)) {
      return false;
    }

    *result = this->m_factory->Decode(id, &b);
    return true;

  }*/

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  /*bool Store::WriteRecord(Storeable *rec) {
    long offset = (long)(rec->GetGraphId()-1) * (long)this->m_recordsize;
    return this->m_file->Write(offset, rec->Buffer()->VoidData(), this->m_recordsize);
  }*/

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  bool Store::ScanIds(IdAccumulator *accumulator) {
    // need to walk the whole store searching for reclaimable ids and the max id.
    // set the values onto the accumulator
    long filesize = this->m_file->Size(); // FileSize();
    char buf[1];


    long count = filesize / (long) this->m_recordsize;

    for(long id = 1; id <= count; id++) {
      long offset = (id - 1) *  (long)this->m_recordsize;

      if(!this->m_file->Read(offset,buf,1)) {
        return false;
      }

      if(buf[0] != 0x0) {
        accumulator->Reclaim((type::gid)id);
      }
    }

    accumulator->SetCounter((type::gid)count+1);
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

