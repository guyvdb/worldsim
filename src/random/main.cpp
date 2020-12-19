
#include <iostream>
#include <string>
#include <random>
#include <chrono>



#include <math/random.h>
#include <math/point.h>
#include <math/rect.h>

#include <map/planetgenerator.h>

int main() {

  math::Random g(std::chrono::system_clock::now().time_since_epoch().count());

  math::Rect r(1,1,100,100);

  std::cout << "Normal = " << g.Normal(3.0,1.0) << std::endl;
  std::cout << "Uniform = " << g.UniformInt(4,7) << std::endl;

  math::Point p = g.UniformPoint(r);

  std::cout << "Uniform Point = (x:" << p.X << ", y:" << p.Y << ")" << std::endl;


  map::PlanetGeneratorConfig cfg = map::DefaultPlanetGeneratorConfig(&g);
  map::PlanetGenerator *planetGenerator = new map::PlanetGenerator(cfg);

  planetGenerator->Generate();



  return 0;
}
