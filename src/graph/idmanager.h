#ifndef IDMANAGER_H
#define IDMANAGER_H

#include <filesystem>
#include <types.h>
#include <storeable.h>
#include <store.h>
#include <idaccumulator.h>
#include <file.h>
#include <mutex>
#include <vector>
#include <map>
//#include <cstdio>

namespace graph {


  class IdCacheItem : public IdAccumulator{
    public:
      IdCacheItem(Store *store);
      aid NextId();
      virtual void Reclaim(aid id);
      void SetActive(bool value) { this->m_active = value; }
      Store *GetStore() { return m_store; }
      int ReclaimedIdCount() { return this->m_data.size(); }
      long FileOffset() { return this->m_fileoffset; }
      void SetFileOffset(long offset) { this->m_fileoffset = offset; }
      std::uint16_t IdLoadCount() { return this->m_idloadcount; }
      void SetIdLoadCount(std::uint16_t count) { this->m_idloadcount = count; }
      aid Counter() { return this->m_counter; }
      virtual void SetCounter(aid count) { this->m_counter = count; }
      std::vector<aid> &Data() {return this->m_data;}
    private:
      aid m_counter;
      std::mutex m_mutex;
      std::vector<aid> m_data;
      Store *m_store;
      bool m_active;
      long m_fileoffset; // used in storing this is the offset in the file
                         // where the data offset is written
                         //
                         // used in loading this is the actual data offset
      std::uint16_t m_idloadcount;
  };

  // The Id manager manages Graph & Type Id's. It maintains its own
  // file and cache. It loads all of its content into memory on startup.
  // It flushes content back to disk on shutdown. If the data file gets
  // out of sync it can rebuild it from the rest of the data files
  //
  // It maintains next id and reclaimed id for the following:
  //
  //  - Entity
  //  - EntityType
  //  - EntityProperty
  //  - EntityPropertyType
  //  - Relation
  //  - RelationType
  //  - RelationProperty
  //  - RelationPropertyType

  class IdManager {
    public:
      IdManager(std::filesystem::path datadir);
      ~IdManager();
      bool Open();
      void Close();

      void Reclaim(gid id, Storeable::Type type);
      void Reclaim(tid id, Storeable::Type type);
      bool Register(Store *store, Storeable::Type type);
      gid NextGraphId(Storeable::Type type);
      tid NextTypeId(Storeable::Type type);
    private:
      void MarkItemState(bool active);
      bool Scan();
      bool Load();
      bool Save();

      /*
      bool Seek(long pos);
      bool Flush();
      long Tell();

      // Read/Write from current position in file
      bool Write(const char *data, std::size_t size);
      bool Write(std::uint8_t data);
      bool Write(std::uint16_t data);
      bool Write(std::uint32_t data);
      bool Read(char *data, std::size_t size);
      bool Read(std::uint8_t *data);
      bool Read(std::uint16_t *data);
      bool Read(std::uint32_t *data);

      // Read/Write from specific position in file
      bool Write(long pos, const char *data, std::size_t size);
      bool Write(long pos, std::uint8_t data);
      bool Write(long pos, std::uint16_t data);
      bool Write(long pos, std::uint32_t data);
      bool Read(long pos, char *data, std::size_t size);
      bool Read(long pos, std::uint8_t *data);
      bool Read(long pos, std::uint16_t *data);
      bool Read(long pos, std::uint32_t *data);
      */


      //std::FILE *m_fd;
      File *m_file;
      std::filesystem::path m_datadir;
      std::map<Storeable::Type, IdCacheItem*> m_cache;
      bool m_isopen;
  };

} // namespace
#endif // IDMANAGER_H
