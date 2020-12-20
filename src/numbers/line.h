#ifndef LINE_H
#define LINE_H

#include "point.h"

namespace num {


  class Line{
    public:
      Line() : A(0,0), B(0,0) {};
      Line(Point a, Point b) : A(a), B(b) {};
      Point A;
      Point B;
      double Length() { return this->A.Distance(this->B); }
  };

}

#endif // LINE_H
