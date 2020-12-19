
#include <iostream>
#include <string>
#include <random>
#include <chrono>



#include <numbers/random.h>
#include <numbers/point.h>
#include <numbers/rect.h>

#include <map/planetgenerator.h>

int main() {

  num::Random g(std::chrono::system_clock::now().time_since_epoch().count());

  num::Rect r(1,1,100,100);

  std::cout << "Normal = " << g.Normal(3.0,1.0) << std::endl;
  std::cout << "Uniform = " << g.UniformInt(4,7) << std::endl;

  num::Point p = g.UniformPoint(r);

  std::cout << "Uniform Point = (x:" << p.X << ", y:" << p.Y << ")" << std::endl;


  map::PlanetGeneratorConfig cfg = map::DefaultPlanetGeneratorConfig(&g);
  map::PlanetGenerator *planetGenerator = new map::PlanetGenerator(cfg);

  planetGenerator->Generate();



  return 0;
}
