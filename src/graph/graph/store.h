#ifndef STORE_H
#define STORE_H

#include <types.h>
#include <filesystem>
#include <cstdint>
#include <string>
#include <page.h>
#include <storeable.h>
#include <idaccumulator.h>
#include <file.h>
#include <encoder.h>
#include <buffer.h>

namespace graph {

  // This is the base class of all data stores
  class Store {
    public:
      Store(std::string filename, std::size_t pagesize, std::size_t recordsize, Encoder *factory, Storeable::Concept concept);
      ~Store();
      bool Open();
      void Close();
      void SetIdAccumulator(IdAccumulator *accumulator) {this->m_accumulator = accumulator;}
      ErrorNo LastError() { return m_lastError; }
      bool IsOpen() { return m_isopen; }
      std::string Filename() { return this->m_filename; }

      bool ReadPage(int page, ByteBuffer *buffer);
      bool WritePage(int page, ByteBuffer *buffer);
      //bool ReadRecord(gid id, Storeable **result);
      //bool WriteRecord(Storeable *rec);

      bool GrowStorage(int pagecount);

      bool ScanIds(IdAccumulator *scanner);
      Storeable::Concept GetConcept() { return  this->m_concept;}
      std::size_t RecordSize() { return this->m_recordsize; }
      std::size_t PageSize() { return this->m_pagesize; }
    private:
      std::string m_filename;
      std::size_t m_pagesize;
      std::size_t m_recordsize;
      Encoder *m_factory;
      bool m_isopen;
      ErrorNo m_lastError;
      Storeable::Concept m_concept;
      File *m_file;
      IdAccumulator *m_accumulator;
  };

}

#endif // STORE_H
