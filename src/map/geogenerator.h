#ifndef GEOGENERATOR_H
#define GEOGENERATOR_H

#include <numbers/random.h>
#include <numbers/triangle.h>
//#include <numbers/delaunator.h>
//#include <numbers/poisson.h>

namespace map {


  struct GeoConfig {
    num::Random *RandomNumberGenerator;
    int SeedPointCount;
    double SeedPointMaxRadius;
    num::Rect Bounds;
  };

  GeoConfig DefaultGeoConfig(num::Random *randomNumberGenerator) {
    return GeoConfig {
      .RandomNumberGenerator=randomNumberGenerator,
      .SeedPointCount=10,
      .SeedPointMaxRadius=8,
      .Bounds=num::Rect(0,0,2000,1000)
    };
  }

  class GeoGenerator {
    public:
      GeoGenerator(GeoConfig &config) : m_config(config) {};
      void Generate(std::string filename);
    private:
      std::vector<double> SamplePoints();
      void CreateNoiseMap();
      //std::vector<double> SamplePointsPoisson();
      //std::vector<double> SamplePointsRandom();
      //std::vector<num::Triangle> Triangulate(std::vector<double> points);

      GeoConfig m_config;
  };


}

#endif // GEOGENERATOR_H
