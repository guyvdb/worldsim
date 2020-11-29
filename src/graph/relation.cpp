#include "relation.h"

#include <iostream>

namespace graph {



  Relation::Relation(gid id) : Storeable(id, Storeable::RelationSize) {
  }

  Relation::Relation(gid id, ByteBuffer *buffer) : Storeable(id, buffer) {
  }

  Relation::~Relation() {
  }

}
