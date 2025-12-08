#ifndef DIJKSTRA_H
#define DIJKSTRA_H
#include "sort_algorithms.h"
#include <algorithm>
#include <limits>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

struct Edge {
  std::string destination;
  double weight;
};

using Graph = std::unordered_map<std::string, std::vector<Edge>>;
inline Graph create_book_graph(const std::vector<Book> &books,
                               size_t max_books = 100) {
  Graph graph;
  size_t limit = std::min(books.size(), max_books);
  for (size_t i = 0; i < limit; ++i) {
    for (size_t j = i + 1; j < limit; ++j) {
      double weight = std::abs(books[i].rating - books[j].rating);
      if (weight <= 1.0) { // Connect books with rating difference <= 1.0
        graph[books[i].title].push_back({books[j].title, weight});
        graph[books[j].title].push_back({books[i].title, weight});
      }
    }
  }
  return graph;
}

inline std::pair<std::unordered_map<std::string, double>,
                 std::unordered_map<std::string, std::string>>
dijkstra(const Graph &graph, const std::string &start) {
  std::unordered_map<std::string, double> distances;
  std::unordered_map<std::string, std::string> previous;
  for (const auto &pair : graph) {
    distances[pair.first] = std::numeric_limits<double>::infinity();
  }
  distances[start] = 0.0;
  std::priority_queue<std::pair<double, std::string>,
                      std::vector<std::pair<double, std::string>>,
                      std::greater<>>
      pq;
  pq.push({0.0, start});
  while (!pq.empty()) {
    auto [current_distance, current_node] = pq.top();
    pq.pop();
    if (current_distance > distances[current_node]) {
      continue;
    }
    for (const auto &edge : graph.at(current_node)) {
      double distance = current_distance + edge.weight;
      if (distance < distances[edge.destination]) {
        distances[edge.destination] = distance;
        previous[edge.destination] = current_node;
        pq.push({distance, edge.destination});
      }
    }
  }
  return {distances, previous};
}

inline std::vector<std::string>

find_shortest_path(const std::unordered_map<std::string, std::string> &previous,
                   const std::string &start, const std::string &end) {
  std::vector<std::string> path;
  std::string current = end;
  while (current != "") {
    path.push_back(current);
    auto it = previous.find(current);
    if (it == previous.end()) {
      if (current != start) {
        path.clear(); // No path exists
      }
      break;
    }
    current = it->second;
  }
  std::reverse(path.begin(), path.end());
  return path;
}

#endif // DIJKSTRA_H