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

      // A full scan of the class store should have already occured.
      // If the class is not in the registry then it does not exist
      // and it needs to be created.
      // Does the type exist in the graph. I.e. does it have a gid
      if(!this->ClassExists(definition.Name)) {
        this->CreateClass(definition); //definition.Concept, definition.Name, definition.SuperclassName ,definition.Properties);
      }


      // class migh have been loaded from a store scan.. attach the factory
      type::gid id = this->GetClassGraphId(definition.Name);
      if(this->m_factories.find(id) == this->m_factories.end()) {
        this->m_factories[id] = definition.Factory;
      }
    }

    /* ----------------------------------------------------------------------------------------
     *
     * --------------------------------------------------------------------------------------*/
    void Registry::RegisterFactoryFunction(std::string clazz, FactoryFunc func) {
      type::gid id = this->GetClassGraphId(clazz);
      return this->RegisterFactoryFunction(id, func);
    }

    /* ----------------------------------------------------------------------------------------
     *
     * --------------------------------------------------------------------------------------*/
    void Registry::RegisterFactoryFunction(type::gid clazz, FactoryFunc func) {
      this->m_factories[clazz] = func;
    }

    /* ----------------------------------------------------------------------------------------
     *
     * --------------------------------------------------------------------------------------*/
    bool Registry::FactoryExists(std::string clazz) {
      type::gid id = this->GetClassGraphId(clazz);
      return this->FactoryExists(id);
    }

    /* ----------------------------------------------------------------------------------------
     *
     * --------------------------------------------------------------------------------------*/
    bool Registry::FactoryExists(type::gid clazz) {
      return this->m_factories.find(clazz) != this->m_factories.end();
    }

    /* ----------------------------------------------------------------------------------------
     *
     * --------------------------------------------------------------------------------------*/
    FactoryFunc Registry::Factory(std::string clazz) {
      type::gid id = this->GetClassGraphId(clazz);
      return this->Factory(id);
    }

    /* ----------------------------------------------------------------------------------------
     *
     * --------------------------------------------------------------------------------------*/
    FactoryFunc Registry::Factory(type::gid clazz) {
      if(this->m_factories.find(clazz) == this->m_factories.end()) {
        return 0x0;
      }
      return this->m_factories[clazz];
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
    gid Registry::CreateClass(ClassDefinition definition) { //Storeable::Concept concept, std::string name, std::string superclass, std::vector<ClassProperty> properties) {
      gid result = NullGraphId;

      graph::Transaction tx;
      if(this->m_graph->Update(tx)) {
        Class *c = tx.CreateClass(definition.Concept, definition.Name, tx.FindClass(definition.SuperclassName));
        // create all the propdefs
        for(auto &property : definition.Properties) {
          if(!c->AddPropDef(property.Name, property.DataType, property.Required)){
            std::cout << "[REGISTRY] Error - failed to add class propdef." << std::endl;
            return NullGraphId;
          }
        }
        result = c->GetGraphId();
        if(!tx.Commit()) {
          std::cout << "[REGISTRY] Error - failed to commit transaction on create class." << std::endl;
          return NullGraphId;
        }
      } else {
        std::cout << "[REGISTRY] Error - failed to start a readwrite transaction." << std::endl;
        return type::NullGraphId;
      }
      return  result;
    }




  }
}

