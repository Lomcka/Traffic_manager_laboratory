#include "traffic_manager.h"
#include <chrono>
#include <gtest/gtest.h>

TEST(Manager, GettersAndSetters) {
  Clique a(5);
  std::vector<int> buns = {1, 2, 3, 4, 5};
  std::vector<int> vehicles = {1, 1, 1, 1, 1};
  TrafficManager m(a, buns, vehicles, 1);
  ASSERT_EQ(m.GetTotalBunsAmount(), 15);
  m.SetBunsAmountInCity(0, 6);
  ASSERT_EQ(m.GetTotalBunsAmount(), 20);
  ASSERT_EQ(m.GetVehiclesAmountInCity(2), 1);
  buns[0] = 6;
  ASSERT_EQ(m.GetBunsAmounts(), buns);
}

TEST(Manager, Transport) {
  Clique a(5);
  std::vector<int> buns = {1, 2, 3, 4, 5};
  std::vector<int> vehicles = {1, 1, 1, 1, 1};
  TrafficManager m(a, buns, vehicles, 1);
  ASSERT_EQ(m.MoveVehicles(0, 2, 1), 1);
  ASSERT_EQ(m.GetVehiclesAmountInCity(2), 2);
//  ASSERT_EQ(m.Transport(4, 0, 5), 2);
//  ASSERT_EQ(m.GetBunsAmountInCity(0), 6);
}

TEST(Manager, Tricky) {
  std::vector<std::vector<Graph::Edge>> edges = {
      {Graph::Edge(1, 5)},
      {Graph::Edge(0, 5), Graph::Edge(2, 3)},
      {Graph::Edge(1, 3), Graph::Edge(3, 10)},
      {Graph::Edge(2, 10)}
  };

  std::vector<int> buns = {1, 2, 30, 4};
  std::vector<int> vehicles = {1, 1, 1, 1};
  Chain a(edges);
  TrafficManager m(a, buns, vehicles, 1);
 // ASSERT_EQ(m.Transport(2, 3, 3), 18);
}

TEST(Manager, Time) {
  Clique a(100);
  Chain b(100);

  std::vector<int> buns(100, 100);
  std::vector<int> vehicles(100, 2);

  TrafficManager first(a, buns, vehicles, 1);
  TrafficManager second(b, buns, vehicles, 1);

  auto start = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < 50'000; ++i) {
    first.Transport(i % 100, (i + 1) % 100, 50);
  }
  auto finish = std::chrono::high_resolution_clock::now();

  std::chrono::duration<double> duration = finish - start;
  std::cout << "Clique graph work time " << duration.count() << std::endl;

  start = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < 50'000; ++i) {
    second.Transport(i % 100, (i + 1) % 100, 50);
  }
  finish = std::chrono::high_resolution_clock::now();

  duration = finish - start;
  std::cout << "Chain graph work time " << duration.count() << std::endl;
}

