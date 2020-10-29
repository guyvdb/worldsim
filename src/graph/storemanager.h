#ifndef STOREMANAGER_H
#define STOREMANAGER_H

#include <store.h>
#include <vector>

// file names
#define ID_STORE_FILENAME "id.db"
#define THING_TYPE_STORE_FILENAME "thing.type"
#define THING_STORE_FILENAME "thing.db"
#define THING_PROP_STORE_FILENAME "thing.prop"
#define THING_PROP_TYPE_STORE_FILENAME "thing.schema"
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
    private:

      const char * ConcatStorePath(const char *filename );

      std::size_t m_pagesize;
      const char *m_datadir;

      // the stores...
      //IdStore *m_idStore;

      ThingStore *m_thingStore;
      ThingTypeStore *m_thingTypeStore;
      PropertyStore *m_thingPropertyStore;
      PropertyTypeStore *m_thingPropertyTypeStore;

      RelationStore *m_relationStore;
      RelationTypeStore *m_relationTypeStore;
      PropertyStore *m_relationPropertyStore;
      PropertyTypeStore *m_relationPropertyTypeStore;

      std::vector<Store*> *m_dataStores;
  };
}

#endif // STOREMANAGER_H
