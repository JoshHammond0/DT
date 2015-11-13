#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QHBoxLayout>
#include "/home/josh/Desktop/Fall 2015/Algorithms/Project/DT/graph.h"
#include <QVBoxLayout>
//#include <QPushButton>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsEllipseItem>
//#include <QLineEdit>
//#include <utility>
//#include <vector>

typedef std::pair<QGraphicsSimpleTextItem*, QGraphicsEllipseItem*> graphicsPair;

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

private:
    Ui::MainWindow *ui;
    QWidget *mainWidget;
    QHBoxLayout *inputPanel;
    QVBoxLayout *mainLayout;
    QGraphicsScene *scene;
    QGraphicsView *view;
    QGraphicsSimpleTextItem *hello;
    Graph points;
    std::vector<graphicsPair> nodeImages;
};

#endif // MAINWINDOW_H
