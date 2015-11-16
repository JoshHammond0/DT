#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "graphics_view_zoom.h"
#include <assert.h>
#include <cstdlib>
#include <ctime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QGraphicsEllipseItem *tmpEllipse;
    mainWidget = new QWidget;
    mainLayout = new QVBoxLayout;
    inputPanel = new QHBoxLayout;
    scene = new QGraphicsScene;
    view = new QGraphicsView(scene);
    std::vector<node> nodes;
    std::pair< std::pair<double,double>, double> circumCircle;

    srand(time(NULL));  //  using the time seed from srand explanation

    points.addNode("1", rand()%500, rand()%500);
    points.addNode("2", rand()%500, rand()%500);
    points.addNode("3", rand()%500, rand()%500);

    nodes = points.getNodes();

    points.addEdge(nodes[0].name,nodes[1].name);
    points.addEdge(nodes[1].name,nodes[2].name);
    points.addEdge(nodes[2].name,nodes[0].name);

    circumCircle = findCircumCircle(nodes[0],nodes[1],nodes[2]);

    tmpEllipse = new QGraphicsEllipseItem(circumCircle.first.first+10-circumCircle.second, circumCircle.first.second+10-circumCircle.second,
                                          circumCircle.second*2, circumCircle.second*2);

    tmpEllipse->setPen(QPen(Qt::green));
    circumCircles.push_back(tmpEllipse);

    scene->addItem(tmpEllipse);

    printNodes();
    printEdges();

    Graphics_view_zoom* z = new Graphics_view_zoom(view);
    z->set_modifiers(Qt::NoModifier);

    mainLayout->addWidget(view);
    mainLayout->addLayout(inputPanel);
    mainWidget->setLayout(mainLayout);
    setCentralWidget(mainWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::printNodes()
{
    std::vector<node> graph = points.getNodes();
    for(unsigned int i = 0; i < graph.size(); i++)
    {
        QGraphicsEllipseItem *tmpEllipse;
        tmpEllipse = new QGraphicsEllipseItem(graph[i].x, graph[i].y, 20, 20);
        tmpEllipse->setBrush(QBrush(Qt::black));
        nodeImages.push_back(tmpEllipse);
        scene->addItem(tmpEllipse);
    }
}

void MainWindow::printEdges()
{
    int startX, startY, endX, endY;
    std::vector<node> graph = points.getNodes();
    std::vector<edge> lines = points.getEdges();
    for(unsigned int i = 0; i < lines.size(); i++)
    {
        for(unsigned int j = 0; j < graph.size(); j++)
        {
            if(lines[i].from == graph[j].name)
            {
                startX = graph[j].x;
                startY = graph[j].y;
            }
            if(lines[i].to == graph[j].name)
            {
                endX = graph[j].x;
                endY = graph[j].y;
            }
        }
        scene->addLine(startX+10,startY+10,endX+10,endY+10, QPen(Qt::black, 4));
    }
}

std::pair< std::pair<int,int>, double> MainWindow::findCircumCircle(node n1, node n2, node n3)
{
    /*****Variable Declarations*****/
    std::pair<double, double> mid1, mid2, mid3;
    double slope1, slope2, slope3, constant1, constant2, constant3;
    std::pair< std::pair<double,double>, double> retVal;

    /*****Middle point n1-n2*****/
    mid1.first = (n1.x+n2.x)/2;
    mid1.second = (n1.y+n2.y)/2;
    /*****Middle point n2-n3*****/
    mid2.first = (n2.x+n3.x)/2;
    mid2.second = (n2.y+n3.y)/2;
    /*****Middle point n3-n1*****/
    mid3.first = (n3.x+n1.x)/2;
    mid3.second = (n3.y+n1.y)/2;

    /*****Slope n1-n2*****/
    if(n2.x-n1.x != 0)
    {
        slope1 = (n2.y-n1.y)/(n2.x-n1.x);
        slope1 = -1/slope1;
    }
    else
    {
        slope1 = 0;
    }
    /*****Slope n2-n3*****/
    if(n3.x-n2.x != 0)
    {
        slope2 =  (n3.y-n2.y)/(n3.x-n2.x);
        slope2 = -1/slope2;
    }
    else
    {
        slope2 = 0;
    }
    /*****Slope n3-n1*****/
    if(n1.x-n3.x != 0)
    {
        slope3 =  (n1.y-n3.y)/(n1.x-n3.x);
        slope3 = -1/slope3;
    }
    else
    {
        slope3 = 0;
    }

    /*****Constant n1-n2*****/
    constant1 = mid1.second - slope1 * mid1.first;
    /*****Constant n2-n3*****/
    constant2 = mid2.second - slope2 * mid2.first;
    /*****Constant n3-n1*****/
    constant3 = mid3.second - slope3 * mid3.first;

    /*****Intersection*****/
    retVal.first.first = (constant1-constant2)/(slope2-slope1);
    retVal.first.second = retVal.first.first * slope1 + constant1;

    /*****Max used for threshold*****/
    double tmp, max = std::max(n1.x,n1.y);
    if(max < (tmp = std::max(n2.x,n2.y)))
    {
        max = tmp;
    }
    if(max < (tmp = std::max(n3.x,n3.y)))
    {
        max = tmp;
    }

    /*****Assert all equations have the same point*****/
    assert(abs(constant1 + (slope1*retVal.first.first) - retVal.first.second) < max*.01);
    assert(abs(constant2 + (slope2*retVal.first.first) - retVal.first.second) < max*.01);
    assert(abs(constant3 + (slope3*retVal.first.first) - retVal.first.second) < max*.01);

    /*****Radius*****/
    retVal.second = sqrt(pow(((retVal.first.first - n3.x)),2) + pow(((retVal.first.second - n3.y)), 2));

    return retVal;
}
