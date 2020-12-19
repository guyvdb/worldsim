#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <graph/graph.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    graph::Graph *CreateGraph();

  private:
    void recursivePrint(graph::Class *c, std::string indent);
  private slots:
    void on_btnCreateEntityRelation_clicked();
    void on_btnReadEntity_clicked();
    void on_btnCreateClassInheritance_clicked();
    void on_btnReadClassInheritance_clicked();
    void on_btnOpenCloseGraph_clicked();
    void on_btnGenerateMap_clicked();

  private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
