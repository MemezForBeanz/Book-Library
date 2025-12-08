#ifndef MERGE_SORT_H
#define MERGE_SORT_H
#include "sort_algorithms.h"
#include <iostream>
#include <string>
#include <vector>

int recursion_depth = 0;

void merge(std::vector<Book> &books, int left, int mid, int right) {
  int n1 = mid - left + 1;
  int n2 = right - mid;
  std::vector<Book> L(n1);
  std::vector<Book> R(n2);
  for (int i = 0; i < n1; ++i)
    L[i] = books[left + i];
  for (int i = 0; i < n2; ++i)
    R[i] = books[mid + 1 + i];
  int i = 0, j = 0, k = left;
  while (i < n1 && j < n2) {
    if (L[i].rating <= R[j].rating) {
      books[k] = L[i];
      i++;
    } else {
      books[k] = R[j];
      j++;
    }
    k++;
  }
  while (i < n1) {
    books[k] = L[i];
    i++;
    k++;
  }
  while (j < n2) {
    books[k] = R[j];
    j++;
    k++;
  }
}
void mergeSortRecursive(std::vector<Book> &books, int left, int right) {
  if (left < right) {
    int mid = left + (right - left) / 2;
    recursion_depth++;
    if (recursion_depth <= 5)
      std::cout << "Recursion depth " << recursion_depth << ": Sorting ["
                << left << ", " << right << "]" << std::endl;
    mergeSortRecursive(books, left, mid);
    mergeSortRecursive(books, mid + 1, right);
    merge(books, left, mid, right);
    if (recursion_depth <= 5)
      std::cout << "After merging depth " << recursion_depth << ": [" << left
                << ", " << right << "]" << std::endl;
    recursion_depth--;
  }
}
void merge_sort(std::vector<Book> &books) {
  mergeSortRecursive(books, 0, books.size() - 1);
}
#endif // MERGE_SORT_H