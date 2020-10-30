#ifndef STORE_H
#define STORE_H

#include <filesystem>
#include <cstdint>
#include <fstream>


#include <gerror.h>
#include <cachepage.h>
#include <storeable.h>

namespace graph {

  class IdAccumulator;


  // This is the base class of all data stores
  class Store {
    public:

      Store(std::filesystem::path filename, std::size_t pagesize, std::size_t recordsize, ObjectFactory *factory);
      ~Store();
      bool Open();
      void Close();
      bool Flush();
      ErrorNo LastError() { return m_lastError; }
      bool IsOpen() { return m_isopen; }

      void ReadPage(pid page, char *data);
      void WritePage(pid page, const char *data);
      Storeable *ReadRecord(gid id);
      bool WriteRecord(Storeable *rec);

      bool GrowStorage(int pagecount);
      std::size_t FileSize();
      std::size_t Capacity();
      std::size_t RecordSize() { return this->m_recordsize; }

      bool ScanIds(IdAccumulator *scanner);

    private:

      std::filesystem::path m_filename;
      std::size_t m_pagesize;
      std::size_t m_recordsize;
      ObjectFactory *m_factory;
      bool m_isopen;
      ErrorNo m_lastError;
      std::fstream *m_file;

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
