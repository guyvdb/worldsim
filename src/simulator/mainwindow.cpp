#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include <filesystem>
#include <string>

#define GRAPHDIR "/home/guy/Projects/worldsim/data/graph"
#define LOGDIR "/home/guy/Projects/worldsim/data/log"


#include <entity.h>
#include <relation.h>

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

graph::Graph *MainWindow::CreateGraph() {
  //Configure
  graph::Config config(std::string(GRAPHDIR), std::string(LOGDIR));
  // Create
  graph::Graph *g = new graph::Graph(config);

  // Open
  if(!g->Open()) {
    std::cout << "Error - failed to open the graph" << std::endl;
    delete g;
    return 0x0;
  }

  return g;
}

void MainWindow::on_pushButton_clicked() {
  graph::Graph *g = this->CreateGraph();
  if(g == 0x0) return ;


  graph::Transaction tx;
  if(g->Update(tx)){
    graph::Entity *e1 = tx.CreateEntity(1343);
    std::cout << "ENTITY ID=" << e1->GetGraphId() << "\n";

    graph::Entity *e2 = tx.CreateEntity(145);
    std::cout << "ENTITY ID=" << e2->GetGraphId() << "\n";

    graph::Relation *r = e1->CreateRelation(e2, 675);

    tx.Commit();
    g->Flush();
  }


    // Close & Dispose
  g->Close();
  delete g;

}

void MainWindow::on_pushButton_2_clicked() {
    graph::Graph *g = this->CreateGraph();
    if(g == 0x0) return;

    graph::Transaction tx;
    if(g->Read(tx)) {
      graph::Entity *e1 = tx.FindEntityById(1);
      std::cout << "ENTITY ID=" << e1->GetGraphId() << std::endl;
      std::cout << "OutRelId=" << e1->GetRootOutRelationId() << std::endl;
      std::cout << "typeid=" << e1->GetTypeId() << std::endl;
      std::cout << std::endl;

      graph::Relation *r = tx.FindRelationById(e1->GetRootOutRelationId());
      std::cout << "RELATION ID=" << r->GetGraphId() << std::endl;
      std::cout << "ToEntityId=" << r->GetToEntityId() << std::endl;
      std::cout << "typeid=" << r->GetTypeId() << std::endl;
      std::cout << std::endl;


      graph::Entity *e2 = tx.FindEntityById(r->GetToEntityId());
      std::cout << "ENTITY ID=" << e2->GetGraphId() << std::endl;
      std::cout << "typeid=" << e2->GetTypeId() << std::endl;
      std::cout << std::endl;
    }

    g->Close();
    delete g;
}

