#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include <filesystem>
#include <string>

#define GRAPHDIR "/home/guy/Projects/worldsim/data/graph"
#define LOGDIR "/home/guy/Projects/worldsim/data/log"


#include <graph/entity.h>
#include <graph/relation.h>
#include <graph/class.h>

#include <map/generator.h>

/* ----------------------------------------------------------------------------------------
 *
 * --------------------------------------------------------------------------------------*/
MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow){
  ui->setupUi(this);
  this->setFixedWidth(300);
}

/* ----------------------------------------------------------------------------------------
 *
 * --------------------------------------------------------------------------------------*/
MainWindow::~MainWindow(){
  delete ui;
}

/* ----------------------------------------------------------------------------------------
 *
 * --------------------------------------------------------------------------------------*/
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

/* ----------------------------------------------------------------------------------------
 *
 * --------------------------------------------------------------------------------------*/
void MainWindow::recursivePrint(graph::Class *c, std::string indent) {
  std::string padding = indent + "  ";

  std::cout << indent << c->GetName() << " -> " << std::endl;

  for(auto &i : c->GetInheritances()) {
    graph::Class *sub = i->GetSubclass();
    if (sub != 0x0) {
      this->recursivePrint(sub, padding);
    }
  }
}

/* ----------------------------------------------------------------------------------------
 *
 * --------------------------------------------------------------------------------------*/
void MainWindow::on_btnReadEntity_clicked() {
  graph::Graph *g = this->CreateGraph();
  if(g == 0x0) return;

  graph::Transaction tx;
  if(g->Read(tx)) {

    // E-1
    graph::Entity *e1 = tx.FindEntity(1);
    std::cout << "ENTITY ID=" << e1->GetGraphId() << std::endl;
    for(auto r : e1->OutRelations()) {
      std::cout << "E:" << r->From()->GetGraphId() << "-> [R:" << r->GetGraphId() << "] -> E:" << r->To()->GetGraphId() << std::endl;
    }

    std::cout << std::endl;

    // E-2
    graph::Entity *e2 = tx.FindEntity(2);
    std::cout << "ENTITY ID=" << e2->GetGraphId() << std::endl;
    for(auto r : e2->InRelations()) {
      std::cout << "E:" << r->To()->GetGraphId() << "<- [R:" << r->GetGraphId() << "] <- E:" << r->From()->GetGraphId() << std::endl;
    }

    std::cout << std::endl;

    // E3
    graph::Entity *e3 = tx.FindEntity(3);
    std::cout << "ENTITY ID=" << e3->GetGraphId() << std::endl;
    for(auto r : e3->InRelations()) {
      std::cout << "E:" << r->To()->GetGraphId() << "<- [R:" << r->GetGraphId() << "] <- E:" << r->From()->GetGraphId() << std::endl;
    }

  }

  g->Close();
  delete g;
}

/* ----------------------------------------------------------------------------------------
 *
 * --------------------------------------------------------------------------------------*/
void MainWindow::on_btnCreateClassInheritance_clicked(){
  graph::Graph *g = this->CreateGraph();
  if(g == 0x0) return;

  graph::Transaction tx;
  if(g->Update(tx)){
    graph::Class *weapon = tx.CreateClass(graph::Storeable::EntityConcept, "Weapon");
    graph::Class *blade = tx.CreateClass(graph::Storeable::EntityConcept, "Blade", weapon);
    graph::Class *bow = tx.CreateClass(graph::Storeable::EntityConcept, "Bow", weapon);

    tx.CreateClass(graph::Storeable::EntityConcept, "CrossBow",bow);
    tx.CreateClass(graph::Storeable::EntityConcept, "LongBow",bow);
    tx.CreateClass(graph::Storeable::EntityConcept, "short-bow",bow);

    tx.CreateClass(graph::Storeable::EntityConcept, "Dagger",blade);
    tx.CreateClass(graph::Storeable::EntityConcept, "StabbingSword",blade);
    tx.CreateClass(graph::Storeable::EntityConcept, "TwoHandedSword",blade);
    tx.CreateClass(graph::Storeable::EntityConcept, "Cleaver",blade);


    tx.Commit();
    g->Flush();
  }

  // Close & Dispose
  g->Close();
  delete g;
}

/* ----------------------------------------------------------------------------------------
 *
 * --------------------------------------------------------------------------------------*/
void MainWindow::on_btnReadClassInheritance_clicked(){
  graph::Graph *g = this->CreateGraph();
  if(g == 0x0) return;

  graph::Transaction tx;
  if(g->Read(tx)) {
    graph::Class *e = tx.FindClass("Entity");
    if(e != 0x0) {
      this->recursivePrint(e,"");
    }
  } else {
    std::cout << "failed to create read transaction" << std::endl;
  }


  // Close & Dispose
  g->Close();
  delete g;

}

/* ----------------------------------------------------------------------------------------
 *
 * --------------------------------------------------------------------------------------*/
void MainWindow::on_btnOpenCloseGraph_clicked(){
  graph::Graph *g = this->CreateGraph();
  if(g == 0x0) return;
  // Close & Dispose
  g->Close();
  delete g;
}

/* ----------------------------------------------------------------------------------------
 *
 * --------------------------------------------------------------------------------------*/
void MainWindow::on_btnCreateEntityRelation_clicked(){
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


void MainWindow::on_btnGenerateMap_clicked() {
  std::cout << "Map Generate Clicked" << std::endl;
  map::Generator gen;

 std::vector<map::geopoint> gpoints = gen.CreateRandomPoints();
 std::vector<double> points = gen.FlattenGeoPoints(gpoints);

}
