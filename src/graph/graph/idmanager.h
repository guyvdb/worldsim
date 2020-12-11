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
      gid NextId();
      virtual void Reclaim(gid id);
      void SetActive(bool value) { this->m_active = value; }
      Store *GetStore() { return m_store; }
      int ReclaimedIdCount() { return this->m_data.size(); }
      long FileOffset() { return this->m_fileoffset; }
      void SetFileOffset(long offset) { this->m_fileoffset = offset; }
      std::uint16_t IdLoadCount() { return this->m_idloadcount; }
      void SetIdLoadCount(std::uint16_t count) { this->m_idloadcount = count; }
      gid Counter() { return this->m_counter; }
      virtual void SetCounter(gid count) { this->m_counter = count; }
      std::vector<gid> &Data() {return this->m_data;}
    private:
      gid m_counter;
      std::mutex m_mutex;
      std::vector<gid> m_data;
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
  // It maintains next id and reclaimed ids

  class IdManager {
    public:
      IdManager(std::filesystem::path datadir);
      ~IdManager();
      bool Open();
      void Close();

      void Reclaim(gid id, Storeable::Concept type);
      //void Reclaim(gid id, Storeable::Concept type);
      bool Register(Store *store, Storeable::Concept type);
      gid NextGraphId(Storeable::Concept type);
      //tid NextTypeId(Storeable::Concept type);
    private:
      void MarkItemState(bool active);
      bool Scan();
      bool Load();
      bool Save();

      ExtendedFile *m_file;
      std::filesystem::path m_datadir;
      std::map<Storeable::Concept, IdCacheItem*> m_cache;
      bool m_isopen;
  };

} // namespace
#endif // IDMANAGER_H
