#ifndef QUICK_SORT_H
#define QUICK_SORT_H
#include "sort_algorithms.h"
#include <iostream>
#include <string>
#include <vector>

int quicksort_recursion_depth = 0;
void quick_sort_recursive(std::vector<Book> &books, int low, int high);
int partition(std::vector<Book> &books, int low, int high);

void quick_sort(std::vector<Book> &books) {
  quicksort_recursion_depth = 0;
  quicksort_recursion_depth = 0;
  quick_sort_recursive(books, 0, books.size() - 1);
}

void quick_sort_recursive(std::vector<Book> &books, int low, int high) {
  if (low < high) {
    int partition_index = partition(books, low, high);
    quicksort_recursion_depth++;
    if (quicksort_recursion_depth <= 5) {
      std::cout << "Recursion depth " << quicksort_recursion_depth
                << ": Partitioned at index " << partition_index
                << " with pivot " << books[partition_index].rating << " ["
                << low << ", " << high << "]\n";
    }
    quick_sort_recursive(books, low, partition_index - 1);
    quick_sort_recursive(books, partition_index + 1, high);
    quicksort_recursion_depth--;
  }
}

int partition(std::vector<Book> &books, int low, int high) {
  double pivot = books[high].rating;
  int i = low - 1; // Index of smaller element
  for (int j = low; j < high; j++) {
    if (books[j].rating <= pivot) {
      i++;
      std::swap(books[i], books[j]);
    }
  }
  std::swap(books[i + 1], books[high]);
  return i + 1;
}
#endif // QUICK_SORT_H