#ifndef WORLD_H
#define WORLD_H

#include <QObject>
#include <QQuickItem>

class World : public QObject
{
    Q_OBJECT
  public:
    explicit World(QObject *parent = nullptr);

    Q_INVOKABLE void hello();
  signals:

};

#endif // WORLD_H
