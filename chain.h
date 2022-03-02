#ifndef CHAIN_H_
#define CHAIN_H_

#include "abstract_graph.h"

class Chain : public AbstractGraph {
 public:
  explicit Chain(const std::vector<std::vector<Edge>>& connections) : AbstractGraph(connections) {}

  std::vector<Edge> GetAnyPath(int from, int to) override;
};

#endif  // CHAIN_H_
