#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "dynamic_programming.h"
#include "nlohmann/json.hpp" // jsoncpp library for JSON parsing
#include "sort_algorithms.h"
using json = nlohmann::json;

std::vector<Book> load_books(const std::string &filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Failed to open " << filename << "\n";
    return {};
  }

  if (file.peek() == std::ifstream::traits_type::eof()) {
    std::cerr << "File is empty: " << filename << "\n";
    return {};
  }

  json booksJson;
  try {
    file >> booksJson;
  } catch (const std::exception &ex) {
    std::cerr << "Error parsing JSON from " << filename << ": " << ex.what() << "\n";
    return {};
  }

  std::vector<Book> books;
  books.reserve(booksJson.size());
  for (const auto &book : booksJson) {
    std::string title = book.value("title", "");
    if (title.empty()) {
      continue;
    }

    std::string author = book.value("author", "");
    double rating = book.value("rating", 0.0);
    int pages = book.value("pages", 0);
    books.push_back({title, author, rating, pages});
  }
  return books;
}
void display_books(const std::vector<Book> &books, int count) {
  for (int i = 0; i < std::min(count, static_cast<int>(books.size())); ++i) {
    std::cout << books[i].title << " (Rating: " << books[i].rating << ")\n";
  }
}

int main() {
  auto books = load_books("data/books.json");
  if (books.empty()) {
    std::cout << "No books loaded.\n";
    return 0;
  }
  // Demonstrate Dynamic Programming
  std::cout << "\n---- Chapter 11: Dynamic Programming - Title Similarity Analysis ----" << std::endl;
  std::cout << "Finding the most similar book titles using Levenshtein distance...\n"
            << std::endl;
  auto similar = find_similar_titles(books);
  std::cout << "Analyzed first 100 books from the dataset\n" << std::endl;
  std::cout << "Title 1: " << similar.title1 << std::endl;
  std::cout << "Title 2: " << similar.title2 << std::endl;
  std::cout << "Normalized Levenshtein distance: "
            << similar.normalized_distance << std::endl;
  // Display part of the dynamic programming matrix
  std::cout << "\nDynamic Programming Matrix (first 5x5):" << std::endl;
  for (size_t i = 0; i < std::min(size_t(5), similar.matrix.size()); ++i) {
    for (size_t j = 0; j < std::min(size_t(5), similar.matrix[i].size()); ++j) {
      std::cout << similar.matrix[i][j] << " ";
    }
    std::cout << std::endl;
  }

    return 0;
}