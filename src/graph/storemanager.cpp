#include "storemanager.h"

#include <filesystem>
#include <storeable.h>
#include <entity.h>

namespace graph {



  StoreManager::StoreManager(const char *datadir, std::size_t pagesize) : m_pagesize(pagesize), m_datadir(datadir) {



    // Create the data stores
  //  this->m_idStore = new IdStore(ConcatStorePath(ID_STORE_FILENAME), pagesize);

    this->m_entityStore = new Store(fn(ENTITY_STORE_FILENAME), pagesize, Storeable::EntitySize, new EntityFactory());
    //this->m_thingTypeStore = new ThingTypeStore(fn(THING_TYPE_STORE_FILENAME), pagesize, Storeable::EntityTypeSize);
    //this->m_thingPropertyStore = new PropertyStore(fn(THING_PROP_STORE_FILENAME), pagesize, Storeable::PropertySize);
    //this->m_thingPropertyTypeStore = new PropertyTypeStore(fn(THING_PROP_TYPE_STORE_FILENAME),pagesize, Storeable::PropertyTypeSize);

    //this->m_relationStore = new RelationStore(fn(RELATION_STORE_FILENAME),pagesize, Storeable::RelationSize);
    //this->m_relationTypeStore = new RelationTypeStore(fn(RELATION_TYPE_STORE_FILENAME), pagesize, Storeable::RelationTypeSize);
    //this->m_relationPropertyStore = new PropertyStore(fn(RELATION_PROP_STORE_FILENAME), pagesize, Storeable::PropertySize);
    //this->m_relationPropertyTypeStore = new PropertyTypeStore(fn(RELATION_PROP_TYPE_STORE_FILENAME),pagesize, Storeable::PropertyTypeSize);


    // Keep a vector of stores
    this->m_dataStores = new std::vector<Store*>(9);
    //this->m_dataStores->push_back(this->m_idStore);
    this->m_dataStores->push_back(this->m_entityStore);
    //this->m_dataStores->push_back(this->m_thingTypeStore);
    //this->m_dataStores->push_back(this->m_thingPropertyStore);
    //this->m_dataStores->push_back(this->m_thingPropertyTypeStore);
    //this->m_dataStores->push_back(this->m_relationStore);
    //this->m_dataStores->push_back(this->m_relationTypeStore);
    //this->m_dataStores->push_back(this->m_relationPropertyStore);
    //this->m_dataStores->push_back(this->m_relationPropertyTypeStore);


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
  const char* StoreManager::fn(const char *filename) {
    std::filesystem::path result(this->m_datadir);
    result /= filename;
    return result.c_str();
  }

}