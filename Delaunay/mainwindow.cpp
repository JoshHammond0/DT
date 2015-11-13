#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "graphics_view_zoom.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mainWidget = new QWidget;
    mainLayout = new QVBoxLayout;
    inputPanel = new QHBoxLayout;

    scene = new QGraphicsScene;
    view = new QGraphicsView(scene);
    //hello = new QGraphicsSimpleTextItem("HELLO WORLD!!!!");
    //scene->addItem(hello);

    points.addNode("Hello", 0, 0);
    points.addNode("World!", 100, 100);
    points.addEdge("Hello","World!");

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
        QGraphicsSimpleTextItem *tmpLabel = new QGraphicsSimpleTextItem(QString::fromStdString(graph[i].name));
        tmpEllipse = new QGraphicsEllipseItem(graph[i].x, graph[i].y, 30, 30);
        tmpLabel->setFont(QFont("Comic Sans MS", 5));
        tmpLabel->setPos(graph[i].x + 5, graph[i].y + 10);
        tmpEllipse->setBrush(QBrush(Qt::black));
        graphicsPair myPair = std::make_pair(tmpLabel,tmpEllipse);
        nodeImages.push_back(myPair);
        scene->addItem(tmpEllipse);
        scene->addItem(tmpLabel);
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
        scene->addLine(startX+15,startY+15,endX+15,endY+15, QPen(Qt::black, 6));
    }
}
