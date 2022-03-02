#include "clique.h"

std::vector<Clique::Edge> Clique::GetAnyPath(int from, int to) {
  std::vector<Edge> result;
  Edge edge(to, GetEdgeLength(from, to));

  result.push_back(edge);
  return result;
}
