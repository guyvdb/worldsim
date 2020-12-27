#include "vector.h"


//#include <bits/stdc++.h>
#include <bits/stdc++.h>
#include <math.h>

namespace num {

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  Vector Vector::FromPolar(Polar p) {
    return Vector(p.Length * std::cos(p.Angle), p.Length * std::sin(p.Angle));
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
   // There are 360 degrees in a circle. And that 360 degrees is equivalent to 2*pi radians.
   // So, converting and angle x degrees to radians is 2*pi * (x / 360).
  double Vector::DegToRad(double angle) {
   return 2 * M_PI * (angle / 360);
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  Polar Vector::ToPolar() {
    return Polar(std::atan2(this->X, this->Y), this->Length());
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  double Vector::DistanceTo(Vector to) {
    return std::sqrt(std::pow(to.X - this->X, 2) + std::pow(to.Y - this->Y,2) * 1.0);
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  double Vector::Length() {
    return std::sqrt((this->X * this->X) + (this->Y * this->Y));
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  Vector Vector::operator+(Vector v) {
    return Vector(this->X + v.X, this->Y + v.Y);
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  Vector Vector::operator-(Vector v) {
    return Vector(this->X - v.X, this->Y - v.Y);
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  Vector Vector::operator*(double scalar) {
    return Vector(this->X * scalar, this->Y * scalar);
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  Vector Vector::operator/(double scalar) {
    return Vector(this->X / scalar , this->Y / scalar);
  }

  /* ----------------------------------------------------------------------------------------
   *
   * --------------------------------------------------------------------------------------*/
  void Vector::Arrow(Vector from, Vector &v1, Vector &v2) {

    //centeral line is vector from to this

    // backward directtion
    Vector D = from - *this;

    // length
    double norm = D.Length();

    // normalize
    Vector uD = D / norm;

    double ax = uD.X * std::sqrt(3)/2 - uD.Y * 1/2;
    double ay = uD.X * 1/2 + uD.Y * std::sqrt(3)/2;
    double bx = uD.X * std::sqrt(3)/2 + uD.Y * 1/2;
    double by = - uD.X * 1/2 + uD.Y * std::sqrt(3)/2;

    double l = 20;

    v1 = Vector(from.X + l * ax, from.Y + l * ay);
    v2 = Vector(from.X + l * bx, from.Y + l * by);

  }
  /*

Your central line is vector from (x1,y1) to (x2,y2)
Backward direction vector D = (dx, dy) = (x1-x2, y1-y2)
Length of it: Norm = Sqrt(dx * dx + dy * dy)
Normalize it: uD = (udx, udy) = (dx/Norm, dy/Norm)

To form "wings" of arrow, rotate uD by needed angle. For example,
I use angle Pi/6 with Cos(Pi/6) = Sqrt(3)/2 and Sin(Pi/6) = 1/2

ax = udx * Sqrt(3)/2 - udy * 1/2
ay = udx * 1/2 + udy * Sqrt(3)/2
bx = udx * Sqrt(3)/2 + udy * 1/2
by =  - udx * 1/2 + udy * Sqrt(3)/2
Points for head with wing length L=20:

 (x1 + 20 * ax, y1 + 20 * ay)
and
 (x1 + 20 * bx, y1 + 20 * by)

  */



}



