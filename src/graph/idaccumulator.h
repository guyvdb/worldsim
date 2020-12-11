#ifndef IDACCUMULATOR_H
#define IDACCUMULATOR_H
#include <type/base.h>

namespace graph {

  class IdAccumulator {
    public:
      IdAccumulator() {}
      virtual ~IdAccumulator() {}
      virtual void Reclaim(type::gid id) = 0;
      virtual void SetCounter(type::gid count) = 0;
  };

}
#endif // IDACCUMULATOR_H
