#ifndef SPECIES_H
#define SPECIES_H

#include <graph/entity.h>
#include <graph/type/base.h>
#include <graph/type/buffer.h>

namespace nature {



  class Species : public graph::Entity {
    public:
      Species():Entity() {};
      Species(graph::type::gid id) : Entity(id) {};
      Species(graph::type::gid id, graph::type::ByteBuffer *buffer) : Entity(id, buffer) {};
  };

}

#endif // SPECIES_H
