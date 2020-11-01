#ifndef IDACCUMULATOR_H
#define IDACCUMULATOR_H
#include <types.h>

namespace graph {

  class IdAccumulator {
    public:
      IdAccumulator() {}
      virtual ~IdAccumulator() {}
      virtual void Reclaim(aid id) = 0;
      virtual void SetCounter(aid count) = 0;
  };

}
#endif // IDACCUMULATOR_H
