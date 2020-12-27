#include "renderer.h"

#include <QSize>
#include <QImage>
#include <QFont>

#include <string>
#include <iostream>

namespace map {

  void Renderer::Render(std::string filename, num::Rect bounds, Map *map) {
    QSize size(bounds.Width, bounds.Height);
    QImage *image = new QImage(size, QImage::Format_RGB32);
    QPainter *painter = new QPainter(image);

    painter->setRenderHint(QPainter::Antialiasing);
    painter->fillRect(0,0,size.width(),size.height(),QBrush(Qt::white));

    QFont font("Arial",8);;
    painter->setFont(font);


    QBrush brushRed(Qt::red);
    QBrush brushBlue(Qt::blue);
    QBrush brushBlack(Qt::black);
    QBrush brushTransparent(Qt::transparent);

    QPen penRed(brushRed, 2);
    QPen penBlue(brushBlue,0.5);
    QPen penBlack(brushBlack,0.5);
    //QPen penBlack(brushBlack)


    painter->setBrush(brushRed);
    painter->setPen(penRed);

    for(auto& c : map->Centers) {
      painter->drawEllipse(c->P->Location.X, c->P->Location.Y, 3,3);
    }

    painter->setBrush(brushBlue);
    painter->setPen(penBlue);
    for(auto& p : map->Points) {
      painter->drawEllipse(p->Location.X, p->Location.Y, 1,1);
    }




    image->save(QString(filename.c_str()),  "PNG");

    delete painter;
    delete image;
  }


  //void MapRenderer::Render(std::string filename, num::Rect bounds ,std::vector<TriangleMeshNode *> nodes) {
   // bool renderText = false;
/*
    QSize size(bounds.Width, bounds.Height);
    QImage *image = new QImage(size, QImage::Format_RGB32);
    QPainter *painter = new QPainter(image);

    painter->setRenderHint(QPainter::Antialiasing);
    painter->fillRect(0,0,size.width(),size.height(),QBrush(Qt::white));

    QFont font("Arial",8);;
    painter->setFont(font);

    //QString s("font test");
    //painter->drawText(100,100,s);

    QBrush brushRed(Qt::red);
    QBrush brushBlue(Qt::blue);
    QBrush brushBlack(Qt::black);
    QBrush brushTransparent(Qt::transparent);

    QPen penRed(brushRed, 2);
    QPen penBlue(brushBlue,0.5);
    QPen penBlack(brushBlack,0.5);
    //QPen penBlack(brushBlack)


    painter->setBrush(brushTransparent);
    painter->setPen(penBlue);

    for(auto &node : nodes) {
      painter->setPen(penBlue);
      QPointF a(node->Position.X, node->Position.Y);
      for(auto &neighbour : node->TriangleMeshNode()) {
        QPointF b(neighbour->Position.X, neighbour->Position.Y);
        painter->drawLine(a,b);
      }
    }



    // loop second time and draw arrows
    painter->setPen(penRed);
    painter->setBrush(brushRed);
    for(auto &node : nodes) {
      TriangleMeshNode *lowest = 0x0;
      for(auto &neighbour : node->TriangleMeshNode()) {
        if(neighbour->Height < node->Height) {
          if(lowest == 0x0) {
            lowest = neighbour;
          } else {
            if(neighbour->Height < lowest->Height) {
              lowest = neighbour;
            }
          }
        }
      }

      if(lowest != 0x0) {
        //num::Vector v1, v2;

        num::Line l(node->Position,lowest->Position);
        num::Vector mid = l.Midpoint();

        QPointF pm(mid.X, mid.Y);
        QPointF pl(lowest->Position.X, lowest->Position.Y);
        //mid.Arrow(node->Position, v1, v2);


        painter->drawLine(pm, pl);





        //node->Position.Arrow(lowest->Position,v1, v2);
        //painter->setPen(penRed);
        //painter->setBrush(brushRed);

//        QPointF p1(v1.X, v1.Y);
//        QPointF p2(v2.X, v2.Y);


//        painter->drawEllipse(pm, 10,10);

//        QPointF points[3] = {p1,p2,pm};
//        painter->drawPolygon(points,3);

        //painter->drawLine(p1,p2);
      }
    }


    // loop third time write text
    if(renderText) {
      painter->setPen(penBlack);
      painter->setBrush(brushTransparent);
      for(auto &node : nodes) {
        QPointF a(node->Position.X, node->Position.Y);
        painter->setPen(penBlack);
        std::string txt = std::to_string(node->Height);
        QString qtxt(txt.c_str());
        painter->drawText(a,qtxt);
      }
    }


    image->save(QString(filename.c_str()),  "PNG");

    delete painter;
    delete image;
    */
  //}







/*
  void MapRenderer::Render(std::string filename,
                     num::Rect bounds,
                     double sampleOffset,
                     std::vector<std::size_t> const &triangles,
                     std::vector<double> const &coords) {

 //void GeoRenderer::Render(std::string filename, num::Rect bounds, geometry g) {
    double sampleSymbolSize = 0.75;
    double sampleOffsetSize = sampleOffset;

    QSize size(bounds.Width, bounds.Height);

    // create the image
    QImage *image = new QImage(size, QImage::Format_RGB32);
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

    // save the image
    image->save(QString(filename.c_str()),  "PNG");

    // clean up
    delete  painter;
    delete image;

  }

*/




}
