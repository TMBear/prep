///////////////////////////////////////////////////////////////////////////////
// https://www.hackerrank.com/challenges/components-in-graph/problem
// 

#include <iostream>
#include <set>
#include <vector>
#include <limits>
#include <algorithm>

using Component = std::set<int>;

std::vector<Component*> g_vertices;

// Ensures there's a component a vertice refers to. Simple lazy create optimization
void ensureComponent(int v) {
  if (g_vertices[v])
    return;

  g_vertices[v] = new Component();
  g_vertices[v]->insert(v);
}


void moveVertices(const Component* from, Component* to) {
  for (int v : *from)
    g_vertices[v] = to;

  to->insert(from->begin(), from->end());
}



std::pair<int, int> componentsInGraph(const std::vector<std::vector<int>>& gb) {
  g_vertices.resize(2 * gb.size(), nullptr);

  for (const auto& edge : gb) {
    auto v1 = edge[0];
    auto v2 = edge[1];
    ensureComponent(v1);
    ensureComponent(v2);

    Component* c1 = g_vertices[edge[0]];
    Component* c2 = g_vertices[edge[1]];

    if (c1 == c2) {
      continue;
    }

    Component* biggerComp = c1->size() > c2->size() ? c1 : c2;
    Component* smallerComp = biggerComp == c1 ? c2 : c1;

    moveVertices(smallerComp, biggerComp);
    delete smallerComp;
  }

  int high = std::numeric_limits<int>::min();
  int low = std::numeric_limits<int>::max();
  for (const auto comp : g_vertices) {
    if (!comp)
      continue;

    high = std::max(high, (int)comp->size());
    low = std::min(low, (int)comp->size());
  }

  return std::make_pair(low, high);
}


void connectedComponents() {
  std::vector<std::vector<int>> edges = {
    {1, 6}, 
    {2, 7},
    {3, 8},
    {4, 9},
    {2, 6}
  };

  auto result = componentsInGraph(edges);

  std::cout << result.first << " " << result.second << std::endl;
}

