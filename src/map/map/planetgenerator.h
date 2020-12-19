#ifndef PLANETGENERATOR_H
#define PLANETGENERATOR_H

#include <vector>

#include <numbers/random.h>
#include <numbers/rect.h>
#include <numbers/delaunator.h>

namespace map {


  struct PlanetGeneratorConfig {
    num::Random *RandomNumberGenerator;
    int SeedPointCount;
    num::Rect Bounds;
  };

  PlanetGeneratorConfig DefaultPlanetGeneratorConfig(num::Random *randomNumberGenerator) {
    return PlanetGeneratorConfig {
      .RandomNumberGenerator=randomNumberGenerator,
      .SeedPointCount=1000000,
      .Bounds=num::Rect(0,0,1920,1080)
    };
  }

  class PlanetGenerator {
    public:
      PlanetGenerator(PlanetGeneratorConfig& config);
      ~PlanetGenerator();
      bool Generate();
    private:
      num::Random *m_rand;
      int m_seedPointCount;
      num::Rect m_bounds;
      num::Delaunator *m_delaunator;

  };




}

#endif // PLANETGENERATOR_H
