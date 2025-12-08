#ifndef GREEDY_ALGORITHM_H
#define GREEDY_ALGORITHM_H
#include "sort_algorithms.h"
#include <algorithm>
#include <vector>

struct BookSelection {
  std::vector<Book> selected_books;
  double total_rating;
  size_t total_pages;
};

inline BookSelection greedy_book_selection(const std::vector<Book> &books,
                                           size_t max_pages) {
  std::vector<std::pair<double, const Book *>> book_values;
  size_t limit = std::min(books.size(), size_t(100));
  
  for (size_t i = 0; i < limit; ++i) {
    double pages =
        200; // Assuming each book has roughly 200 pages for demonstration
    book_values.push_back({books[i].rating / pages, &books[i]});
  }

  std::sort(book_values.begin(), book_values.end(),
            [](const auto &a, const auto &b) { return a.first > b.first; });

  BookSelection result;
  result.total_pages = 0;
  result.total_rating = 0;
  for (const auto &[value, book] : book_values) {
    size_t book_pages = 200; // Same assumption as above
    if (result.total_pages + book_pages <= max_pages) {
      result.selected_books.push_back(*book);
      result.total_pages += book_pages;
      result.total_rating += book->rating;
    }
  }

  return result;
}
#endif // GREEDY_ALGORITHM_H