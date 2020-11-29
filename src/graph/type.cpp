#include "type.h"

namespace graph {

  Type::Type(gid id) : Storeable(id, Storeable::TypeSize) {

  }

  Type::Type(gid id, std::string name) : Storeable(id, Storeable::TypeSize) {
    // name is fixed length
  }

  Type::Type(gid id, ByteBuffer *buffer) : Storeable(id, buffer) {

  }

  Type::~Type() {

  }

}
