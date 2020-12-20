#ifndef FACTORY_H
#define FACTORY_H

#include "../storeable.h"
#include "base.h"
#include "buffer.h"

namespace graph {
  namespace type {

    typedef graph::Storeable* (*FactoryFunc)(gid id, ByteBuffer *buffer);
  }
}

#endif // FACTORY_H
