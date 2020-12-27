#ifndef MAPRENDERER_H
#define MAPRENDERER_H

#include <QPainter>

#include <string>
#include <vector>
#include <numbers/vector.h>
#include <numbers/rect.h>
#include <numbers/triangle.h>

#include "map.h"


namespace map {


  class Renderer {
    public:
      void Render(std::string filename, num::Rect bounds, Map *map);
    private:
  };

}

#endif // MAPRENDERER_H
