#ifndef PLANET_H
#define PLANET_H

#include <graph/storeable.h>
#include <graph/entity.h>
#include <graph/type/base.h>
#include <graph/type/buffer.h>
#include <graph/type/registry.h>

namespace nature {
  namespace planet {

    graph::Storeable* PlanetFactory(graph::type::gid id, graph::type::ByteBuffer *buffer);
    graph::type::ClassDefinition PlanetDefinition();

    class Planet : public graph::Entity{
      public:
        Planet() : graph::Entity() {};
        Planet(graph::type::gid id) : Entity(id) {};
        Planet(graph::type::gid id, graph::type::ByteBuffer *buffer) : Entity(id, buffer) {};
        virtual graph::Storeable::Concept GetConcept() { return graph::Storeable::Concept::EntityConcept; }
    };


  }

}


#endif // PLANET_H
