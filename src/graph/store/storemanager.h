#ifndef STOREMANAGER_H
#define STOREMANAGER_H

#include <store/store.h>
#include <vector>
#include <string>
#include <map>


//#define ID_STORE_FILENAME "id.db"
//#define ENTITY_TYPE_STORE_FILENAME "entity.type"
//#define ENTITY_STORE_FILENAME "entity.db"
//#define ENTITY_PROP_STORE_FILENAME "entity.prop"
//#define ENTITY_PROP_TYPE_STORE_FILENAME "entity.schema"
//#define RELATION_TYPE_STORE_FILENAME "relation.type"
//#define RELATION_STORE_FILENAME "relation.db"
//#define RELATION_PROP_STORE_FILENAME "relation.prop"
//#define RELATION_PROP_TYPE_STORE_FILENAME "relation.schema"

namespace graph {

  namespace store {


    class StoreManager  {
      public:


        //const char * ID_STORE_FILENAME = "id.db";
        const char * ENTITY_STORE_FILENAME = "entity.db";
        const char * ENTITY_DEFINITION_STORE_FILENAME = "entity.def";
        const char * RELATION_STORE_FILENAME = "relation.db";
        const char * RELATION_DEFINITION_STORE_FILENAME = "relation.def";
        const char * TYPE_STORE_FILENAME = "type.db";
        const char * HEIRACHY_STORE_FILENAME = "heirachy.db";


        const char * ATTRIBUTE_BUCKET_STORE_FILENAME = "attribute.db";
        const char * ATTRIBUTE_DEFINITION_STORE_FILENAME = "attribute.def";

        StoreManager(const char *datadir, std::size_t pagesize);
        ~StoreManager();

        bool Open();
        bool Close();
        std::vector<Store*> *Stores() { return &this->m_dataStores; }
        Store *GetStore(Storeable::Concept concept);
      private:

        Store *CreateStore(std::string filename, std::size_t size, Storeable::Concept concept, Decoder *encoder);
        std::string fn(std::string filename );

        std::size_t m_pagesize;
        const char *m_datadir;

        Store *m_entityStore;
        Store *m_relationStore;
        Store *m_attributeBucketStore;
        Store *m_attributeDefinitionStore;
        Store *m_typeStore;
        Store *m_heirachyStore;


        std::vector<Store*> m_dataStores;
        std::map<Storeable::Concept, Store*> m_dataStoreIndex;
    };

  }
}

#endif // STOREMANAGER_H
