#ifndef LINE_H
#define LINE_H

#include "vector.h"

namespace num {


  class Line{
    public:
      Line() : A(0,0), B(0,0) {};
      Line(Vector a, Vector b) : A(a), B(b) {};
      Vector A;
      Vector B;
      double Length() { return this->A.DistanceTo(this->B); }


      Vector Midpoint();
  };

}

#endif // LINE_H
