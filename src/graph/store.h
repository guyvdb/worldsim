#ifndef STORE_H
#define STORE_H

#include <types.h>
#include <filesystem>
#include <cstdint>
#include <string>
#include <cachepage.h>
#include <storeable.h>
#include <idaccumulator.h>
#include <file.h>
#include <encoder.h>

namespace graph {




  // This is the base class of all data stores
  class Store {
    public:
//std::filesystem::path filename
      Store(std::string filename, std::size_t pagesize, std::size_t recordsize, Encoder *factory, Storeable::Concept concept);
      ~Store();
      bool Open();
      void Close();
      void SetIdAccumulator(IdAccumulator *accumulator) {this->m_accumulator = accumulator;}
      ErrorNo LastError() { return m_lastError; }
      bool IsOpen() { return m_isopen; }
      std::string Filename() { return this->m_filename; }

      bool ReadPage(pid page, char *data);
      bool WritePage(pid page, const char *data);
      bool ReadRecord(gid id, Storeable **result);
      bool WriteRecord(Storeable *rec);

      bool GrowStorage(int pagecount);

      bool ScanIds(IdAccumulator *scanner);
      Storeable::Concept Type() { return  this->m_concept;}
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


      //std::FILE *m_file;
  };

/*
  class IdStore : public Store {
    public:
      IdStore(std::filesystem::path filename, std::size_t pagesize, std::size_t recordsize) :
        Store(filename, pagesize, recordsize) {}
      

  };

  class ThingStore : public Store {
    public:
      ThingStore(std::filesystem::path filename, std::size_t pagesize, std::size_t recordsize) :
        Store(filename, pagesize, recordsize) {}
  };

  class ThingTypeStore : public Store {
    public:
      ThingTypeStore(std::filesystem::path filename, std::size_t pagesize, std::size_t recordsize) :
        Store(filename, pagesize, recordsize) {}
  };

  class RelationStore : public Store {
    public:
      RelationStore(std::filesystem::path filename, std::size_t pagesize, std::size_t recordsize) :
        Store(filename, pagesize, recordsize) {}
  };

  class RelationTypeStore : public Store {
    public:
      RelationTypeStore(std::filesystem::path filename, std::size_t pagesize, std::size_t recordsize) :
        Store(filename, pagesize, recordsize) {}
  };

  class PropertyStore : public Store {
    public:
      PropertyStore(std::filesystem::path filename, std::size_t pagesize, std::size_t recordsize) :
        Store(filename, pagesize, recordsize) {}
  };

  class PropertyTypeStore : public Store {
    public:
      PropertyTypeStore(std::filesystem::path filename, std::size_t pagesize, std::size_t recordsize) :
        Store(filename, pagesize, recordsize) {}
  };
*/
}

#endif // STORE_H
