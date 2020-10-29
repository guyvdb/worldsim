#include "storemanager.h"

#include <filesystem>
#include <storeable.h>

namespace graph {



  StoreManager::StoreManager(const char *datadir, std::size_t pagesize) : m_pagesize(pagesize), m_datadir(datadir) {



    // Create the data stores
  //  this->m_idStore = new IdStore(ConcatStorePath(ID_STORE_FILENAME), pagesize);

    this->m_thingStore = new ThingStore(ConcatStorePath(THING_STORE_FILENAME), pagesize, Storeable::ThingSize);
    this->m_thingTypeStore = new ThingTypeStore(ConcatStorePath(THING_TYPE_STORE_FILENAME), pagesize, Storeable::ThingTypeSize);
    this->m_thingPropertyStore = new PropertyStore(ConcatStorePath(THING_PROP_STORE_FILENAME), pagesize, Storeable::PropertySize);
    this->m_thingPropertyTypeStore = new PropertyTypeStore(ConcatStorePath(THING_PROP_TYPE_STORE_FILENAME),pagesize, Storeable::PropertyTypeSize);

    this->m_relationStore = new RelationStore(ConcatStorePath(RELATION_STORE_FILENAME),pagesize, Storeable::RelationSize);
    this->m_relationTypeStore = new RelationTypeStore(ConcatStorePath(RELATION_TYPE_STORE_FILENAME), pagesize, Storeable::RelationTypeSize);
    this->m_relationPropertyStore = new PropertyStore(ConcatStorePath(RELATION_PROP_STORE_FILENAME), pagesize, Storeable::PropertySize);
    this->m_relationPropertyTypeStore = new PropertyTypeStore(ConcatStorePath(RELATION_PROP_TYPE_STORE_FILENAME),pagesize, Storeable::PropertyTypeSize);


    // Keep a vector of stores
    this->m_dataStores = new std::vector<Store*>(9);
    //this->m_dataStores->push_back(this->m_idStore);
    this->m_dataStores->push_back(this->m_thingStore);
    this->m_dataStores->push_back(this->m_thingTypeStore);
    this->m_dataStores->push_back(this->m_thingPropertyStore);
    this->m_dataStores->push_back(this->m_thingPropertyTypeStore);
    this->m_dataStores->push_back(this->m_relationStore);
    this->m_dataStores->push_back(this->m_relationTypeStore);
    this->m_dataStores->push_back(this->m_relationPropertyStore);
    this->m_dataStores->push_back(this->m_relationPropertyTypeStore);


  }

  StoreManager::~StoreManager() {
    // close all stores

    // delete the list of stores
    delete this->m_dataStores;
  }

  bool StoreManager::Open() {
    // open all stores
    return true;
  }

  bool StoreManager::Close() {
    // All files should have been fsynced via a log shutdown checkpoint -- asset that here

    // close all stores

    return true;
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  const char* StoreManager::ConcatStorePath(const char *filename) {
    std::filesystem::path result(this->m_datadir);
    result /= filename;
    return result.c_str();
  }

}
