#ifndef ENTITYTYPE_H
#define ENTITYTYPE_H

#include <storeable.h>

namespace graph {


  class EntityType : public Storeable {
    public:
      EntityType(gid id);
  };

}
#endif // ENTITYTYPE_H
