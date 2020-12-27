#ifndef HEATMAPRENDERER_H
#define HEATMAPRENDERER_H


#include <vector>
#include <string>
#include <numbers/rect.h>


namespace map {



  class HeatMapRenderer {
    public:

      // values: vector of rows each containing vector of columns
      static void Render(std::string filename, num::Rect bounds, std::vector<std::vector<float>>& values);
  };
}

#endif // HEATMAPRENDERER_H
