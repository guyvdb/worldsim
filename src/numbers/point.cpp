#include "point.h"


//#include <bits/stdc++.h>
#include <bits/stdc++.h>

namespace num {


  double Point::Distance(Point to) {
    return std::sqrt(std::pow(to.X - this->X, 2) + std::pow(to.Y - this->Y,2) * 1.0);
  }
}

/*
float distance(int x1, int y1, int x2, int y2)
{
    // Calculating distance
    return sqrt(pow(x2 - x1, 2) +
                pow(y2 - y1, 2) * 1.0);
}
*/

