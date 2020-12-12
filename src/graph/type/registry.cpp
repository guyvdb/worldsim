#include "registry.h"
#include <graph.h>
#include <tx/transaction.h>

namespace graph {
  namespace type {

    Registry::Registry(graph::Graph *g) : m_graph(g) {

    }

    Registry::~Registry(){

    }

    // The registry takes ownership of the factory pointer
    // an will release memory it ~Registry()
    void Registry::Register(TypeDefinition definition) {

      // Does the type exist in the graph. I.e. does it have a gid
      if(!this->TypeExists(definition.Name)) {
        this->CreateType(definition.Name, definition.Properties);
      }




      // do we alread have a factory registered for this type? If so
      // release the current factory and assign the new one





    }




    bool Registry::TypeExists(std::string name) {
      graph::tx::Transaction tx;
      if(this->m_graph->Read(tx)) {

      } else {
        std::cout << "[REGISTRY] Error - failed to read graph." << std::endl;
        return false;
      }
    }

    gid Registry::CreateType(std::string name, std::vector<TypeProperty> properties) {

    }




  }
}

