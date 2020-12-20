#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "point.h"
#include "line.h"

namespace num {
  class Triangle {
    public:
      Triangle() : A(0,0), B(0,0), C(0,0) {};
      Triangle(Point a, Point b, Point c) : A(a), B(b), C(c) {};

      //int Id;
      num::Point A;
      num::Point B;
      num::Point C;

      Point Circumcenter();
      Line AB() { return Line(this->A, this->B); }
      Line BC() { return Line(this->B, this->C); }
      Line CA() { return Line(this->C, this->A); }


    private:
      void LineFromPoints(Point P, Point Q, double &a, double &b, double &c);
      void PerpendicularBisectorForLine(Point P, Point Q, double &a, double &b, double &c);
      Point LineLineIntersection(double a1, double b1, double c1, double a2, double b2, double c2);



//      pdd lineLineIntersection(double a1, double b1, double c1,
//                  double a2, double b2, double c2)

//      void perpendicularBisectorFromLine(pdd P, pdd Q,
//              double &a, double &b, double &c)

      //void lineFromPoints(pdd P, pdd Q, double &a,
      //            double &b, double &c)
  };
}

#endif // TRIANGLE_H


//num::Point Circumcenter(num::Triangle t);
//void LineFromPoints(num::Point P, num::Point Q, double &a, double &b, double &c);
