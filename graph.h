#ifndef GRAPH_H_
#define GRAPH_H_

#include "abstract_graph.h"

class Graph : public AbstractGraph {
 public:
  explicit Graph(const std::vector<std::vector<Edge>>& connections)
  : AbstractGraph(connections) {}

  explicit Graph(int n) : AbstractGraph(n) {}

  Graph() : AbstractGraph() {}

  std::vector<Edge> GetAnyPath(int from, int to) override;
};

#endif  // GRAPH_H_
