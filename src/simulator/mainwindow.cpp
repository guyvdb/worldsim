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
    for(int i=0;i<50;i++) {
      graph::Entity *e2 = tx.CreateEntity(145);
       e1->CreateRelation(e2, 675);
    }
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

      // E-1
      graph::Entity *e1 = tx.FindEntityById(1);
      std::cout << "ENTITY ID=" << e1->GetGraphId() << std::endl;
      for(auto r : e1->OutRelations()) {
        std::cout << "E:" << r->From()->GetGraphId() << "-> [R:" << r->GetGraphId() << "] -> E:" << r->To()->GetGraphId() << std::endl;
      }

      std::cout << std::endl;

      // E-2
      graph::Entity *e2 = tx.FindEntityById(2);
      std::cout << "ENTITY ID=" << e2->GetGraphId() << std::endl;
      for(auto r : e2->InRelations()) {
        std::cout << "E:" << r->To()->GetGraphId() << "<- [R:" << r->GetGraphId() << "] <- E:" << r->From()->GetGraphId() << std::endl;
      }

      std::cout << std::endl;

      // E3
      graph::Entity *e3 = tx.FindEntityById(3);
      std::cout << "ENTITY ID=" << e3->GetGraphId() << std::endl;
      for(auto r : e3->InRelations()) {
        std::cout << "E:" << r->To()->GetGraphId() << "<- [R:" << r->GetGraphId() << "] <- E:" << r->From()->GetGraphId() << std::endl;
      }

    }

    g->Close();
    delete g;
}

