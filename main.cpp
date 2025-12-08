#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "greedy_algorithm.h"
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
  // Demonstrate Greedy Algorithm
  std::cout
      << "\n---- Chapter 10: Greedy Algorithm - Book Selection Problem ----"
      << std::endl;
  std::cout
      << "Selecting books to maximize rating while staying under page limit..."
      << std::endl;
  size_t max_pages = 1000;

  auto selection = greedy_book_selection(books, max_pages);
  std::cout << "\nSelected " << selection.selected_books.size()
            << " books totaling " << selection.total_pages << " pages"
            << std::endl;

  if (!selection.selected_books.empty()) {
    std::cout << "Average rating of selection: "
              << selection.total_rating / selection.selected_books.size()
              << std::endl;
    std::cout << "\nTop 10 selected books:" << std::endl;
    display_books(selection.selected_books, 10);
  } else {
    std::cout << "No books selected.\n";
  }
  return 0;
}