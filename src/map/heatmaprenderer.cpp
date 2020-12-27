#include "heatmaprenderer.h"

#include <QSize>
#include <QImage>
#include <QPainter>

#include "heatmapgradient.h"

namespace map {
  void HeatMapRenderer::Render(std::string filename, num::Rect bounds, std::vector<std::vector<float>>& rows) {
    HeatMapGradient gradient;

    QSize size(bounds.Width, bounds.Height);

    // create the image
    QImage *image = new QImage(size, QImage::Format_RGB32);
    QPainter *painter = new QPainter(image);
    painter->setRenderHint(QPainter::Antialiasing);
    painter->fillRect(0,0,size.width(),size.height(),QBrush(Qt::white));


    for(std::size_t y=0;y<rows.size();y++) {
      std::vector<float>& cols = rows[y];
      for(std::size_t x=0; x<cols.size();x++){
        image->setPixelColor((int)x, (int)y, gradient.GetColor(cols[x]));
      }
    }

    // save the file ....
    image->save(QString(filename.c_str()),  "PNG");

    delete painter;
    delete image;

  }
}
