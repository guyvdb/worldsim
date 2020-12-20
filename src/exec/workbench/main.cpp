#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "bridge.h"
#include "mapcanvas.h"

int main(int argc, char *argv[]) {
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
  QGuiApplication app(argc, argv);


  qmlRegisterType<MapCanvas>("MapCanvas",1,0,"MapCanvas");

  //qmlRegisterType<MapCanvas>("MapCanvas",1,0,"MapCanvas");
  QQmlApplicationEngine engine;
  const QUrl url(QStringLiteral("qrc:/main.qml"));
  QObject::connect(&engine, &QQmlApplicationEngine::objectCreated, &app, [url](QObject *obj, const QUrl &objUrl) {
    if (!obj && url == objUrl)QCoreApplication::exit(-1);
  }, Qt::QueuedConnection);


  Bridge *bridge = new Bridge();
  engine.rootContext()->setContextProperty("bridge",bridge);


  //engine.rootObjects()

//  // add global c++ object to the QML context as a property
//  MyGlobalObject* myGlobal = new MyGlobalObject();
//  myGlobal->doSomething("TEXT FROM C++");
//  engine.rootContext()->setContextProperty("myGlobalObject", myGlobal);



  engine.load(url);

  return app.exec();
}
