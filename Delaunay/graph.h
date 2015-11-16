#ifndef GRAPH_H
#define GRAPH_H

#include "components.h"
#include <math.h>

class Graph
{
  public:
    Graph();
    ~Graph();
    void addNode(std::string name, double x, double y);
    void addEdge(std::string startNode, std::string endNode);
    node findNode(std::string name);
    std::vector<node> getNodes(void);
    std::vector<edge> getEdges(void);

  private:
    std::vector<node> nodes;
    std::vector<edge> edges;
    int numberNodes;
};

#endif
