#ifndef STOREMANAGER_H
#define STOREMANAGER_H

#include <store.h>
#include <vector>
#include <string>
#include <map>

// file names
#define ID_STORE_FILENAME "id.db"
#define ENTITY_TYPE_STORE_FILENAME "entity.type"
#define ENTITY_STORE_FILENAME "entity.db"
#define ENTITY_PROP_STORE_FILENAME "entity.prop"
#define ENTITY_PROP_TYPE_STORE_FILENAME "entity.schema"
#define RELATION_TYPE_STORE_FILENAME "relation.type"
#define RELATION_STORE_FILENAME "relation.db"
#define RELATION_PROP_STORE_FILENAME "relation.prop"
#define RELATION_PROP_TYPE_STORE_FILENAME "relation.schema"

namespace graph {

  class StoreManager  {
    public:
      StoreManager(const char *datadir, std::size_t pagesize);
      ~StoreManager();

      bool Open();
      bool Close();
      std::vector<Store*> *Stores() { return &this->m_dataStores; }
      Store *GetStore(Storeable::Concept concept);
    private:

      Store *CreateStore(std::string filename, std::size_t size, Storeable::Concept concept, Encoder *encoder);
      std::string fn(std::string filename );

      std::size_t m_pagesize;
      const char *m_datadir;

      // the stores...
      //IdStore *m_idStore;

      Store *m_entityStore;
      Store *m_entityTypeStore;
      Store *m_entityPropertyStore;
      Store *m_entityPropertyTypeStore;

      Store *m_relationStore;
      Store *m_relationTypeStore;
      Store *m_relationPropertyStore;
      Store *m_relationPropertyTypeStore;

      std::vector<Store*> m_dataStores;
      std::map<Storeable::Concept, Store*> m_dataStoreIndex;
  };
}

#endif // STOREMANAGER_H
