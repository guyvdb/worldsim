#ifndef STORE_H
#define STORE_H

#include <filesystem>
#include <cstdint>
//#include <fstream>
#include <cstdio>

#include <gerror.h>
#include <cachepage.h>

namespace graph {




  // This is the base class of all data stores
  class Store {
      // This is a scanner that can scan the data store record by record
      // This is used to rebuild an id store or restore checkpoints.
      class Scanner {
        public:
          Scanner(Store *store);
      };
    public:

      Store(std::filesystem::path filename, std::size_t pagesize, std::size_t recordsize);
      bool Open();
      void Close();
      bool Flush();
      ErrorNo LastError() { return m_lastError; }
      bool IsOpen() { return m_isopen; }

      std::size_t Read(pid page, char *data);
      std::size_t Write(pid page, const char *data);
      std::size_t FileSize();
      std::size_t Capacity();
      std::size_t RecordSize();
    private:

      std::filesystem::path m_filename;
      std::size_t m_pagesize;
      std::size_t m_recordsize;
      bool m_isopen;
      ErrorNo m_lastError;

      std::FILE *m_file;
  };


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

}

#endif // STORE_H
