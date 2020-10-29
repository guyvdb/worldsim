#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include <filesystem>
#include <string>

#define GRAPHDIR "/home/guy/Projects/worldsim/data/graph"
#define LOGDIR "/home/guy/Projects/worldsim/data/log"

#include <graph.h>

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  this->setFixedWidth(300);
}

MainWindow::~MainWindow()
{
  delete ui;
}


void MainWindow::on_pushButton_clicked() {
    std::cout << "Create Graph" << std::endl;


    graph::Config config(std::string(GRAPHDIR), std::string(LOGDIR));
    std::cout << "Config Created" << std::endl;

    graph::Graph *g = new graph::Graph(config);
    std::cout << "Graph Created" << std::endl;

    if(!g->Open()) {
      std::cout << "Error - failed to open the graph" << std::endl;
      delete g;
      return;
    }
    std::cout << "Open" << std::endl;

    graph::Tx *tx = g->Update();
    std::cout << "Create Tx" << std::endl;


    // create 30 things
    for(int i=0;i<30;i++) {

    // the thing belongs to the transaction and will be release on commit or rollback
      graph::Thing *t = tx->NewThing();
      std::cout << "Create Thing" << std::endl;

      tx->Commit();
      std::cout << "Tx.Commit" << std::endl;

    }



    if(!g->Close()) {
      std::cout << "Error - failed to close the graph" << std::endl;
    }
    std::cout << "Close Graph" << std::endl;

    delete g;
    std::cout << "Delete Graph" << std::endl;
}
