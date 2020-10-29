#ifndef GID_H
#define GID_H

#include <types.h>
#include <storeable.h>

namespace graph {
  enum GraphIds : gid {
    NullId = 0x0,
    InvalidId = 0xFFFFFFFF
  };



  class GraphId : public Storeable {

  };

}

#endif // GID_H
