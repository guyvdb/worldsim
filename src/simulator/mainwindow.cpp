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
    graph::Entity *e = tx.CreateEntity();
    std::cout << "ENTITY ID=" << e->GetId() << "\n";
    e->SetFlag(0);
    e->SetInRelId(23);
    e->SetOutRelId(44);
    e->SetPropId(233);

    std::cout << "Flag = " << e->GetFlag() << std::endl;
    std::cout << "InRelId = " << e->InRelId() << std::endl;
    std::cout << "OutRelId = " << e->OutRelId() << std::endl;
    std::cout << "PropId = " << e->PropId() << std::endl;


    graph::Entity *e2 = tx.CopyEntity(e);




    tx.Commit();
  }


  /*
   *   REQUIRE(t1->GetId() == t2->GetId());
  REQUIRE(t1->PropId() == t2->PropId());
  REQUIRE(t1->InRelId() == t2->InRelId());
  REQUIRE(t1->OutRelId() == t2->OutRelId());
  */

  /*
  graph::Transaction tx;
  if(g->Update(tx)) {
    graph::Entity *e = tx.CreateEntity();
    std::cout << "Entity Id: " << e->GetId() << " created\n";
    tx.Commit();
  }
  */

    // Close & Dispose
    g->Close();    
    delete g;

}
