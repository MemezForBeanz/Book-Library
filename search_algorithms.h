#ifndef SEARCH_ALGORITHMS_H
#define SEARCH_ALGORITHMS_H
#include <algorithm>
#include <string>
#include <vector>

int binary_search(const std::vector<std::string> &arr,
                  const std::string &target) {
  int left = 0, right = arr.size() - 1;
  while (left <= right) {
    int mid = (left + right) / 2;
    if (arr[mid] == target) {
      return mid;
    } else if (arr[mid] < target) {
      left = mid + 1;
    } else {
      right = mid - 1;
    }
  }

  return -1;
}

#endif // SEARCH_ALGORITHMS_H