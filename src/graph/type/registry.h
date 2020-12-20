#ifndef REGISTRY_H
#define REGISTRY_H

#include "../type/base.h"
#include "../store/storemanager.h"
#include "../store/scanner.h"
#include "../store/store.h"
#include "../storeable.h"
#include "../type/buffer.h"
#include "factory.h"

#include <vector>
#include <map>

namespace graph {

  class Graph;

  namespace type {

    // We can define a type derived from base class entity or relation
    // or one of the subclasses of the two.

    // We can define the properties of our new type

    // We can provide a factory for the generation of our new type



/*
    class ClassFactory {
        virtual Storeable *CreateType() = 0;
        virtual Storeable *CreateType(gid id, ByteBuffer *buffer) = 0;
       // virtual std::string TypeName() = 0;
    };*/

    struct ClassProperty {
        std::string Name;
        type::DataType DataType;
        bool Required;
    };

    struct ClassDefinition {
        std::string Name;
        std::string SuperclassName;
        Storeable::Concept Concept;
        FactoryFunc Factory;
        std::vector<ClassProperty> Properties;
    };



    // The registry allows applications to register
    // pre-defined types with the type system
    class Registry : public store::Scanner {
      public:
        Registry(graph::Graph *g, store::StoreManager *storeManager);
        virtual ~Registry() {};
        virtual void Scan(type::gid id, bool active, ByteBuffer *data, std::size_t len) override;
        void RegisterClass(ClassDefinition definition);
        void IndexTypeName(type::gid id, std::string name);
        bool Open();
        bool Close();
        bool ClassExists(std::string name);
        type::gid GetClassGraphId(std::string name);
      private:
        bool ClassFactoryExists(std::string name);
        gid CreateClass(Storeable::Concept concept, std::string name, std::string superclass, std::vector<ClassProperty> properties);
        std::map<std::string, gid> m_nameIndex;
        std::map<gid, FactoryFunc> m_factories;
        graph::Graph *m_graph;
        store::Store *m_typeStore;
    };


  }
}


#endif // REGISTRY_H
