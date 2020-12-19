#ifndef SIZE_H
#define SIZE_H

#include "point.h"
#include "bounds.h"


namespace math {


  class Rect {
    public:
      Rect() : Top(0), Left(0), Width(0), Height(0) {};
      Rect(double top, double left, double width, double height) : Top(top), Left(left), Width(width), Height(height) {};
      Rect(Point topleft, Point bottomright);

      Bounds XBounds();
      Bounds YBounds();


      double Top;
      double Left;
      double Width;
      double Height;
  };

}
#endif // SIZE_H
