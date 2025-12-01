#include <iostream>

#include <fstream>

#include <vector>

#include <string>

#include <chrono>

#include "nlohmann/json.hpp" // Include the JSON library (nlohmann/json)

#include "search_algorithms.h"

#include "sort_algorithms.h"

using json = nlohmann::json;

std::vector<Book> load_books(const std::string &filename) {

  std::ifstream file(filename);

  json booksJson;

  file >> booksJson;

  std::vector<Book> books;

  for (const auto &book : booksJson) {

    std::string title = book["title"].get<std::string>();

    double rating = book.contains("rating") ? book["rating"].get<double>() : 0;

    books.push_back({title, rating});
  }

  return books;
}

void display_books(const std::vector<Book> &books, int count = 20) {

  for (int i = 0; i < std::min(count, static_cast<int>(books.size())); ++i) {

    std::cout << books[i].title << " (Rating: " << books[i].rating << ")\n";
  }
}

int main() {

  // Load dataset

  std::vector<Book> books = load_books("data/books.json");

  // Extract sorted titles for binary search

  std::vector<std::string> sorted_titles;

  for (const auto &book : books) {

    sorted_titles.push_back(book.title);
  }

  // Binary search prompt

  std::cout << "\n---- Chapter 1: Binary Search ----" << std::endl;

  std::cout << "Enter the title of the book you want to search for: ";

  std::string book_to_search;   

  std::getline(std::cin, book_to_search);

  // Measure the time taken for the search

  auto start_search_time = std::chrono::high_resolution_clock::now();

  int index = binary_search(sorted_titles, book_to_search);

  auto end_search_time = std::chrono::high_resolution_clock::now();

  std::chrono::duration<double> search_time_taken =
      end_search_time - start_search_time;

  if (index != -1) {

    std::cout << "Book '" << book_to_search << "' found at index " << index
              << "." << std::endl;

  } else {

    std::cout << "Book '" << book_to_search << "' not found." << std::endl;
  }

  std::cout << "Search took " << search_time_taken.count() << " seconds."
            << std::endl;

  // Display first 20 books before sorting by rating

  std::cout << "\n---- Displaying the first 20 books before sorting ----"
            << std::endl;

  display_books(books, 20);

  // Prompt user to sort book titles using selection sort by rating

  std::cout << "\n---- Chapter 2: Selection Sort by Rating ----" << std::endl;

  auto start_sort_time = std::chrono::high_resolution_clock::now();

  selection_sort(books);

  auto end_sort_time = std::chrono::high_resolution_clock::now();

  std::chrono::duration<double> sort_time_taken =
      end_sort_time - start_sort_time;

  std::cout << "Books sorted by rating using selection sort." << std::endl;

  std::cout << "Sorting took " << sort_time_taken.count() << " seconds."
            << std::endl;

  // Display first 20 books after sorting by rating

  std::cout << "\n---- Displaying the first 20 books after sorting ----"
            << std::endl;

  display_books(books, 20);

  return 0;
}