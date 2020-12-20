#include "storemanager.h"

#include <filesystem>
#include <storeable.h>
#include <entity.h>
#include <relation.h>
#include <class.h>
#include <inheritance.h>

namespace graph {


  namespace store {



    StoreManager::StoreManager(const char *datadir, std::size_t pagesize) : m_pagesize(pagesize), m_datadir(datadir) {

     // this->m_dataStores = new std::vector<Store*>();
     // this->m_dataStoreIndex = new std::map<Storeable::Type, Store*>();
      this->m_entityStore = this->CreateStore(ENTITY_STORE_FILENAME,
                                              Storeable::EntitySize,
                                              Storeable::Concept::EntityConcept);

      this->m_relationStore = this->CreateStore(RELATION_STORE_FILENAME,
                                                Storeable::RelationSize,
                                                Storeable::Concept::RelationConcept);


      this->m_classStore = this->CreateStore(CLASS_STORE_FILENAME,
                                            Storeable::ClassSize,
                                            Storeable::ClassConcept);

      this->m_inheritanceStore = this->CreateStore(INHERITANCE_STORE_FILENAME,
                                                Storeable::InheritanceSize,
                                                Storeable::InheritanceConcept);

    }

    StoreManager::~StoreManager() {
      // close all stores
      for(auto &store : this->m_dataStores) {
        store->Close();
        delete store;

      }

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
    Store *StoreManager::CreateStore(std::string filename, std::size_t size, Storeable::Concept concept) {
      std::string fq = fn(filename);

//      std::cout << "[STOREMANAGER] Create store: " <<
//                   "filename=" << filename <<
//                   ", fq=" << fq << std::endl;


      Store *s = new Store(fq,this->m_pagesize, size, concept);
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
}
