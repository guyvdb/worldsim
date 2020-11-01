#ifndef STORE_H
#define STORE_H

#include <filesystem>
#include <cstdint>
#include <cstdio>


#include <gerror.h>
#include <cachepage.h>
#include <storeable.h>
#include <idaccumulator.h>

namespace graph {




  // This is the base class of all data stores
  class Store {
    public:
//std::filesystem::path filename
      Store(const char *filename, std::size_t pagesize, std::size_t recordsize, ObjectFactory *factory);
      ~Store();
      bool Open();
      void Close();
      void SetIdAccumulator(IdAccumulator *accumulator) {this->m_accumulator = accumulator;}
      ErrorNo LastError() { return m_lastError; }
      bool IsOpen() { return m_isopen; }

      bool ReadPage(pid page, char *data);
      bool WritePage(pid page, const char *data);
      bool ReadRecord(gid id, Storeable **result);
      bool WriteRecord(Storeable *rec);

      bool GrowStorage(int pagecount);

      bool ScanIds(IdAccumulator *scanner);

    private:
      bool Read(char *data, std::size_t size);
      bool Read(long pos, char *data, std::size_t size);
      bool Write(const char *data, std::size_t size);
      bool Write(long pos, const char *data, std::size_t size);
      bool Seek(long pos);
      bool Flush();
      long Tell();
      long FileSize();


      const char *m_filename;
      std::size_t m_pagesize;
      std::size_t m_recordsize;
      ObjectFactory *m_factory;
      bool m_isopen;
      ErrorNo m_lastError;
      std::FILE *m_fd;
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
