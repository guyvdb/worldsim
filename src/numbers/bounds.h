#ifndef BOUNDS_H
#define BOUNDS_H




namespace num {


  class Bounds {
    public:
      Bounds() : Lower(0), Upper(0) {};
      Bounds(double lower, double upper) : Lower(lower), Upper(upper) {};
      double Lower;
      double Upper;


  };


}
#endif // BOUNDS_H
