#include "line.h"


namespace num {

  Vector Line::Midpoint() {
    return Vector((this->A + this->B) / 2);
  }
}


//void midpoint(int x1, int x2,
//                int y1, int y2)
//{
//    cout << (float)(x1+x2)/2 <<
//            " , "<< (float)(y1+y2)/2 ;
//}
