#ifndef CHAIN_H_
#define CHAIN_H_

#include "abstract_graph.h"

class Chain : public AbstractGraph {
 public:
  explicit Chain(const std::vector<std::vector<Edge>>& connections) : AbstractGraph(connections) {}

  explicit Chain(int n) {
    n_ = n;
    connections_.resize(n_);
    for (int i = 0; i < n - 1; ++i) {
        Edge edge(i, i + 1, 1);
        connections_[i].push_back(edge);
    }

    for (int i = 1; i < n; ++i) {
      Edge edge(i, i - 1, 1);
      connections_[i].push_back(edge);
    }
  }

  Chain() : AbstractGraph() {}

  std::vector<Edge> GetAnyPath(int from, int to) override;
};

#endif  // CHAIN_H_
