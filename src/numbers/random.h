#ifndef RANDOMNUMBERS_H
#define RANDOMNUMBERS_H

#include <random>

#include "point.h"
#include "rect.h"

namespace num {
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


#endif // RANDOMNUMBERS_H
