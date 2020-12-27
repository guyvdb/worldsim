#ifndef GEOGENERATOR_H
#define GEOGENERATOR_H

#include <vector>
#include <map>

#include <numbers/delaunator.h>
#include <numbers/random.h>

#include "spartialindex.h"
#include "geometry.h"
#include "map.h"


namespace map {


  struct GeoConfig {
    num::Random *RandomNumberGenerator;
    //int SeedPointCount;
    double SeedPointMaxRadius;
    num::Rect Bounds;
  };



  GeoConfig DefaultGeoConfig(num::Random *randomNumberGenerator) {
    return GeoConfig {
      .RandomNumberGenerator=randomNumberGenerator,
      //.SeedPointCount=10,
      .SeedPointMaxRadius=6,  // 10 - 100,100 segfault
      .Bounds=num::Rect(0,0,500,250)
    };
  }

  class GeoGenerator {
    public:
      GeoGenerator(GeoConfig &config) : m_config(config){};
      ~GeoGenerator();
      void Generate(std::string filename, long seed);
    private:
      void CreateGraph(delaunator::Delaunator& d);
      void IndexPoints(std::vector<double>& points);
      XYPoint *FindOrCreatePoint(double x, double y);
      Center *FindOrCreateCenter(double x, double y);
      Edge* CreateEdge(double ax, double ay, double bx, double by);
      std::vector<double> SamplePoints();
     // bool ValidTriangle(double ax, double ay, double bx, double by, double cx, double cy);
      GeoConfig m_config;


      SpartialIndex<Center*> m_centerIndex;
      SpartialIndex<XYPoint*> m_pointIndex;
      SpartialIndex<Corner*> m_cornerIndex;

      Map m_map;





  };

  /*
   // These store the graph data
    public var points:Vector.<Point>;  // Only useful during map construction
    public var centers:Vector.<Center>;
    public var corners:Vector.<Corner>;
    public var edges:Vector.<Edge>;
    */
}

#endif // GEOGENERATOR_H
