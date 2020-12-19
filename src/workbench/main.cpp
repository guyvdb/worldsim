#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "world.h"


int main(int argc, char *argv[]) {
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
  QGuiApplication app(argc, argv);

  QQmlApplicationEngine engine;
  const QUrl url(QStringLiteral("qrc:/main.qml"));
  QObject::connect(&engine, &QQmlApplicationEngine::objectCreated, &app, [url](QObject *obj, const QUrl &objUrl) {
    if (!obj && url == objUrl)QCoreApplication::exit(-1);
  }, Qt::QueuedConnection);


  World *world = new World();
  engine.rootContext()->setContextProperty("world",world);


  //engine.rootObjects()

//  // add global c++ object to the QML context as a property
//  MyGlobalObject* myGlobal = new MyGlobalObject();
//  myGlobal->doSomething("TEXT FROM C++");
//  engine.rootContext()->setContextProperty("myGlobalObject", myGlobal);



  engine.load(url);

  return app.exec();
}
