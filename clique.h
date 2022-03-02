#ifndef CLIQUE_H_
#define CLIQUE_H_

#include "abstract_graph.h"

class Clique : public AbstractGraph {
 public:
    explicit Clique(int n) : AbstractGraph(n) {}
    explicit Clique(std::vector<std::vector<Edge>> connections)
    : AbstractGraph(connections) {}
    Clique() : AbstractGraph() {}

    std::vector<Edge> GetAnyPath(int from, int to) override;
};

#endif  // CLIQUE_H_
