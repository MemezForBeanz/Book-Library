#ifndef KNN_ALGORITHM_H
#define KNN_ALGORITHM_H

#include "sort_algorithms.h"

#include <algorithm>
#include <cmath>
#include <string>
#include <vector>

struct BookSimilarity {
  const Book *book;
  double similarity;
};

inline double cosine_similarity(const Book &book1, const Book &book2) {
  // Create feature vectors using rating and normalized page count
  std::vector<double> vec1 = {book1.rating,
                              static_cast<double>(book1.pages) / 1000};
  std::vector<double> vec2 = {book2.rating,
                              static_cast<double>(book2.pages) / 1000};
  // Calculate dot product
  double dot_product = vec1[0] * vec2[0] + vec1[1] * vec2[1];
  // Calculate norms
  double norm1 = std::sqrt(vec1[0] * vec1[0] + vec1[1] * vec1[1]);
  double norm2 = std::sqrt(vec2[0] * vec2[0] + vec2[1] * vec2[1]);
  return (norm1 * norm2 != 0) ? dot_product / (norm1 * norm2) : 0;
}

inline std::vector<BookSimilarity>

find_k_nearest_neighbors(const std::vector<Book> &books,
                         const Book &target_book, size_t k = 5) {
  std::vector<BookSimilarity> similarities;
  for (const auto &book : books) {
    if (book.title != target_book.title) {
      double sim = cosine_similarity(book, target_book);
      similarities.push_back({&book, sim});
    }
  }
  // Sort by similarity in descending order
  std::sort(similarities.begin(), similarities.end(),
            [](const BookSimilarity &a, const BookSimilarity &b) {
              return a.similarity > b.similarity;
            });
  // Return k nearest neighbors
  if (similarities.size() > k) {
    similarities.resize(k);
  }
  return similarities;
}
#endif // KNN_ALGORITHM_H