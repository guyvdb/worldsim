#include "idmanager.h"
#include <gid.h>
#include <iostream>
#include <string>
const std::string filename("id.db");
const char ValidFileMarker[2] = {0xA,0xB};
const char InvalidFileMarker[2] = {0x0,0x0};

namespace graph {


  IdCacheItem::IdCacheItem(Store *store) : IdAccumulator() ,m_store(store),m_active(false){
  }

  /* ----------------------------------------------------------------------------------------
   * Take the next id out of the data vector if there is one. Otherwise
   * return the counter and increment it. Do all of this within a mutex lock
   * --------------------------------------------------------------------------------------*/
  gid IdCacheItem::NextId() {
    if(!this->m_active) {
      std::cout << "[ID MANAGER] Error - trying to get id while cache item is inactive." << std::endl;
      return (gid)NullId;
    }


    gid result;

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
  void IdCacheItem::Reclaim(gid id) {
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
  IdManager::IdManager(std::filesystem::path datadir) : m_file(0x0), m_datadir(datadir),  m_isopen(false) {
    std::filesystem::path fn(this->m_datadir);
    fn /= filename;
    this->m_file = new File(fn);
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


    delete this->m_file;

  }

  /* ----------------------------------------------------------------------------------------
   * The caller should have called Register() on all datastores before opening the IdManager.
   * The Id manager will reconstruct its cache from disk file. If the file does not exist or
   * is damaged, the manager will recreate the file by scanning all data stores and recording
   * all reclaimed ids and the highest issued id.
   * --------------------------------------------------------------------------------------*/
  bool IdManager::Open(){
    // open the file
    if(!this->m_file->Open()){
      std::cout << "[ID MANAGER] Error - failed to open file."  << std::endl;
      return false;
    }

    // load the file
    if(this->Load()) {
      this->MarkItemState(true);
      this->m_isopen = true;
      return true;
    }

    if(this->Scan()) {
      this->MarkItemState(true);
      this->m_isopen = true;
      return true;
    }

    // This is very bad we should not get here.
    std::cout << "[ID MANAGER] Error - failed to open." << std::endl;
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
    this->m_file->Close();
  }

  /* ----------------------------------------------------------------------------------------
   * Mark this id as reclaimed for the given type
   * --------------------------------------------------------------------------------------*/
  void IdManager::Reclaim(gid id, Storeable::Concept concept){
    if(!this->m_isopen) {
      std::cout << "[ID MANAGER] Error - trying to reclaim an id while closed." << std::endl;
      return;
    }
    IdCacheItem *item = this->m_cache[concept];
    if(item == 0x0) {
      std::cout << "[ID MANAGER] Error - trying to reclaim an id with an unregisterd type." << std::endl;
      return;
    }

    // The item will lock a mutex on reclaim
    item->Reclaim((gid)id);
  }

  /* ----------------------------------------------------------------------------------------
   * Mark this id as reclaimed for the given type
   * --------------------------------------------------------------------------------------*/
  /*void IdManager::Reclaim(tid id, Storeable::Concept type){
    this->Reclaim((gid)id, type);
  }*/

  /* ----------------------------------------------------------------------------------------
   * Register a data store for a given type with the manager. This function should be called
   * an appropriate number of times prior to the store being opened. Once the store is open
   * no more stores can be registerd. The register method is not thread safe.
   * --------------------------------------------------------------------------------------*/
  bool IdManager::Register(Store *store, Storeable::Concept concept){
    if(this->m_isopen) {
      std::cout << "[ID MANAGER] Error - trying to register a store after the manager has been opened." << std::endl;
      return false;
    }

    IdCacheItem *item = this->m_cache[concept];
    if(item != 0x0) {
      std::cout << "[ID MANAGER] Error - trying to register alread registerd store." << std::endl;
      return false;
    }

    item = new IdCacheItem(store);
    this->m_cache[concept] = item;

    return true;
  }

  /* ----------------------------------------------------------------------------------------
   * Get the next gid for the given type (reclaimed or new)
   * --------------------------------------------------------------------------------------*/
  gid IdManager::NextGraphId(Storeable::Concept concept){
    if (!this->m_isopen) {
      std::cout << "[ID MANAGER] Error - trying to get an id while closed." << std::endl;
      return  NullId;
    }

    IdCacheItem *item = this->m_cache[concept];
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
  /*tid IdManager::NextTypeId(Storeable::Concept type){
    return (tid)this->NextGraphId(type);
  }*/

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
    for(const auto &pair : this->m_cache) {
      Store *store = pair.second->GetStore();
      store->ScanIds(pair.second);
    }
    return true;
  }

  /* ----------------------------------------------------------------------------------------
   * Rebuild the cache via a load of the data file. On successful load, the data file is
   * truncated so that it is no longer valid.
   * --------------------------------------------------------------------------------------*/
  bool IdManager::Load() {
    // after we have completed a load we should write a bad magic number to the file ....
    char magic[2];

    if(!this->m_file->Seek(0)) {
      return false;
    }

    // read the magic
    if(!this->m_file->Read(magic,2)) {
      return false; // not a valid store
    }

    // magic should be Valid
    if(magic[0] != ValidFileMarker[0] || magic[1] != ValidFileMarker[1] ) {
      // not a valid store
      std::cout << "[ID MANAGER] Store file magic is not valid." << std::endl;
      return false;
    }

    // Invalidate the store magic for future
    // Save will revalidate it
    if(!this->m_file->Seek(0)) {
      return false; // this is bad
    }

    if(!this->m_file->Write(InvalidFileMarker,2)) {
      return false; // this is bad
    }

    std::uint16_t typecnt;
    if(!this->m_file->Read(&typecnt)) {
      return false;
    }

    // Get the type index-items
    for(std::uint16_t i = 0; i < typecnt; i++) {

      // read type id
      std::uint8_t tid;
      if(!this->m_file->Read(&tid)) {
        return false;
      }

      // read the counter value
      std::uint32_t counter;
      if(!this->m_file->Read(&counter)){
        return false;
      }

      // read reclaimed id count for type
      std::uint16_t reclaimCnt;
      if(!this->m_file->Read(&reclaimCnt)) {
        return false;
      }

      // read data offset for data start
      std::uint32_t offset;
      if(!this->m_file->Read(&offset)) {
        return false;
      }

      // do we have the type registered?
      Storeable::Concept concept = (Storeable::Concept)tid;
      IdCacheItem *item = this->m_cache[concept];
      if (item != 0x0) {
        // set the load count and file offset on the item
        item->SetFileOffset((long)offset);
        item->SetIdLoadCount(reclaimCnt);
        item->SetCounter((gid)counter);
      } else {
        // have an unregistered type.... do nothing with it.
      }
    }

    // Load the the actual reclaimed ids
    for (const auto &pair : this->m_cache) {
      std::uint32_t reclaimCount = pair.second->ReclaimedIdCount();
      long offset = pair.second->FileOffset();

      if(!this->m_file->Seek(offset)) {
        return false;
      }

      for(std::uint32_t i = 0; i < reclaimCount; i++) {
        std::uint32_t id;
        if(!this->m_file->Read(&id)) {
          return false;
        }
        pair.second->Reclaim((gid)id);
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
    this->m_file->Seek(0); // seek to begining

    // Write magic header
    if(!this->m_file->Write(ValidFileMarker, 2)) {
      return false;
    }

    // Write count types
    std::uint16_t cnt = (std::uint16_t)this->m_cache.size();
    if(!this->m_file->Write(cnt)) {
      return false;
    }

    // Write out the index items
    // <index-item>=<type-id(1)><counter(4)><id-count(2)><file-offset(4)>
    for(const auto &pair : this->m_cache) {
      std::uint16_t reclaimCnt = (std::uint16_t)pair.second->ReclaimedIdCount();
      std::uint8_t type = (std::uint8_t)pair.first;
      std::uint32_t counter = (std::uint32_t)pair.second->Counter();
      std::uint32_t fakeOffset = 0xFFFFFFFF;

      // Write the type
      if(!this->m_file->Write(type)) {
        return false;
      }

      // Write the counter value
      if(!this->m_file->Write(counter)) {
        return false;
      }

      // Write the reclaimed id count
      if(!this->m_file->Write(reclaimCnt)) {
        return false;
      }

      // Save the location to the cache item where we
      // have to come back and write the read dataoffset
      pair.second->SetFileOffset(this->m_file->Tell());

      // write the fake dataoffset
      if(!this->m_file->Write(fakeOffset)){
        return false;
      }
    }


    // Loop again writing the actual data
    long marker = this->m_file->Tell();

    // Write the data items
    for(const auto &pair : this->m_cache) {

      // seek to the write marker
      if(!this->m_file->Seek(marker)) {
        return false;
      }

      // write the reclaimed id data for this type
      auto data = pair.second->Data();
      for(auto id : data) {
        if(!this->m_file->Write((uint32_t)id)) {
          return false;
        }
      }

      // keep a copy of where this data begines
      long offset = marker;

      // set the marker at where we are for next write
      marker = this->m_file->Tell();

      // jump back to this types index entry
      if(!this->m_file->Seek(pair.second->FileOffset())) {
        return false;
      }

      // write the correct data offset replacing the old fake offset
      if(!this->m_file->Write((uint32_t)offset)){
        return false;
      }

      // will loop back around and reposition to marker.
    }

    // we are done
    return true;
  }



}
