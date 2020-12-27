#ifndef POINT_H
#define POINT_H

namespace num {

  class Polar {
    public:
      Polar() : Length(0), Angle(0) {}
      Polar(double len, double angle) : Length(len), Angle(angle) {}
      double Length;
      double Angle;
  };

/*
         /|
        / |
     d /  | v
      / a |
     /-----
       h

  d = distance
  v = verticle
  h = horizontal
  a = angle

               v
  sine(a)   = ---
               d

               h
  cosine(a) = ---
               d

*/
  class Vector {
    public:

      static Vector FromPolar(Polar p);
      static double DegToRad(double angle);

      Vector() : X(0), Y(0) {};
      Vector(double x, double y) : X(x), Y(y) {};
      double X;
      double Y;

      Polar ToPolar();
      double DistanceTo(Vector to);
      double Length();
      Vector operator+(Vector v);
      Vector operator-(Vector v);
      Vector operator*(double scalar);
      Vector operator/(double scalar);

      void Arrow(Vector from, Vector &v1, Vector &v2); // this must come out of here
  };
}




#endif // POINT_H
