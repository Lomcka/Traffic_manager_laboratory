#include "graph.h"

Graph::Graph(const std::vector<std::vector<Edge>>& connections) {
  n_ = connections.size();
  connections_.resize(n_);
  for (int cur_node = 0; cur_node < n_; ++cur_node) {
    for (auto edge : connections[cur_node]) {
      edge.from = cur_node;
      connections_[cur_node].push_back(edge);
    }
  }
}

Graph::Graph(int n) {
  n_ = n;
  connections_.resize(n);
  for (int first_node = 0; first_node < n; ++first_node) {
    for (int second_node = 0; second_node < n; ++second_node) {
      if (first_node != second_node) {
        connections_[first_node].push_back(Edge(first_node, second_node, 1));
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

int Graph::GetSize() const {
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


std::vector<Graph::Edge> Graph::FindWay(int from,
                                        int to,
                                        std::vector<Graph::Edge>& path) {
  std::vector<Edge> result;
  int cur_node = to;
  while (cur_node != from) {
    Edge edge = path[cur_node];
    cur_node = edge.from;
    result.push_back(edge);
  }
  reverse(result.begin(), result.end());
  return result;
}

std::vector<Graph::Edge> Graph::Dijkstra(int from) {
  std::vector<Edge> result(n_);
  std::vector<int> dist(n_, kMaxDistance);
  dist[from] = 0;
  std::set<std::pair<int, int>> buf;
  buf.insert(std::make_pair(dist[from], from));
  while (!buf.empty()) {
    int cur_node = buf.begin()->second;
    buf.erase(buf.begin());

    for (auto edge : connections_[cur_node]) {
      if (dist[edge.to] > dist[cur_node] + edge.length) {
        buf.erase(std::make_pair(dist[edge.to], edge.to));
        dist[edge.to] = dist[cur_node] + edge.length;
        buf.insert(std::make_pair(dist[edge.to], edge.to));
        result[edge.to] = edge;
      }
    }
  }
  return result;
}
std::vector<Graph::Edge> Graph::GetShortestPath(int from, int to) {
  std::vector<Edge> path = Dijkstra(from);
  return FindWay(from, to, path);
}
std::vector<std::vector<Graph::Edge>> Graph::GetShortestPaths(int from) {
  std::vector<Edge> path = Dijkstra(from);
  std::vector<std::vector<Edge>> result(n_);
  for (int to = 0; to < n_; ++to) {
    result[to] = FindWay(from, to, path);
  }
  return result;
}
