#ifndef GENERATOR_H
#define GENERATOR_H

#include <vector>

#include "map.h"


namespace map {


  // the map is generated as a set of blocks

  /*

       |-----------------------------|
       |                             |
       |                             |
       |                             |
       |                             |
       |                             |
       |                             |
       |                             |
       |                             |
       |                             |
       |                             |
       |-----------------------------|


       15^4
   */


  struct geopoint {
      double lat;
      double lon;
  };


  class Generator {
    public:

      std::vector <geopoint> CreateRandomPoints();
      std::vector <double> FlattenGeoPoints(std::vector<geopoint> points);


      Generator();
      Map* Generate(long width, long height);
  };




}

#endif // GENERATOR_H
