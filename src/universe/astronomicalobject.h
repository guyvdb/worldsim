#ifndef ASTRONOMICALOBJECT_H
#define ASTRONOMICALOBJECT_H

#include <entity.h>
#include <type/base.h>
#include <type/buffer.h>

namespace universe {


  class AstronomicalObject : public graph::Entity {
    public:
      AstronomicalObject() : graph::Entity() {}
      AstronomicalObject(graph::type::gid id) : graph::Entity(id) {}
      AstronomicalObject(graph::type::gid id, graph::type::ByteBuffer *buffer) : graph::Entity(id, buffer) {}
  };

}


#endif // ASTRONOMICALOBJECT_H
