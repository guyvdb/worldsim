#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <numbers/random.h>
#include <map/geogenerator.h>
#include <iostream>
//#include <random>
#include <chrono>


MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);
}

MainWindow::~MainWindow()
{
  delete ui;
}


void MainWindow::on_btnDrawMap_clicked()
{
  num::Random g(std::chrono::system_clock::now().time_since_epoch().count());


  // Geo
  map::GeoConfig cfg = map::DefaultGeoConfig(&g);
  map::GeoGenerator *generator = new map::GeoGenerator(cfg);
  generator->Generate("/home/guy/Projects/worldsim/image2.png",0);
  delete generator;

  std::cout << "complete" << std::endl;
  exit(0);
}
