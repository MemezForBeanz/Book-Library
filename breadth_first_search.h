#ifndef BREADTH_FIRST_SEARCH_H
#define BREADTH_FIRST_SEARCH_H
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

bool bfs(const std::unordered_map<std::string, std::vector<std::string>> &graph,
         const std::string &start, const std::string &target) {

  std::unordered_set<std::string> visited;
  std::queue<std::string> queue;
  visited.insert(start);
  queue.push(start);

  while (!queue.empty()) {

    std::string node = queue.front();
    queue.pop();

    if (visited.size() <= 10) { // Limit the output
      std::cout << "Visiting node: " << node << std::endl;
    }

    if (node == target) {
      return true;
    }

    if (graph.find(node) != graph.end()) {
      for (const std::string &neighbor : graph.at(node)) {
        if (visited.find(neighbor) == visited.end()) {
          visited.insert(neighbor);
          queue.push(neighbor);
        }
      }
    }
  }

  return false;
}
#endif // BREADTH_FIRST_SEARCH_H