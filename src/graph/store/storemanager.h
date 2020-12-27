#ifndef STOREMANAGER_H
#define STOREMANAGER_H

#include "store.h"
#include <vector>
#include <string>
#include <map>


namespace graph {

  namespace store {


    class StoreManager  {
      public:
        const char * ENTITY_STORE_FILENAME = "entity.db";
       // const char * ENTITY_DEFINITION_STORE_FILENAME = "entity.def";
        const char * RELATION_STORE_FILENAME = "relation.db";
        //const char * RELATION_DEFINITION_STORE_FILENAME = "relation.def";
        const char * CLASS_STORE_FILENAME = "class.db";
        const char * INHERITANCE_STORE_FILENAME = "inheritance.db";
        const char * INSTANCE_STORE_FILENAME = "instance.db";


        const char * ATTRIBUTE_BUCKET_STORE_FILENAME = "attribute.db";
        const char * ATTRIBUTE_DEFINITION_STORE_FILENAME = "attribute.def";

        StoreManager(const char *datadir, std::size_t pagesize);
        ~StoreManager();

        bool Open();
        bool Close();
        std::vector<Store*> GetStores() { return this->m_dataStores; }
        Store *GetStore(Storeable::Concept concept);
      private:

        Store *CreateStore(std::string filename, std::size_t size, Storeable::Concept concept);
        std::string fn(std::string filename );

        std::size_t m_pagesize;
        const char *m_datadir;

        Store *m_entityStore;
        Store *m_relationStore;
        Store *m_classStore;
        Store *m_inheritanceStore;
        Store *m_instanceStore;


        std::vector<Store*> m_dataStores;
        std::map<Storeable::Concept, Store*> m_dataStoreIndex;
    };

  }
}

#endif // STOREMANAGER_H
