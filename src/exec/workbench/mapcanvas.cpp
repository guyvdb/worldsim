#include "mapcanvas.h"
#include <QBrush>
#include <QPen>
#include <QPainter>
#include <iostream>

MapCanvas::MapCanvas(QQuickItem *parent) : QQuickPaintedItem(parent) {
  //this->update();
  this->setSize(QSizeF(300,200));
  this->setVisible(true);
}

void MapCanvas::redraw() {
  std::cout << "redraw was called" << std::endl;
  this->update();
}

void MapCanvas::paint(QPainter *painter) {
  QBrush brush(Qt::green);

  QSizeF size = this->size();
  std::cout << "Paint: width=" << size.width() << ", height=" << size.height() << std::endl;

//  //QPen pen(brush);
//   QSizeF size = this->size();
//   QPointF pos =  this->position();
//   QRectF rect(pos,size);
  painter->setBrush(brush);
  painter->drawRect(2,2,size.width()-4, size.height()-4);

}
