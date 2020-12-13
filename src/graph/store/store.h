#ifndef STORE_H
#define STORE_H

#include <type/base.h>
#include <filesystem>
#include <cstdint>
#include <string>
#include <cache/page.h>
#include <storeable.h>
#include <id/idmanager.h>
#include <store/file.h>
#include <store/scanner.h>
//#include <decoder.h>
#include <buffer.h>
#include <grapherrors.h>


namespace graph {
  namespace store {
    // This is the base class of all data stores
    class Store {
      public:
        Store(std::string filename, std::size_t pagesize, std::size_t recordsize, Storeable::Concept concept);
        ~Store();
        bool Open();
        void Close();
        ErrorNo LastError() { return m_lastError; }
        bool IsOpen() { return m_isopen; }
        std::string Filename() { return this->m_filename; }
        long Size() { return this->m_file->Size(); }
        bool ReadPage(int page, ByteBuffer *buffer);
        bool WritePage(int page, ByteBuffer *buffer);
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
        ErrorNo m_lastError;
        Storeable::Concept m_concept;
        BlockFile *m_file;
    };
  }
}

#endif // STORE_H