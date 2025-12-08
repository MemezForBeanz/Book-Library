#ifndef DEPTH_FIRST_SEARCH_H
#define DEPTH_FIRST_SEARCH_H
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
// Recursive DFS implementation with visited set

bool dfs(const std::unordered_map<std::string, std::vector<std::string>> &graph,
         const std::string &start, const std::string &target,
         std::unordered_set<std::string> &visited) {
  visited.insert(start);
  if (visited.size() <= 10) { // Limit the output
    std::cout << "Visiting node: " << start << std::endl;
  }
  if (start == target) {
    return true;
  }
  if (graph.find(start) != graph.end()) {
    for (const std::string &neighbor : graph.at(start)) {
      if (visited.find(neighbor) == visited.end()) {
        if (dfs(graph, neighbor, target, visited)) {
          return true;
        }
      }
    }
  }
  return false;
}

// Wrapper function to initialize visited set
bool dfs(const std::unordered_map<std::string, std::vector<std::string>> &graph,
         const std::string &start, const std::string &target) {
  std::unordered_set<std::string> visited;
  return dfs(graph, start, target, visited);
}
#endif // DEPTH_FIRST_SEARCH_H