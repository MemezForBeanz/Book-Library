#ifndef DYNAMIC_PROGRAMMING_H
#define DYNAMIC_PROGRAMMING_H
#include "sort_algorithms.h"
#include <algorithm>
#include <cctype>
#include <limits>
#include <string>
#include <vector>
struct LevenshteinResult {
  int distance;
  std::vector<std::vector<int>> matrix;
};
struct SimilarTitlesResult {
  std::string title1;
  std::string title2;
  double normalized_distance;
  std::vector<std::vector<int>> matrix;
};
inline LevenshteinResult levenshtein_distance(const std::string &s1,
                                              const std::string &s2) {
  int m = s1.length();
  int n = s2.length();
  std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));
  // Initialize first row and column
  for (int i = 0; i <= m; i++) {
    dp[i][0] = i;
  }
  for (int j = 0; j <= n; j++) {
    dp[0][j] = j;
  }
  // Fill dp table
  for (int i = 1; i <= m; i++) {
    for (int j = 1; j <= n; j++) {
      if (s1[i - 1] == s2[j - 1]) {
        dp[i][j] = dp[i - 1][j - 1]; // No operation needed
      } else {
        dp[i][j] = std::min({
            dp[i - 1][j] + 1,    // deletion
            dp[i][j - 1] + 1,    // insertion
            dp[i - 1][j - 1] + 1 // substitution
        });
      }
    }
  }
  return {dp[m][n], dp};
}
inline SimilarTitlesResult find_similar_titles(const std::vector<Book> &books, size_t sample_size = 100) {
  double min_distance = std::numeric_limits<double>::infinity();
  SimilarTitlesResult result;
  size_t limit = std::min(books.size(), sample_size);
  for (size_t i = 0; i < limit; i++) {
    for (size_t j = i + 1; j < limit; j++) {
      std::string title1 = books[i].title;
      std::string title2 = books[j].title;
      // Convert to lowercase for comparison
      std::transform(title1.begin(), title1.end(), title1.begin(), ::tolower);
      std::transform(title2.begin(), title2.end(), title2.begin(), ::tolower);
      auto max_len = std::max(title1.length(), title2.length());
      if (max_len == 0) {
        continue;
      }

      auto [distance, matrix] = levenshtein_distance(title1, title2);
      double normalized_distance = static_cast<double>(distance) / max_len;
      if (normalized_distance < min_distance) {
        min_distance = normalized_distance;
        result = {books[i].title, books[j].title, normalized_distance, matrix};
      }
    }
  }
  return result;
}
#endif // DYNAMIC_PROGRAMMING_H