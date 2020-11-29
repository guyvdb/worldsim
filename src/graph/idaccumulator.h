#ifndef IDACCUMULATOR_H
#define IDACCUMULATOR_H
#include <graph_types.h>

namespace graph {

  class IdAccumulator {
    public:
      IdAccumulator() {}
      virtual ~IdAccumulator() {}
      virtual void Reclaim(gid id) = 0;
      virtual void SetCounter(gid count) = 0;
  };

}
#endif // IDACCUMULATOR_H
