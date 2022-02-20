#ifndef GRAPH_H_
#define GRAPH_H_

#include <set>
#include <vector>

class Graph {
 public:
  struct Edge {
    Edge(int to, int length) : to(to), length(length) {}
    bool operator<(const Edge& edge) const {
      return length < edge.length;
    }
    int to;
    int length;
  };

  Graph() = default;
  Graph(std::vector<std::vector<Edge>> connections);
  Graph(int n);

  int GetEdgeLength(int from, int to);
  const std::vector<Edge>& GetEdges(int from);
  int GetSize();

  bool DFS(int from, int to,
           std::vector<Graph::Edge>& result_path,
           std::vector<bool>& used);
  std::vector<Edge> GetAnyPath(int from, int to);

  std::vector<Edge> GetShortestPath(int from, int to);
  std::vector<Edge> GetShortestPaths(int from);


 private:
  int n_{0};
  std::vector<std::vector<Edge>> connections_;
};

#endif  // GRAPH_H_
