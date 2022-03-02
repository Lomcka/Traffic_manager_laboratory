#include "chain.h"
#include "graph.h"
#include "clique.h"
#include <gtest/gtest.h>

std::vector<std::vector<Graph::Edge>> edges = {
    {Graph::Edge(1, 5)}, // 0
    {Graph::Edge(0, 5), Graph::Edge(2, 3)}, // 1
    {Graph::Edge(1, 3), Graph::Edge(3, 10)}, // 2
    {Graph::Edge(2, 10)}  // 3
};

TEST(Chain, Simple) {
  std::vector<std::vector<Chain::Edge>> c = {
      {Chain::Edge(1, 2)}, // 0
      {Chain::Edge{2, 3}, Chain::Edge(0, 2)}, // 1
      {Chain::Edge(3, 5), Chain::Edge(1, 3)}, // 2
      {Chain::Edge(2, 3)} // 3
  };

  Chain a(c);
  ASSERT_EQ(a.GetSize(), 4);

  std::vector<Chain::Edge> expected = {
      {Chain::Edge(1, 2)},
      {Chain::Edge(2, 3)}
  };

//  for (auto x : a.GetAnyPath(0, 2)) {
//    std::cout << x.to << " " << x.length << '\n';
//  }
}

TEST(Graph, Simple) {
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

TEST(Clique, Simple) {
  Clique graph1(5);

  EXPECT_EQ(graph1.GetEdgeLength(0, 3), 1);
  EXPECT_EQ(graph1.GetEdgeLength(3, 2), 1);
  EXPECT_EQ(graph1.GetEdgeLength(1, 3), 1);
}