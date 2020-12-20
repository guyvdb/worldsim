#ifndef MAPCANVAS_H
#define MAPCANVAS_H

#include <QObject>
#include <QQuickPaintedItem>

#include "bridge.h"

class MapCanvas : public QQuickPaintedItem {
    Q_OBJECT
  public:
    explicit MapCanvas(QQuickItem *parent = 0);

    Q_INVOKABLE void redraw();
     void paint(QPainter *painter) override; // Override the method in which the object will be rendered to our


  private:
     Bridge *m_bridge;

};

#endif // MAPCANVAS_H



/*
 QQuickPaintedItem
 */
