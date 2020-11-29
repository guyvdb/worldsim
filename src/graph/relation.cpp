#include "relation.h"

#include <iostream>

namespace graph {



  Relation::Relation(gid id) : Storeable(id) {
    this->m_buf = new ByteBuffer(Storeable::RelationSize);
  }

  Relation::Relation(gid id, ByteBuffer *buffer) : Storeable(id) {
    this->m_buf = new ByteBuffer(buffer);
  }

  Relation::~Relation() {
    delete  this->m_buf;
  }

}
