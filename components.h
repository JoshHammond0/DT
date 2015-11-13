#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <vector>
#include <string>

struct node{
  std::string name = "";
  int x = 0;
  int y = 0;
};

struct edge{
  std::string to = "";
  std::string from = "";
  double length = 0;
};

#endif
