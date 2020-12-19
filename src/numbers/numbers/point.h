#ifndef POINT_H
#define POINT_H

namespace num {
  class Point {
    public:
      Point() : X(0), Y(0) {};
      Point(double x, double y) : X(x), Y(y) {};
      double X;
      double Y;
  };
}


#endif // POINT_H
