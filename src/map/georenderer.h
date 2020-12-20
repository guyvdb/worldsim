#ifndef GEORENDERER_H
#define GEORENDERER_H

#include <string>
#include <vector>
#include <numbers/rect.h>
#include <numbers/triangle.h>
namespace map {

  /*
  struct geometry {
    double SampleOffsetSize;
    std::vector<double> *Samples;
    std::vector<std::size_t> *Triangles;
    std::vector<double> const& Coords;
    std::vector<std::size_t> *HalfEdges;
  };
  */

  class GeoRenderer {
    public:
      static void Render(std::string filename,
                         num::Rect bounds,
                         double sampleOfset,
                         std::vector<std::size_t> const &triangles,
                         std::vector<double> const &coords
                         );
  };

}

#endif // GEORENDERER_H
