#ifndef STORE_H
#define STORE_H

#include <filesystem>
#include <cstdint>
#include <string>

#include "file.h"
#include "scanner.h"
#include "../type/base.h"
#include "../cache/page.h"
#include "../storeable.h"
#include "../id/idmanager.h"
#include "../type/buffer.h"
#include "../type/errors.h"


namespace graph {
  namespace store {
    // This is the base class of all data stores
    class Store {
      public:
        Store(std::string filename, std::size_t pagesize, std::size_t recordsize, Storeable::Concept concept);
        ~Store();
        bool Open();
        void Close();
        graph::type::ErrorNo LastError() { return m_lastError; }
        bool IsOpen() { return m_isopen; }
        std::string Filename() { return this->m_filename; }
        long Size() { return this->m_file->Size(); }
        bool ReadPage(int page, graph::type::ByteBuffer *buffer);
        bool WritePage(int page, graph::type::ByteBuffer *buffer);
        bool Write(long pos, void *ptr, std::size_t size);
        bool Scan(Scanner *scanner);
        bool ScanIds(id::IdAccumulator *scanner);
        Storeable::Concept GetConcept() { return  this->m_concept;}
        std::size_t RecordSize() { return this->m_recordsize; }
        std::size_t PageSize() { return this->m_pagesize; }
      private:
        std::string m_filename;
        std::size_t m_pagesize;
        std::size_t m_recordsize;
        bool m_isopen;
        graph::type::ErrorNo m_lastError;
        Storeable::Concept m_concept;
        BlockFile *m_file;
    };
  }
}

#endif // STORE_H
