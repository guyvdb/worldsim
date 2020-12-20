#include "geogenerator.h"

#include <array>
#include <numbers/poisson.h>
#include <numbers/delaunator.h>
#include <numbers/simplexnoise.h>
#include "georenderer.h"

namespace map {



  std::vector<double> GeoGenerator::SamplePoints() {
    // create a sampling of points from blue noise
    auto kxMin = std::array<double,2>{{0,0}};
    auto kxMax = std::array<double,2>{{this->m_config.Bounds.Width,this->m_config.Bounds.Height}};
    const auto samples = num::PoissonDiskSampling(this->m_config.SeedPointMaxRadius, kxMin, kxMax);

    // convert the samples into a vector x0,y0,x1,y1,x2......
    std::vector<double> points;
    points.reserve(samples.size() * 2);
    for(auto &v : samples) {
      points.push_back(v[0]);
      points.push_back(v[1]);

      std::cout << "point(" << v[0] << "," << v[1] << ")" << std::endl;
    }
    return points;
  }


  void GeoGenerator::CreateNoiseMap() {
    //num::Noise noise;
    //double value = noise.eval(0.13, 0.31); // For 2D noise
  }

  void GeoGenerator::Generate(std::string filename) {
    std::vector<double> points = this->SamplePoints();
    delaunator::Delaunator d(points);


    GeoRenderer::Render(filename,this->m_config.Bounds,
                        this->m_config.SeedPointMaxRadius,
                        d.triangles,
                        d.coords);
  }

}
