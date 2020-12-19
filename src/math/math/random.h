#ifndef RANDOM_H
#define RANDOM_H

#include <random>

#include "point.h"
#include "rect.h"

namespace math {  
  class Random {
    public:
      Random(unsigned long seed);
      double Normal(double mean, double stddev);
      Point UniformPoint(Rect& bounds);
      double UniformReal(Bounds& bounds);
      int UniformInt(int min, int max);
      std::default_random_engine* Engine() { return &this->m_generator; }
    private:
      std::default_random_engine m_generator;
  };
}


#endif // RANDOM_H
