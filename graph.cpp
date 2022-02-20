#include "graph.h"

Graph::Graph(std::vector<std::vector<Edge>> connections) {
  connections_ = connections;
  for (auto edges_from_cur_node : connections) {
    for (auto edges : edges_from_cur_node) {
      n_ = std::max(n_, edges.to);
    }
  }
}

Graph::Graph(int n) {
  n_ = n;
  for (int first_node = 0; first_node < n; ++first_node) {
    for (int second_node = 0; second_node < n; ++second_node) {
      if (first_node != second_node) {
        connections_[first_node].push_back(Edge(second_node, 1));
      }
    }
  }
}

int Graph::GetEdgeLength(int from, int to)
{
  for (auto edge : connections_[from]) {
    if (edge.to == to) {
      return edge.length;
    }
  }
  return 0;
}

const std::vector<Graph::Edge>& Graph::GetEdges(int from) {
  return connections_[from];
}

int Graph::GetSize() {
  return n_;
}

bool Graph::DFS(int from, int to,
                std::vector<Graph::Edge>& result_path,
                std::vector<bool>& used) {
  used[from] = true;
  for (auto edge : connections_[from]) {
    if (edge.to == to) {
      result_path.push_back(edge);
      return true;
    } else if (!used[edge.to]){
      result_path.push_back(edge);
      if (DFS(edge.to, to, result_path, used)) {
        return true;
      } else {
        result_path.pop_back();
      }
    }
  }
  used[from] = false;
}


std::vector<Graph::Edge> Graph::GetAnyPath(int from, int to) {
  std::vector<Edge> result_path;
  std::vector<bool> used(n_, false);
  DFS(from, to, result_path, used);
  return result_path;
}

std::vector<Graph::Edge> Graph::GetShortestPath(int from, int to) {

}

std::vector<Graph::Edge> Graph::GetShortestPaths(int from) {
}