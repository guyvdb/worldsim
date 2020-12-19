#include "random.h"


namespace math {



    Random::Random(unsigned long seed){
      this->m_generator.seed(seed);
    }

    double Random::Normal(double mean, double stddev) {
      std::normal_distribution<double> dist(mean, stddev);
      return dist(this->m_generator);
    }

    Point Random::UniformPoint(Rect &bounds) {
      Bounds x = bounds.XBounds();
      Bounds y = bounds.YBounds();
      return Point(this->UniformReal(x), this->UniformReal(y));
    }

    double Random::UniformReal(Bounds &bounds) {
      std::uniform_real_distribution<double> dist(bounds.Lower, bounds.Upper);
      return dist(this->m_generator);
    }

    int Random::UniformInt(int min, int max) {
      std::uniform_int_distribution dist(min, max);
      return dist(this->m_generator);
    }



}

