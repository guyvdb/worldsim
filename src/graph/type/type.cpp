#include "type.h"


namespace graph {

  namespace type {

    Type::Type(gid id) : Storeable(id, Storeable::TypeSize) {

    }

    Type::Type(gid id, ByteBuffer *buffer) : Storeable(id, buffer) {

    }

  }
}
