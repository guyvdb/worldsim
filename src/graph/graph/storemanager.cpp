#include "storemanager.h"

#include <filesystem>
#include <storeable.h>
#include <entity.h>
#include <relation.h>
#include <attribute.h>

namespace graph {



  StoreManager::StoreManager(const char *datadir, std::size_t pagesize) : m_pagesize(pagesize), m_datadir(datadir) {

   // this->m_dataStores = new std::vector<Store*>();
   // this->m_dataStoreIndex = new std::map<Storeable::Type, Store*>();
    this->m_entityStore = this->CreateStore(ENTITY_STORE_FILENAME,
                                            Storeable::EntitySize,
                                            Storeable::Concept::CEntity,
                                            new EntityEncoder());

    this->m_relationStore = this->CreateStore(RELATION_STORE_FILENAME,
                                              Storeable::RelationSize,
                                              Storeable::Concept::CRelation,
                                              new RelationEncoder());

    this->m_attributeDefinitionStore = this->CreateStore(ATTRIBUTE_DEFINITION_STORE_FILENAME,
                                                         Storeable::AttributeDefinitionSize,
                                                         Storeable::Concept::CAttributeDefinition,
                                                         new AttributeDefinitionEncoder());

    this->m_attributeBucketStore = this->CreateStore(ATTRIBUTE_BUCKET_STORE_FILENAME,
                                                     Storeable::AttributeBucketSize,
                                                     Storeable::Concept::CAttributeBucket,
                                                     new AttributeBucketEncoder());


    // Create the data stores
  //  this->m_idStore = new IdStore(ConcatStorePath(ID_STORE_FILENAME), pagesize);

    //this->m_entityStore = new Store(fn(ENTITY_STORE_FILENAME), pagesize, Storeable::EntitySize, new EntityFactory(), Storeable::Type::Entity);
    //this->m_thingTypeStore = new ThingTypeStore(fn(THING_TYPE_STORE_FILENAME), pagesize, Storeable::EntityTypeSize);
    //this->m_thingPropertyStore = new PropertyStore(fn(THING_PROP_STORE_FILENAME), pagesize, Storeable::PropertySize);
    //this->m_thingPropertyTypeStore = new PropertyTypeStore(fn(THING_PROP_TYPE_STORE_FILENAME),pagesize, Storeable::PropertyTypeSize);

    //this->m_relationStore = new RelationStore(fn(RELATION_STORE_FILENAME),pagesize, Storeable::RelationSize);
    //this->m_relationTypeStore = new RelationTypeStore(fn(RELATION_TYPE_STORE_FILENAME), pagesize, Storeable::RelationTypeSize);
    //this->m_relationPropertyStore = new PropertyStore(fn(RELATION_PROP_STORE_FILENAME), pagesize, Storeable::PropertySize);
    //this->m_relationPropertyTypeStore = new PropertyTypeStore(fn(RELATION_PROP_TYPE_STORE_FILENAME),pagesize, Storeable::PropertyTypeSize);


    // Keep a vector of stores
   // this->m_dataStores = new std::vector<Store*>(9);
    //this->m_dataStores->push_back(this->m_idStore);
    //this->m_dataStores->push_back(this->m_entityStore);
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
  }

  bool StoreManager::Open() {

    bool error = false;

    // open all the files
    for (auto& store : this->m_dataStores) {
      if(!store->Open()) {
        error = true;
        std::cout << "[STOREMANAGER] Failed to open store: " << store->Filename() << std::endl;
        break;
      }
    }

    if(error) {
      for(auto &store : this->m_dataStores) {
        store->Close();
      }
      return false;
    }

    // open all stores
    return true;
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  bool StoreManager::Close() {
    // All files should have been fsynced via a log shutdown checkpoint -- asset that here

    // close all stores

    return true;
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  Store *StoreManager::CreateStore(std::string filename, std::size_t size, Storeable::Concept concept, Encoder *encoder) {
    std::string fq = fn(filename);

    std::cout << "[STOREMANAGER] Create store: " <<
                 "filename=" << filename <<
                 ", fq=" << fq << std::endl;


    Store *s = new Store(fq,this->m_pagesize, size, encoder, concept);
    this->m_dataStores.push_back(s);
    this->m_dataStoreIndex[concept] = s;
    return s;

  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  Store *StoreManager::GetStore(Storeable::Concept concept) {
    std::map<Storeable::Concept,Store*>::iterator it = this->m_dataStoreIndex.find(concept);
    if(it != this->m_dataStoreIndex.end()) {
      return it->second;
    }
    return 0x0;
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  std::string StoreManager::fn(std::string filename) {
    std::filesystem::path result(this->m_datadir);
    result /= filename;
    return result.native();
  }

}
