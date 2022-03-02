#ifndef TRAFFIC_MANAGER_H_
#define TRAFFIC_MANAGER_H_

#include <vector>
#include "graph.h"

class TrafficManager {
 public:
  TrafficManager(const Graph& graph,
                  const std::vector<int>& buns_amounts,
                  const std::vector<int>& vehicles,
                  int vehicle_capacity) : country_(graph),
                                          buns_(buns_amounts),
                                          vehicles_(vehicles),
                                          vehicle_capacity_(vehicle_capacity) {}

  int GetTotalBunsAmount();
  int GetBunsAmountInCity(int city);
  std::vector<int> GetBunsAmounts();

  int GetTotalVehiclesAmount();
  int GetVehiclesAmountInCity(int city);
  std::vector<int> GetVehiclesAmounts();

  void SetBunsAmounts(const std::vector<int>& buns);
  void SetBunsAmountInCity(int city, int buns);

  void SetVehiclesAmounts(const std::vector<int>& vehicles);
  void SetVehiclesAmountInCity(int city, int vehicles);

  int MoveVehicles(int from, int to, int count);
  int Transport(int from, int to, int buns_amount);

 private:
  int GetShortestPathLength(int from, int to);
  void TransferVehicles(int from, int to, int count);

  Graph country_;
  std::vector<int> buns_;
  std::vector<int> vehicles_;
  int vehicle_capacity_;
};

#endif  // TRAFFIC_MANAGER_H_
