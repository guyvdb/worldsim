
#include <iostream>
#include <string>
#include <random>
#include <chrono>



#include <numbers/random.h>
#include <numbers/point.h>
#include <numbers/rect.h>

//#include <map/planetgenerator.h>
#include <map/geogenerator.h>

int main() {

  num::Random g(std::chrono::system_clock::now().time_since_epoch().count());

  // Planet
//  map::PlanetGeneratorConfig cfg = map::DefaultPlanetGeneratorConfig(&g);
//  map::PlanetGenerator *generator = new map::PlanetGenerator(cfg);
//  generator->Generate();
//  delete generator;


  // Geo
  map::GeoConfig cfg = map::DefaultGeoConfig(&g);
  map::GeoGenerator *generator = new map::GeoGenerator(cfg);
  generator->Generate("/home/guy/Projects/worldsim/image2.png");
  delete generator;


  std::cout << "complete" << std::endl;

  return 0;
}
