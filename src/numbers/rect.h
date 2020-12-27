#ifndef SIZE_H
#define SIZE_H

#include "vector.h"
#include "bounds.h"


namespace num {


  class Rect {
    public:
      Rect() : Top(0), Left(0), Width(0), Height(0) {};
      Rect(double top, double left, double width, double height) : Top(top), Left(left), Width(width), Height(height) {};
      Rect(Vector topleft, Vector bottomright);

      Bounds XBounds();
      Bounds YBounds();


      double Top;
      double Left;
      double Width;
      double Height;
  };

}
#endif // SIZE_H
