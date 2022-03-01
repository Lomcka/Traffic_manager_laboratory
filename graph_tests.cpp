#include <gtest/gtest.h>
#include "graph.h"

std::vector<std::vector<Graph::Edge>> edges = {
    {Graph::Edge(1, 5)}, // 0
    {Graph::Edge(0, 5), Graph::Edge(2, 3)}, // 1
    {Graph::Edge(1, 3), Graph::Edge(3, 10)}, // 2
    {Graph::Edge(2, 10)}  // 3
};

TEST (Graph, BasicFunctions) {
  Graph graph1(4);
  Graph graph2(edges);

  EXPECT_EQ(graph1.GetSize(), graph2.GetSize());
  EXPECT_EQ(graph1.GetEdgeLength(0, 3), 1);
  EXPECT_EQ(graph1.GetEdgeLength(3, 2), 1);
  EXPECT_EQ(graph1.GetEdgeLength(1, 3), 1);

  EXPECT_EQ(graph2.GetEdgeLength(1, 0), 5);
  EXPECT_EQ(graph2.GetEdgeLength(2, 1), 3);
  EXPECT_EQ(graph2.GetEdgeLength(2, 3), 10);
  EXPECT_EQ(graph2.GetEdgeLength(0, 2), 0);
}

TEST (Graph, Ways) {
  Graph graph1(4);
  Graph graph2(edges);

  std::vector<Graph::Edge> way = {
      Graph::Edge(1, 5), Graph::Edge(2, 3), Graph::Edge(3, 10)
  };

  EXPECT_EQ(graph2.GetAnyPath(0, 3), way);
  EXPECT_EQ(graph2.GetAnyPath(0, 3), graph2.GetShortestPath(0, 3));
  auto shortest_paths = graph2.GetShortestPaths(0);
  EXPECT_EQ(shortest_paths[3], graph2.GetShortestPath(0, 3));
  EXPECT_EQ(shortest_paths[2], graph2.GetShortestPath(0, 2));
  EXPECT_EQ(shortest_paths[1], graph2.GetShortestPath(0, 1));
  EXPECT_EQ(shortest_paths[0], graph2.GetShortestPath(0, 0));
}