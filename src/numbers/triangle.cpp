#include "triangle.h"


namespace num {

  Point Triangle::Circumcenter() {

    // Line AB is ax + by = c
    double a,b,c;
    this->LineFromPoints(this->A, this->B, a, b, c);


    // Line BC is ex + fy = c
    double e,f,g;
    this->LineFromPoints(this->B,this->C, e, f, g);

    // Convert lines AB and BC to perpendicular
    // vbisectors. After this L = ax + by = c
    // M = ex + fy = g
    this->PerpendicularBisectorForLine(this->A, this->B, a, b, c);
    this->PerpendicularBisectorForLine(this->B, this->C, e, f, g);


    return this->LineLineIntersection(a,b,c,e,f,g);
  }

  void Triangle::LineFromPoints(Point P, Point Q, double &a, double &b, double &c){
    a = Q.Y - P.Y;
    b = P.X - Q.X;
    c = a * (P.X) + b * (P.Y);
  }


  void Triangle::PerpendicularBisectorForLine(Point P, Point Q, double &a, double &b, double &c){
    Point mid((P.X + Q.X) / 2, (P.Y + Q.Y) / 2);
    // c = -bc + ay
    c = -b * (mid.X) + a * (mid.Y);

    double t = a;
    a = -b;
    b = t;
  }



  Point Triangle::LineLineIntersection(double a1, double b1, double c1, double a2, double b2, double c2){
    double determinant = a1 * b2 - a2 * b1;
    double x = (b2 * c1 - b1 * c2) / determinant;
    double y = (a1 * c2 - a2 * c1) / determinant;
    return Point(x,y);
  }

  /*

  // Returns the intersection point of two lines
  pdd lineLineIntersection(double a1, double b1, double c1,
              double a2, double b2, double c2)
  {
    double determinant = a1*b2 - a2*b1;
    if (determinant == 0)
    {
      // The lines are parallel. This is simplified
      // by returning a pair of FLT_MAX
      return make_pair(FLT_MAX, FLT_MAX);
    }

    else
    {
      double x = (b2*c1 - b1*c2)/determinant;
      double y = (a1*c2 - a2*c1)/determinant;
      return make_pair(x, y);
    }
  }


  */


  /*

  // C++ program to find the CIRCUMCENTER of a
  // triangle
  #include <iostream>
  #include <cfloat>
  using namespace std;

  // This pair is used to store the X and Y
  // coordinate of a point respectively
  #define pdd pair<double, double>

  // Function to find the line given two points
  void lineFromPoints(pdd P, pdd Q, double &a,
              double &b, double &c)
  {
    a = Q.second - P.second;
    b = P.first - Q.first;
    c = a*(P.first)+ b*(P.second);
  }

  // Function which converts the input line to its
  // perpendicular bisector. It also inputs the points
  // whose mid-point lies on the bisector
  void perpendicularBisectorFromLine(pdd P, pdd Q,
          double &a, double &b, double &c)
  {
    pdd mid_point = make_pair((P.first + Q.first)/2,
                (P.second + Q.second)/2);

    // c = -bx + ay
    c = -b*(mid_point.first) + a*(mid_point.second);

    double temp = a;
    a = -b;
    b = temp;
  }

  // Returns the intersection point of two lines
  pdd lineLineIntersection(double a1, double b1, double c1,
              double a2, double b2, double c2)
  {
    double determinant = a1*b2 - a2*b1;
    if (determinant == 0)
    {
      // The lines are parallel. This is simplified
      // by returning a pair of FLT_MAX
      return make_pair(FLT_MAX, FLT_MAX);
    }

    else
    {
      double x = (b2*c1 - b1*c2)/determinant;
      double y = (a1*c2 - a2*c1)/determinant;
      return make_pair(x, y);
    }
  }

  void findCircumCenter(pdd P, pdd Q, pdd R)
  {
    // Line PQ is represented as ax + by = c
    double a, b, c;
    lineFromPoints(P, Q, a, b, c);

    // Line QR is represented as ex + fy = g
    double e, f, g;
    lineFromPoints(Q, R, e, f, g);

    // Converting lines PQ and QR to perpendicular
    // vbisectors. After this, L = ax + by = c
    // M = ex + fy = g
    perpendicularBisectorFromLine(P, Q, a, b, c);
    perpendicularBisectorFromLine(Q, R, e, f, g);

    // The point of intersection of L and M gives
    // the circumcenter
    pdd circumcenter =
      lineLineIntersection(a, b, c, e, f, g);

    if (circumcenter.first == FLT_MAX &&
      circumcenter.second == FLT_MAX)
    {
      cout << "The two perpendicular bisectors "
          "found come parallel" << endl;
      cout << "Thus, the given points do not form "
          "a triangle and are collinear" << endl;
    }

    else
    {
      cout << "The circumcenter of the triangle PQR is: ";
      cout << "(" << circumcenter.first << ", "
        << circumcenter.second << ")" << endl;
    }
  }

  // Driver code.
  int main()
  {
    pdd P = make_pair(6, 0);
    pdd Q = make_pair(0, 0);
    pdd R = make_pair(0, 8);
    findCircumCenter(P, Q, R);
    return 0;
  }



    */

}
