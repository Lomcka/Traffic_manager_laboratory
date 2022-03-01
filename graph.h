#ifndef GRAPH_H_
#define GRAPH_H_

#include <set>
#include <vector>
#include <algorithm>

class Graph {
 public:
  struct Edge {
    Edge() = default;
    Edge(int to, int length) : to(to), length(length) {}
    Edge(int from, int to, int length) : from(from), to(to), length(length) {}
    bool operator<(const Edge& edge) const {
      return length < edge.length;
    }
    bool operator==(const Edge& edge) const {
      return (to == edge.to && length == edge.length);
    }
    int from{0};
    int to{0};
    int length{0};
  };

  Graph() = default;
  Graph(const std::vector<std::vector<Edge>>& connections);
  Graph(int n);

  int GetEdgeLength(int from, int to);
  const std::vector<Edge>& GetEdges(int from);
  int GetSize() const;

  std::vector<Edge> GetAnyPath(int from, int to);

  std::vector<Edge> GetShortestPath(int from, int to);
  std::vector<std::vector<Edge>> GetShortestPaths(int from);


 private:
  int n_{0};
  std::vector<std::vector<Edge>> connections_;
  bool DFS(int from, int to,
           std::vector<Graph::Edge>& result_path,
           std::vector<bool>& used);
  std::vector<Edge> Dijkstra(int from);
  std::vector<Edge> FindWay(int from, int to,
                            std::vector<Edge>& from_what_node);
};

#endif  // GRAPH_H_
