#include "graph.h"

std::vector<Graph::Edge> Graph::GetAnyPath(int from, int to) {
  std::vector<Edge> result_path;
  std::vector<bool> used(n_, false);
  DFS(from, to, result_path, used);
  return result_path;
}

