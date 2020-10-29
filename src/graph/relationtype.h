#ifndef RELATIONTYPE_H
#define RELATIONTYPE_H

#include <storeable.h>

namespace graph {



  class RelationType : public Storeable {
    public:
      RelationType(gid id);
  };

}

#endif // RELATIONTYPE_H
