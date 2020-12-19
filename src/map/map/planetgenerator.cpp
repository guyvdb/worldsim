#include "planetgenerator.h"
#include <iostream>
#include <vector>

#include <numbers/point.h>
#include <numbers/bounds.h>
#include <numbers/delaunator.h>

namespace map {

  PlanetGenerator::PlanetGenerator(PlanetGeneratorConfig& config) {
    this->m_rand = config.RandomNumberGenerator;
    this->m_seedPointCount = config.SeedPointCount;
    this->m_bounds = config.Bounds;
    this->m_delaunator = 0x0;
  }

  PlanetGenerator::~PlanetGenerator() {
    if (this->m_delaunator != 0x0) {
      delete this->m_delaunator;
    }
  }

  bool PlanetGenerator::Generate() {

    num::Bounds x = this->m_bounds.XBounds();
    num::Bounds y = this->m_bounds.YBounds();
    std::vector<double> points;
    points.reserve(this->m_seedPointCount * 2);


    std::cout << "PlanetGenerator: start" << std::endl;
    for(int i=0;i<this->m_seedPointCount;i++) {
      points.push_back(this->m_rand->UniformReal(x));
      points.push_back(this->m_rand->UniformReal(y));
    }
    std::cout << "PlanetGenerator: finish adding points. point count=" << points.size() << std::endl;


    this->m_delaunator = new num::Delaunator(points);

    std::cout << "PlanetGenerator: finished triangulating points. triangle count=" << this->m_delaunator->triangles.size() << std::endl;
    std::cout << "Hull area = " << this->m_delaunator->get_hull_area() << std::endl;
    return true;
  }


}
