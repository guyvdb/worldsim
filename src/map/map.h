#ifndef MAP_H
#define MAP_H

#include <vector>
#include "geometry.h"


namespace map {



  class Map {
    public:
      Map();
      ~Map();

      void Add(Center *c) { this->Centers.push_back(c); }
      void Add(Corner *c) { this->Corners.push_back(c); }
      void Add(Edge *e) { this->Edges.push_back(e); }
      void Add(XYPoint *p) { this->Points.push_back(p); }

      std::vector<Center*> Centers;
      std::vector<Corner*> Corners;
      std::vector<Edge*> Edges;
      std::vector<XYPoint*> Points;
  };

}
#endif // MAP_H
