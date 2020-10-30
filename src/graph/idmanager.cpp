#include "idmanager.h"
#include <gid.h>
#include <iostream>
#include <string>
const std::string filename("id.db");
const char ValidFileMarker[2] = {0xA,0xB};
const char InvalidFileMarker[2] = {0x0,0x0};

namespace graph {


  IdCacheItem::IdCacheItem(Store *store) : IdAccumulator(), m_store(store),m_active(false){

  }

  /* ----------------------------------------------------------------------------------------
   * Take the next id out of the data vector if there is one. Otherwise
   * return the counter and increment it. Do all of this within a mutex lock
   * --------------------------------------------------------------------------------------*/
  aid IdCacheItem::NextId() {
    if(!this->m_active) {
      std::cout << "[ID MANAGER] Error - trying to get id while cache item is inactive." << std::endl;
      return (aid)NullId;
    }


    aid result;

    // Lock the mutex - will be released at end of scope
    std::lock_guard<std::mutex> guard(this->m_mutex);

    // Use a reclaimed Id
    if(this->m_data.size() > 0) {
      result = this->m_data.back();
      this->m_data.pop_back();
      return result;
    }

    // Create a new id
    result = this->m_counter;
    this->m_counter++;
    return result;
  }

  /* ----------------------------------------------------------------------------------------
   * Put the id in the reclaimed data vector within a locked mutex
   * --------------------------------------------------------------------------------------*/
  void IdCacheItem::Reclaim(aid id) {
    if(!this->m_active) {
      std::cout << "[ID MANAGER] Error - trying to reclaim id while cache item is inactive." << std::endl;
      return;
    }
    std::lock_guard<std::mutex> gaurd(this->m_mutex);
    this->m_data.push_back(id);
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  IdManager::IdManager(std::filesystem::path datadir) : m_fd(0x0), m_datadir(datadir),  m_isopen(false) {

  }

  /* ----------------------------------------------------------------------------------------
   * Free all resource created during store registration, if any
   * --------------------------------------------------------------------------------------*/
  IdManager::~IdManager() {
    // iterate the cache and delete all items
    for(const auto &pair : this->m_cache) {
      delete pair.second;
    }

    // clear the cache
    this->m_cache.clear();
  }

  /* ----------------------------------------------------------------------------------------
   * The caller should have called Register() on all datastores before opening the IdManager.
   * The Id manager will reconstruct its cache from disk file. If the file does not exist or
   * is damaged, the manager will recreate the file by scanning all data stores and recording
   * all reclaimed ids and the highest issued id.
   * --------------------------------------------------------------------------------------*/
  bool IdManager::Open(){
    std::filesystem::path fn(this->m_datadir);
    fn /= filename;

    // open the file
    this->m_fd = std::fopen(fn.c_str(), "rwab");
    if(this->m_fd == 0x0){
      std::cout << "[ID MANAGER] Error - failed to open " << fn.native() << std::endl;
      return false;
    }

    // load the file
    if(this->Load()) {
      this->MarkItemState(true);
      this->m_isopen = true;
      return true;
    }

    // if load fail scan the data stores
    std::cout << "[ID MANAGER] Failed to load file - starting scan." << std::endl;
    if(this->Scan()) {
      this->MarkItemState(true);
      this->m_isopen = true;
      return true;
    }

    // This is very bad we should not get here.
    std::cout << "[ID MANAGER] Error - failed to open." << std::endl;
    std::fclose(this->m_fd);
    this->m_fd = 0x0;
    return false;
  }

  /* ----------------------------------------------------------------------------------------
   * On close the cache state is written back to the data file.
   * --------------------------------------------------------------------------------------*/
  void IdManager::Close(){

    this->m_isopen = false;
    this->MarkItemState(false);

    // store the state    
    if(!this->Save()) {
      std::cout << "[ID MANAGER] Error - failed to store cache state." << std::endl;
    }

    // close the file
    if(this->m_fd != 0x0) {
      std::fflush(this->m_fd);
      std::fclose(this->m_fd);
      this->m_fd = 0x0;
    }
  }

  /* ----------------------------------------------------------------------------------------
   * Mark this id as reclaimed for the given type
   * --------------------------------------------------------------------------------------*/
  void IdManager::Reclaim(gid id, Storeable::Type type){
    if(!this->m_isopen) {
      std::cout << "[ID MANAGER] Error - trying to reclaim an id while closed." << std::endl;
      return;
    }
    IdCacheItem *item = this->m_cache[type];
    if(item == 0x0) {
      std::cout << "[ID MANAGER] Error - trying to reclaim an id with an unregisterd type." << std::endl;
      return;
    }

    // The item will lock a mutex on reclaim
    item->Reclaim((aid)id);
  }

  /* ----------------------------------------------------------------------------------------
   * Mark this id as reclaimed for the given type
   * --------------------------------------------------------------------------------------*/
  void IdManager::Reclaim(tid id, Storeable::Type type){
    this->Reclaim((gid)id, type);
  }

  /* ----------------------------------------------------------------------------------------
   * Register a data store for a given type with the manager. This function should be called
   * an appropriate number of times prior to the store being opened. Once the store is open
   * no more stores can be registerd. The register method is not thread safe.
   * --------------------------------------------------------------------------------------*/
  bool IdManager::Register(Store *store, Storeable::Type type){
    if(this->m_isopen) {
      std::cout << "[ID MANAGER] Error - trying to register a store after the manager has been opened." << std::endl;
      return false;
    }

    IdCacheItem *item = this->m_cache[type];
    if(item != 0x0) {
      std::cout << "[ID MANAGER] Error - trying to register alread registerd store." << std::endl;
      return false;
    }

    item = new IdCacheItem(store);
    this->m_cache[type] = item;

    return true;
  }

  /* ----------------------------------------------------------------------------------------
   * Get the next gid for the given type (reclaimed or new)
   * --------------------------------------------------------------------------------------*/
  gid IdManager::NextGraphId(Storeable::Type type){
    if (!this->m_isopen) {
      std::cout << "[ID MANAGER] Error - trying to get an id while closed." << std::endl;
      return  NullId;
    }

    IdCacheItem *item = this->m_cache[type];
    if(item == 0x0) {
      std::cout << "[ID MANAGER] Error - trying to get an id from a nonregistered type."<< std::endl;
      return NullId;
    }

    // this will lock a mutex
    return (gid)item->NextId();
  }

  /* ----------------------------------------------------------------------------------------
   * Get the next tid for the given type (reclaimed or new)
   * --------------------------------------------------------------------------------------*/
  tid IdManager::NextTypeId(Storeable::Type type){
    return (tid)this->NextGraphId(type);
  }

  /* ----------------------------------------------------------------------------------------
   * If the item state is inactive it will not provide ids
   * --------------------------------------------------------------------------------------*/
  void IdManager::MarkItemState(bool active) {
    for(const auto &pair : this->m_cache) {
      pair.second->SetActive(active);
    }
  }

  /* ----------------------------------------------------------------------------------------
   * Rebuild the cache via a scan of the data stores
   * --------------------------------------------------------------------------------------*/
  bool IdManager::Scan(){

//    for (const auto &pair : this->m_cache) {
//      aid max;
//      Store *store = pair.second->GetStore();

//      pair.second->GetStore()->ScanStoreIds(&max, &pair.second.)
//    }
  }

  /* ----------------------------------------------------------------------------------------
   * Rebuild the cache via a load of the data file. On successful load, the data file is
   * truncated so that it is no longer valid.
   * --------------------------------------------------------------------------------------*/
  bool IdManager::Load() {
    // after we have completed a load we should write a bad magic number to the file ....
    char magic[2];

    if(!this->Seek(0)) {
      return false;
    }

    // read the magic
    if(!this->Read(magic,2)) {
      return false; // not a valid store
    }

    // magic should be Valid
    if(magic[0] != ValidFileMarker[0] || magic[1] != ValidFileMarker[1] ) {
      // not a valid store
      return false;
    }

    // Invalidate the store magic for future
    // Save will revalidate it
    if(!this->Seek(0)) {
      return false; // this is bad
    }
    if(!this->Write(InvalidFileMarker,1)) {
      return false; // this is bad
    }

    // start to read the index
    /*
    *   <header><index><data>
    *   <header> = <magic(2)><type-count(2)>
    *   <index>=<index-item>,<index-item>...type-count items
    *   <index-item>=<type-id(1)><counter(4)><id-count(2)><file-offset(4)>
    *   <data>=<data-item>,<data-item>,...id-count items
    *   <data-item>=<id(4)>
    */
    std::uint16_t typecnt;
    if(!this->Read(&typecnt)) {
      return false;
    }

    // Get the type index-items
    for(std::uint16_t i = 0; i < typecnt; i++) {

      //<index-item>=<type-id(1)><counter(4)><id-count(2)><file-offset(4)>

      // read type id
      std::uint8_t tid;
      if(!this->Read(&tid)) {
        return false;
      }

      // read the counter value
      std::uint32_t counter;
      if(!this->Read(&counter)){
        return false;
      }

      // read reclaimed id count for type
      std::uint16_t reclaimCnt;
      if(!this->Read(&reclaimCnt)) {
        return false;
      }

      // read data offset for data start
      std::uint32_t offset;
      if(!this->Read(&offset)) {
        return false;
      }

      // do we have the type registered?
      Storeable::Type type = (Storeable::Type)tid;
      IdCacheItem *item = this->m_cache[type];
      if (item != 0x0) {
        // set the load count and file offset on the item
        item->SetFileOffset((long)offset);
        item->SetIdLoadCount(reclaimCnt);
        item->SetCounter((aid)counter);
      } else {
        // have an unregistered type.... do nothing with it.
      }

    }

    // Load the the actual reclaimed ids
    for (const auto &pair : this->m_cache) {
      std::uint32_t reclaimCount = pair.second->ReclaimedIdCount();
      long offset = pair.second->FileOffset();

      if(!this->Seek(offset)) {
        return false;
      }

      for(std::uint32_t i = 0; i < reclaimCount; i++) {
        std::uint32_t id;
        if(!this->Read(&id)) {
          return false;
        }
        pair.second->Reclaim((aid)id);
      }
    }

    // load success
    return true;
  }

  /* ----------------------------------------------------------------------------------------
   * Save the state of the cache to disk.
   * File layout
   *
   *   <header><index><data>
   *   <header> = <magic(2)><type-count(2)>
   *   <index>=<index-item>,<index-item>...type-count items
   *   <index-item>=<type-id(1)><counter(4)><id-count(2)><file-offset(4)>
   *   <data>=<data-item>,<data-item>,...id-count items
   *   <data-item>=<id(4)>
   * --------------------------------------------------------------------------------------*/
  bool IdManager::Save() {

    // write the header
    this->Seek(0); // seek to begining

    // Write magic header
    if(!this->Write(ValidFileMarker, 2)) {
      return false;
    }

    // Write count types
    std::uint16_t cnt = (std::uint16_t)this->m_cache.size();
    if(!this->Write(cnt)) {
      return false;
    }

    // Write out the index items
    // <index-item>=<type-id(1)><counter(4)><id-count(2)><file-offset(4)>
    for(const auto &pair : this->m_cache) {
      std::uint16_t reclaimCnt = (std::uint16_t)pair.second->ReclaimedIdCount();
      std::uint8_t type = (std::uint8_t)pair.first;
      std::uint32_t counter = (std::uint32_t)pair.second->Counter();
      std::uint32_t fakeOffset = 0;

      // Write the type
      if(!this->Write(type)) {
        return false;
      }

      // Write the counter value
      if(!this->Write(counter)) {
        return false;
      }

      // Write the reclaimed id count
      if(!this->Write(reclaimCnt)) {
        return false;
      }

      // Save the location to the cache item where we
      // have to come back and write the read dataoffset
      pair.second->SetFileOffset(this->Tell());

      // write the fake dataoffset
      if(!this->Write(fakeOffset)){
        return false;
      }
    }


    // Loop again writing the actual data

    long marker = this->Tell();

    // Write the data items
    for(const auto &pair : this->m_cache) {

      // seek to the write marker
      if(!this->Seek(marker)) {
        return false;
      }

      // write the reclaimed id data for this type
      auto data = pair.second->Data();
      for(auto id : data) {
        if(!this->Write((uint32_t)id)) {
          return false;
        }
      }

      // keep a copy of where this data begines
      long offset = marker;

      // set the marker at where we are for next write
      marker = this->Tell();

      // jump back to this types index entry
      if(!this->Seek(pair.second->FileOffset())) {
        return false;
      }

      // write the correct data offset replacing the old fake offset
      if(!this->Write((uint32_t)offset)){
        return false;
      }

      // will loop back around and reposition to marker.
    }

    // we are done
    return true;
  }


  /* ----------------------------------------------------------------------------------------
   * Write data size long to the pos in the file
   * --------------------------------------------------------------------------------------*/
  bool IdManager::Write(long pos, const char *data, std::size_t size){
    if(!this->Seek(pos)) {
      return false;
    }
    return this->Write(data, size);
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  bool IdManager::Write(long pos, std::uint8_t data){
    if(!this->Seek(pos)) {
      return false;
    }
    return this->Write(data);
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  bool IdManager::Write(long pos, std::uint16_t data){
    if(!this->Seek(pos)) {
      return false;
    }
    return this->Write(data);
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  bool IdManager::Write(long pos, std::uint32_t data){
    if(!this->Seek(pos)) {
      return false;
    }
    return  this->Write(data);
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  bool IdManager::Read(long pos, char *data, std::size_t size){
    if(!this->Seek(pos)) {
      return false;
    }
    return this->Read(data,size);
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  bool IdManager::Read(long pos, std::uint8_t *data){
    if(!this->Seek(pos)) {
      return false;
    }
    return this->Read(data);
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  bool IdManager::Read(long pos, std::uint16_t *data){
    if(!this->Seek(pos)) {
      return false;
    }
    return this->Read(data);
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  bool IdManager::Read(long pos, std::uint32_t *data){
    if(!this->Seek(pos)) {
      return false;
    }
    return  this->Read(data);
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  bool IdManager::Write(const char *data, std::size_t size) {
    // std::size_t fwrite( const void* buffer, std::size_t size, std::size_t count, std::FILE* stream );

    // write size bytes at the current position
    std::size_t written = std::fwrite((void*)data,1,size,this->m_fd);
    return written == size;
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  bool IdManager::Write(std::uint8_t data) {
    char buf[1];
    buf[0] = (char)data;
    return this->Write(buf,1);
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  bool IdManager::Write(std::uint16_t data) {
    char buf[2];
    buf[0] = (char)(data >>8);
    buf[1] = (char)(data);
    return this->Write(buf,2);
  }

/*
      data[0] = value >> 24;
      data[1] = value >> 16;
      data[2] = value >> 8;
      data[3] = value;
  */


  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  bool IdManager::Write(std::uint32_t data) {
    char buf[4];
    buf[0] = (char)(data >> 24);
    buf[1] = (char)(data >> 16);
    buf[2] = (char)(data >> 8);
    buf[3] = (char)(data);
    return this->Write(buf,4);
  }

  /* ----------------------------------------------------------------------------------------
   * data needs to be at least size bytes long
   * --------------------------------------------------------------------------------------*/
  bool IdManager::Read(char *data, std::size_t size) {
    std::size_t read = fread((void*)data,1,size,this->m_fd);
    return read == size;
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  bool IdManager::Read(std::uint8_t *data) {
    return this->Read((char*)data, 1);
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  bool IdManager::Read(std::uint16_t *data) {
    char buf[2];
    if(!this->Read(buf,2)) {
      return false;
    }

    *data = (buf[0] <<8) + buf[1];
    return true;
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  bool IdManager::Read(std::uint32_t *data) {
    char buf[4];
    if(!this->Read(buf,4)) {
      return false;
    }
    *data = (buf[0] << 24) + (buf[1] << 16) + (buf[2] << 8) + buf[3];
    return true;
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  bool IdManager::Seek(long pos) {
    return std::fseek(this->m_fd,pos,SEEK_SET) == 0;
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  bool IdManager::Flush() {
    return std::fflush(this->m_fd) == 0;
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  long IdManager::Tell() {
     return std::ftell(this->m_fd);
  }

}
