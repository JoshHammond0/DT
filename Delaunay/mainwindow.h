#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QHBoxLayout>
#include "graph.h"
#include <QVBoxLayout>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsEllipseItem>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void printNodes();
    void printEdges();
    std::pair< std::pair<int,int>, double> findCircumCircle(node n1, node n2, node n3);

private:
    Ui::MainWindow *ui;
    QWidget *mainWidget;
    QHBoxLayout *inputPanel;
    QVBoxLayout *mainLayout;
    QGraphicsScene *scene;
    QGraphicsView *view;
    std::vector<QGraphicsEllipseItem *> circumCircles;
    std::vector<QGraphicsEllipseItem *> nodeImages;
    Graph points;
};

#endif // MAINWINDOW_H
