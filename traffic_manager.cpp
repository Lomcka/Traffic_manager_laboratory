#include <algorithm>
#include <iostream>
#include "traffic_manager.h"

int TrafficManager::GetTotalBunsAmount() {
  int result = 0;
  for (int x : buns_) {
    result += x;
  }

  return result;
}

int TrafficManager::GetTotalVehiclesAmount() {
  int result = 0;
  for (int x : vehicles_) {
    result += x;
  }

  return result;
}

int TrafficManager::GetBunsAmountInCity(int city) {
  return buns_[city];
}

int TrafficManager::GetVehiclesAmountInCity(int city) {
  return vehicles_[city];
}

std::vector<int> TrafficManager::GetBunsAmounts() {
  return buns_;
}

std::vector<int> TrafficManager::GetVehiclesAmounts() {
  return vehicles_;
}

void TrafficManager::SetBunsAmounts(const std::vector<int>& buns) {
  buns_ = buns;
}

void TrafficManager::SetBunsAmountInCity(int city, int buns) {
  buns_[city] = buns;
}

void TrafficManager::SetVehiclesAmounts(const std::vector<int>& vehicles) {
  vehicles_ = vehicles;
}

void TrafficManager::SetVehiclesAmountInCity(int city, int vehicles) {
  vehicles_[city] = vehicles;
}

int TrafficManager::GetShortestPathLength(int from, int to) {
  std::vector<AbstractGraph::Edge> path = country_.GetShortestPath(from, to);

  int result = 0;
  for (auto edge : path) {
    result += edge.length;
  }

  return result;
}

int TrafficManager::MoveVehicles(int from, int to, int count) {
  vehicles_[from] -= count;
  vehicles_[to] += count;

  return GetShortestPathLength(from, to);
}

int TrafficManager::Transport(int from, int to, int buns_amount) {
  buns_[from] -= buns_amount;
  buns_[to] += buns_amount;

  int necessary_vehicles = buns_amount / vehicle_capacity_;
  if (buns_amount % vehicle_capacity_ != 0) {
    ++necessary_vehicles;
  }

  if (necessary_vehicles <= vehicles_[from]) {
    vehicles_[from] -= necessary_vehicles;
    vehicles_[to] += necessary_vehicles;
    return GetShortestPathLength(from, to);
  }


  std::vector<std::pair<int, int>> nearest_city;
  std::vector<std::vector<Graph::Edge>> shortest_ways = country_.GetShortestPaths(from);

  for (int i = 0; i < shortest_ways.size(); ++i) {
    if (i == from) {
      continue;
    }

    int path_length = 0;
    for (int j = 0; j < shortest_ways[i].size(); ++j) {
      path_length += shortest_ways[i][j].length;
    }

    nearest_city.emplace_back(path_length, i);
  }

  std::sort(nearest_city.rbegin(), nearest_city.rend());

  int result = 0;
  int transfer_vehicles = necessary_vehicles - GetVehiclesAmountInCity(from);
  while (transfer_vehicles > 0) {
    int current_city = nearest_city.back().second;
    int available_vehicles = GetVehiclesAmountInCity(current_city);
    if (available_vehicles >= transfer_vehicles) {
      result = nearest_city.back().first;
      TransferVehicles(current_city, from, transfer_vehicles);
      break;
    } else {
      TransferVehicles(current_city, from, available_vehicles);
      transfer_vehicles -= available_vehicles;
    }

    nearest_city.pop_back();
  }

  result += GetShortestPathLength(from, to);
  TransferVehicles(from, to, GetVehiclesAmountInCity(from));
  return result;
}

void TrafficManager::TransferVehicles(int from, int to, int count) {
  vehicles_[from] -= count;
  vehicles_[to] += count;
}


