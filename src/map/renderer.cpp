#include "georenderer.h"

#include <QSize>
#include <QImage>
#include <QPainter>

namespace map {


  void GeoRenderer::Render(std::string filename,
                     num::Rect bounds,
                     double sampleOffset,
                     std::vector<std::size_t> const &triangles,
                     std::vector<double> const &coords) {

 //void GeoRenderer::Render(std::string filename, num::Rect bounds, geometry g) {
    double sampleSymbolSize = 0.75;
    double sampleOffsetSize = sampleOffset;

    QSize size(bounds.Width, bounds.Height);

    // create the image
    QImage *image = new QImage(size, QImage::Format_ARGB32);
    QPainter *painter = new QPainter(image);
    painter->setRenderHint(QPainter::Antialiasing);
    painter->fillRect(0,0,size.width(),size.height(),QBrush(Qt::white));

    // set up brush and pen
    QBrush brushRed(Qt::red);
    QBrush brushBlue(Qt::blue);
    QBrush brushGreen(Qt::green);
    QBrush brushTransparent(Qt::transparent);
    QBrush brushGray(Qt::gray);

    QBrush brushYellow(Qt::yellow);
    QBrush brushCyan(Qt::cyan);

    QPen penRed(brushRed, 0.5);
    QPen penBlue(brushBlue,0.5);
    QPen penYellow(brushYellow, 0.5);
    QPen penCyan(brushCyan, 0.5);

    QPen penGreen(brushGreen, 1);
    QPen penGray(brushGray,0.5, Qt::PenStyle::DashLine);


    // print the triangles
    painter->setBrush(brushTransparent);
    painter->setPen(penBlue);

    for(std::size_t i=0; i < triangles.size(); i += 3) {
      double ax, ay, bx, by, cx, cy;
      ax = coords[2 * triangles[i]];
      ay = coords[2 * triangles[i] + 1];
      bx = coords[2 * triangles[i+1]];
      by = coords[2 * triangles[i+1] + 1];
      cx = coords[2 * triangles[i+2]];
      cy = coords[2 * triangles[i+2] + 1];
      QPointF a(ax, ay);
      QPointF b(bx, by);
      QPointF c(cx, cy);

      painter->drawLine(a,b);
      painter->drawLine(b,c);
      painter->drawLine(c,a);
    }

    // paint the points
    for(std::size_t i=0; i<coords.size(); i += 2){
      QPointF p(coords[i], coords[i+1]);

      // point
      painter->setBrush(brushRed);
      painter->setPen(penRed);
      painter->drawEllipse(p,sampleSymbolSize,sampleSymbolSize);


      //offset
      painter->setBrush(brushTransparent);
      painter->setPen(penGray);
      painter->drawEllipse(p, sampleOffsetSize, sampleOffsetSize);
    }




/*
    for(std::size_t i=0; i< samples.size(); i+=2) {
      QPointF p(samples[i], samples[i+1]);

      painter->setBrush(brushRed);
      painter->setPen(penRed);
      painter->drawEllipse(p,sampleSymbolSize,sampleSymbolSize);


      // outline the point
      painter->setBrush(brushTransparent);
      painter->setPen(penBlue);
      painter->drawEllipse(p, sampleOffsetSize, sampleOffsetSize);
    }

    painter->setBrush(brushTransparent);
    painter->setPen(penGreen);
    for(auto &t : triangles) {
      QPointF a(t.A.X, t.A.Y);
      QPointF b(t.B.X, t.B.Y);
      QPointF c(t.C.X, t.C.Y);

      painter->drawEllipse(a,1,1);
      painter->drawEllipse(b,1,1);
      painter->drawEllipse(c,1,1);

    }
*/

    // save the image
    image->save(QString(filename.c_str()),  "PNG");

    // clean up
    delete  painter;
    delete image;

  }


  /*

    num::Delaunator *d = this->m_delaunator;
    std::vector<std::size_t> triangles = d->triangles;
    std::size_t len = triangles.size() / 3;
    std::vector<num::Triangle> result;
    result.reserve(len);

    for(std::size_t i=0; i < triangles.size(); i += 3) {
      double ax, ay, bx, by, cx, cy;


      ax = d->coords[2 * triangles[i]];
      ay = d->coords[2 * triangles[i] + 1];
      bx = d->coords[2 * triangles[i+1]];
      by = d->coords[2 * triangles[i+1] + 1];
      cx = d->coords[2 * triangles[i+2]];
      cy = d->coords[2 * triangles[i+2] + 1];



      result.push_back(num::Triangle(
                         num::Point(ax,ay),
                         num::Point(bx,by),
                         num::Point(cx,cy)
                       ));
    }

    return result;


  */


}
