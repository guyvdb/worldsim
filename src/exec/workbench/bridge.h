#ifndef WORLD_H
#define WORLD_H

#include <QObject>
#include <QQuickItem>
//#include <map/planetgenerator.h>

class Bridge : public QObject
{
    Q_OBJECT
  public:
    explicit Bridge(QObject *parent = nullptr);

    Q_INVOKABLE void hello();
    Q_INVOKABLE void render();
    Q_INVOKABLE void buildMap();

    bool haveMap();

  signals:

  private:
   // map::PlanetGenerator *m_planetGenerator;
};

#endif // WORLD_H
