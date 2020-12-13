#include "registry.h"
#include <graph.h>
#include <tx/transaction.h>

namespace graph {
  namespace type {

    /* ----------------------------------------------------------------------------------------
     *
     * --------------------------------------------------------------------------------------*/
    Registry::Registry(graph::Graph *g, store::StoreManager *storeManager) : m_graph(g) {
      this->m_typeStore = storeManager->GetStore(Storeable::TypeConcept);
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
        FixedString s(data, Type::NAME_OFFSET);
        std::cout << "[REGISTRY] Register type: " << s.GetValue() << " - " << id << std::endl;
        this->m_nameIndex[s.GetValue()] = id;
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
    void Registry::RegisterType(TypeDefinition definition) {

      // Does the type exist in the graph. I.e. does it have a gid
      if(!this->TypeExists(definition.Name)) {
        this->CreateType(definition.Concept, definition.Name, definition.Properties);
      }

      // do we alread have a factory registered for this type? If so
      // release the current factory and assign the new one
    }

    /* ----------------------------------------------------------------------------------------
     *
     * --------------------------------------------------------------------------------------*/
    type::gid Registry::GetTypeId(std::string name) {
      return this->m_nameIndex[name];
    }

    /* ----------------------------------------------------------------------------------------
     *
     * --------------------------------------------------------------------------------------*/
    bool Registry::TypeExists(std::string name) {
      // if the name is in the name->id index it exists
      return this->m_nameIndex.find(name) != this->m_nameIndex.end();
    }

    /* ----------------------------------------------------------------------------------------
     *
     * --------------------------------------------------------------------------------------*/
    gid Registry::CreateType(Storeable::Concept concept, std::string name, std::vector<TypeProperty> properties) {
      graph::tx::Transaction tx;
      if(this->m_graph->Update(tx)) {
        type::Type *t = tx.CreateType(concept, name);
        return t->GetGraphId();
      }

      // failed...
      std::cout << "[REGISTRY] Error - failed to create type " << name << "." << std::endl;
      return type::NullGraphId;
    }




  }
}

