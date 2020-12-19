#include "planetgenerator.h"
#include <iostream>
#include <vector>

#include <math/point.h>
#include <math/bounds.h>
#include <math/delaunator.h>

namespace map {

  PlanetGenerator::PlanetGenerator(PlanetGeneratorConfig& config) {
    this->m_rand = config.RandomNumberGenerator;
    this->m_seedPointCount = config.SeedPointCount;
    this->m_bounds = config.Bounds;
  }


  bool PlanetGenerator::Generate() {

    math::Bounds x = this->m_bounds.XBounds();
    math::Bounds y = this->m_bounds.YBounds();
    std::vector<double> points;
    points.reserve(this->m_seedPointCount * 2);


    std::cout << "PlanetGenerator: start" << std::endl;
    for(int i=0;i<this->m_seedPointCount;i++) {
      points.push_back(this->m_rand->UniformReal(x));
      points.push_back(this->m_rand->UniformReal(y));
    }
    std::cout << "PlanetGenerator: finish adding points. point count=" << points.size() << std::endl;


    math::Delaunator d(points);
    std::cout << "PlanetGenerator: finished triangulating points. triangle count=" << d.triangles.size() << std::endl;



    //std::vector<math::Point> points;
    //points.reserve(this->m_seedPointCount);

    //

    //for(int i=0;i<this->m_seedPointCount;i++) {
      //points.push_back(this->m_rand->UniformPoint(this->m_bounds));
    //}





  }
/*

int main() {
     x0, y0, x1, y1, ... *
    std::vector<double> coords = {-1, 1, 1, 1, 1, -1, -1, -1};

    //triangulation happens here
    delaunator::Delaunator d(coords);

    for(std::size_t i = 0; i < d.triangles.size(); i+=3) {
        printf(
            "Triangle points: [[%f, %f], [%f, %f], [%f, %f]]\n",
            d.coords[2 * d.triangles[i]],        //tx0
            d.coords[2 * d.triangles[i] + 1],    //ty0
            d.coords[2 * d.triangles[i + 1]],    //tx1
            d.coords[2 * d.triangles[i + 1] + 1],//ty1
            d.coords[2 * d.triangles[i + 2]],    //tx2
            d.coords[2 * d.triangles[i + 2] + 1] //ty2
        );
    }
}


  */

}
