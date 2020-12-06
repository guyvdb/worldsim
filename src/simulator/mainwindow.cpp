#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include <filesystem>
#include <string>

#define GRAPHDIR "/home/guy/Projects/worldsim/data/graph"
#define LOGDIR "/home/guy/Projects/worldsim/data/log"

#include <graph.h>
#include <entity.h>

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
  //Configure
  graph::Config config(std::string(GRAPHDIR), std::string(LOGDIR));
  // Create
  graph::Graph *g = new graph::Graph(config);

  // Open
  if(!g->Open()) {
    std::cout << "Error - failed to open the graph" << std::endl;
    delete g;
    return;
  }


  graph::Transaction tx;
  if(g->Update(tx)){
    graph::Entity *e1 = tx.CreateEntity(1);
    std::cout << "ENTITY ID=" << e1->GetGraphId() << "\n";

    graph::Entity *e2 = tx.CreateEntity(1);
    std::cout << "ENTITY ID=" << e2->GetGraphId() << "\n";

    graph::Relation *r = e1->CreateRelation(e2, 1);



    tx.Commit();
  }


    // Close & Dispose
    g->Close();    
    delete g;

}
