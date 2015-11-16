#include "graph.h"

Graph::Graph()
{
    nodes.resize(0);
    edges.resize(0);
    numberNodes = 0;
}

Graph::~Graph()
{

}

void Graph::addNode(std::string name, double x, double y)
{
    node tmp;
    tmp.name = name;
    tmp.x = x;
    tmp.y = y;
    nodes.push_back(tmp);
    numberNodes++;
}

void Graph::addEdge(std::string startNode, std::string endNode)
{
    if(startNode == endNode) return;

    int startX, startY, endX, endY;
    bool foundStart = false, foundEnd = true;

    for(int i = 0; i < numberNodes; i++)
    {
        if(nodes[i].name == startNode)
        {
            startX = nodes[i].x;
            startY = nodes[i].y;
            foundStart = true;
        }
        if(nodes[i].name == endNode)
        {
            endX = nodes[i].x;
            endY = nodes[i].y;
            foundEnd = true;
        }
    }
    if(foundStart && foundEnd)
    {
        edge tmp;
        tmp.from = startNode;
        tmp.to = endNode;
        tmp.length = sqrt(pow((endX - startX),2) + pow((endY - startY), 2));
        edges.push_back(tmp);
    }
}

std::vector<node> Graph::getNodes(void)
{
    return nodes;
}

std::vector<edge> Graph::getEdges(void)
{
    return edges;
}
