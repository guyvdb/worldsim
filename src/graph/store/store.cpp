#include "store.h"
#include <iostream>
#include <cerrno>
#include <buffer.h>

namespace graph {
  namespace store {



    /* ----------------------------------------------------------------------------------------
     *
     * --------------------------------------------------------------------------------------*/
    Store::Store(std::string filename, std::size_t pagesize, std::size_t recordsize, Storeable::Concept concept) :
      m_filename(filename), m_pagesize(pagesize), m_recordsize(recordsize),
      m_isopen(false), m_lastError(ErrorNone),m_concept(concept), m_file(0x0)/*,m_accumulator(0x0)*/ {
      std::filesystem::path fn(filename);

      std::cout << "[STORE] Create - filename = " << this->m_filename <<
                   ", pagesize = " << this->m_pagesize <<
                   ", recordsize = " << this->m_recordsize <<
                   ", type = " << (int)this->m_concept << std::endl;


      this->m_file = new BlockFile(fn);

    }

    /* ----------------------------------------------------------------------------------------
     *
     * --------------------------------------------------------------------------------------*/
    Store::~Store() {
      delete this->m_file;
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
//    bool Store::GrowStorage(int pagecount) {
//      if(!this->m_isopen || this->m_accumulator == 0x0) {
//        return false;
//      }



//    }


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

    /* ----------------------------------------------------------------------------------------
     *
     * --------------------------------------------------------------------------------------*/
    bool Store::Write(long pos, void* ptr, std::size_t size) {
      return this->m_file->Write(pos, ptr, size);
    }

    /* ----------------------------------------------------------------------------------------
     * Scan every record in the store
     * --------------------------------------------------------------------------------------*/
    bool Store::Scan(Scanner *scanner) {
      long filesize = this->m_file->Size();
      long count = filesize / (long) this->m_recordsize;
      //std::vector<std::uint8_t> buffer(this->m_recordsize, 0x0);

      ByteBuffer buffer(this->m_recordsize);

      for(long id = 1; id <= count; id++) {
        long offset = (id-1) * (long)this->m_recordsize;
        if(!this->m_file->Read(offset, buffer.Data(),this->m_recordsize)) {
          return false;
        }
        bool active = buffer.At(0) == 0x1;

        scanner->Scan((type::gid)id, active, &buffer, this->m_recordsize);
      }
      return true;
    }

    /* ----------------------------------------------------------------------------------------
     * TODO design a scanner interface that can be used for Id scanning and other scanning
     * purposes.
     * --------------------------------------------------------------------------------------*/
    bool Store::ScanIds(id::IdAccumulator *accumulator) {
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

  }
}

