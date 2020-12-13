#ifndef REGISTRY_H
#define REGISTRY_H

#include <type/base.h>
#include <store/storemanager.h>
#include <store/scanner.h>
#include <store/store.h>
#include <storeable.h>
#include <buffer.h>
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
     *       virtual ~Decoder() {}
      virtual Storeable *Decode(type::gid id, ByteBuffer *buffer) = 0;
      virtual Storeable *Empty() = 0;
      virtual bool Decodeable() = 0;
      */


    class TypeFactory {
        virtual Storeable *CreateType() = 0;
        virtual Storeable *CreateType(gid id, ByteBuffer *buffer) = 0;
        virtual std::string TypeName() = 0;
    };

    struct TypeProperty {
        std::string Name;
        stid TypeId;
        bool Required;
    };

    struct TypeDefinition {
        std::string Name;
        Storeable::Concept Concept;
        TypeFactory *Factory;
        std::vector<TypeProperty> Properties;
    };



    // The registry allows applications to register
    // pre-defined types with the type system
    class Registry : public store::Scanner {
      public:
        Registry(graph::Graph *g, store::StoreManager *storeManager);
        virtual ~Registry() {};
        virtual void Scan(type::gid id, bool active, ByteBuffer *data, std::size_t len) override;
        void RegisterType(TypeDefinition definition);
        void IndexTypeName(type::gid id, std::string name);
        bool Open();
        bool Close();
        bool TypeExists(std::string name);
        type::gid GetTypeId(std::string name);
      private:
        bool FactoryExists(std::string name);

        gid CreateType(Storeable::Concept concept, std::string name, std::vector<TypeProperty> properties);
        //gid TypeNameToId(std::string name);
        std::map<std::string, gid> m_nameIndex;
        std::map<gid, TypeFactory*> m_factories;
        graph::Graph *m_graph;
        store::Store *m_typeStore;
    };


  }
}


#endif // REGISTRY_H
