#ifndef GENERATOR_H
#define GENERATOR_H

#include <vector>

#include "map.h"

#include <math/random.h>
#include <math/rect.h>

namespace map {


  struct PlanetGeneratorConfig {
    math::Random *RandomNumberGenerator;
    int SeedPointCount;
    math::Rect Bounds;
  };

  PlanetGeneratorConfig DefaultPlanetGeneratorConfig(math::Random *randomNumberGenerator) {
    return PlanetGeneratorConfig {
      .RandomNumberGenerator=randomNumberGenerator,
      .SeedPointCount=1000000,
      .Bounds=math::Rect(0,0,1920,1080)
    };
  }

  class PlanetGenerator {
    public:
      PlanetGenerator(PlanetGeneratorConfig& config);
      bool Generate();
    private:
      math::Random *m_rand;
      int m_seedPointCount;
      math::Rect m_bounds;

  };




}

#endif // GENERATOR_H
