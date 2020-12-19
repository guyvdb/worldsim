#include "registry.h"
#include <graph.h>
#include <transaction.h>

namespace graph {
  namespace type {

    /* ----------------------------------------------------------------------------------------
     *
     * --------------------------------------------------------------------------------------*/
    Registry::Registry(graph::Graph *g, store::StoreManager *storeManager) : m_graph(g) {
      this->m_typeStore = storeManager->GetStore(Storeable::ClassConcept);
      if(this->m_typeStore == 0x0) {
        std::cout << "[REGISTRY] Error - failed to get type store from store manager." << std::endl;
      }
    }

    /* ----------------------------------------------------------------------------------------
     *
     * --------------------------------------------------------------------------------------*/
    bool Registry::Open() {
      return this->m_typeStore->Scan(this);
    }

    /* ----------------------------------------------------------------------------------------
     *
     * --------------------------------------------------------------------------------------*/
    bool Registry::Close() {
      return true;
    }

    /* ----------------------------------------------------------------------------------------
     *
     * --------------------------------------------------------------------------------------*/
    void Registry::Scan(type::gid id, bool active, ByteBuffer *data, std::size_t) {
      if(active) {
        // we need to get the name of every type and its associated id
        FixedString s(data, Class::NAME_OFFSET);
        std::cout << "[REGISTRY] Register type: " << s.StdString() << " - " << id << std::endl;
        this->m_nameIndex[s.StdString()] = id;
      }
    }

    /* ----------------------------------------------------------------------------------------
     *
     * --------------------------------------------------------------------------------------*/
    void Registry::IndexTypeName(type::gid id, std::string name) {
      this->m_nameIndex[name] = id;
    }

    /* ----------------------------------------------------------------------------------------
     *
     * --------------------------------------------------------------------------------------*/
    // The registry takes ownership of the factory pointer
    // an will release memory it ~Registry()
    void Registry::RegisterClass(ClassDefinition definition) {

      // Does the type exist in the graph. I.e. does it have a gid
      if(!this->ClassExists(definition.Name)) {
        this->CreateClass(definition.Concept, definition.Name, definition.SuperclassName ,definition.Properties);
      }

      // do we alread have a factory registered for this type? If so
      // release the current factory and assign the new one
    }

    /* ----------------------------------------------------------------------------------------
     *
     * --------------------------------------------------------------------------------------*/
    type::gid Registry::GetClassGraphId(std::string name) {
      return this->m_nameIndex[name];
    }

    /* ----------------------------------------------------------------------------------------
     *
     * --------------------------------------------------------------------------------------*/
    bool Registry::ClassExists(std::string name) {
      // if the name is in the name->id index it exists
      return this->m_nameIndex.find(name) != this->m_nameIndex.end();
    }

    /* ----------------------------------------------------------------------------------------
     *
     * --------------------------------------------------------------------------------------*/
    gid Registry::CreateClass(Storeable::Concept concept, std::string name, std::string superclass, std::vector<ClassProperty> properties) {
      gid result = NullGraphId;

      graph::Transaction tx;
      if(this->m_graph->Update(tx)) {
        Class *t = tx.CreateClass(concept, name, tx.FindClass(superclass));

        // create all the propdefs

        for(auto &property : properties) {
          t->AddProperty(property.Name, property.DataType, property.Required);

        }



        result = t->GetGraphId();
        if(!tx.Commit()) {
          std::cout << "[REGISTRY] Error - failed to commit transaction on create class." << std::endl;
          return NullGraphId;
        }
      }
      return  result;
    }




  }
}

