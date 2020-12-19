#include "generator.h"
#include <iostream>

namespace map {


  Generator::Generator(){

  }

  std::vector<geopoint> Generator::CreateRandomPoints() {

    /*
    int pointcout = 2^14;


    // Point space is 180°



    std::vector<geopoint> v(len*len);
    for(double lat=0;lat<len;lat++) {
      for(double lon=0;lon<len;lon++) {
        v.push_back(geopoint{lat,lon});
      }
    }
    std::cout << "Created " << v.size() << " geopoints" << std::endl;
    return v;*/
  }

  std::vector<double> Generator::FlattenGeoPoints(std::vector<geopoint> points) {

    std::vector<double> v(points.size()*2);
    for(auto& p : points){
      v.push_back(p.lat);
      v.push_back(p.lon);
    }
    std::cout << "Created " << v.size() << " doubles" << std::endl;

    return v;
  }
}
