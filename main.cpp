#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <nlohmann/json.hpp>
#include "search_algorithms.h"
#include "sort_algorithms.h"
#include "merge_sort.h"
#include "quick_sort.h"
#include "hash_table.h"

using json = nlohmann::json;

std::vector<Book> load_books(const std::string& filename) {
    std::ifstream file(filename);
    json booksJson;
    file >> booksJson;

    std::vector<Book> books;
    for (const auto& book : booksJson) {
        std::string title = book["title"].get<std::string>();
        double rating = book.contains("rating") ? book["rating"].get<double>() : 0;
        books.push_back({title, rating});
    }
    return books;
}

void display_books(const std::vector<Book>& books, int count = 20) {
    for (int i = 0; i < std::min(count, static_cast<int>(books.size())); ++i) {
        std::cout << books[i].title << " (Rating: " << books[i].rating << ")\n";
    }
}
int main() {
    std::vector<Book> books = load_books("data/books.json");

    std::vector<std::string> sorted_titles;
    for (const auto& book : books) {
        sorted_titles.push_back(book.title);
    }

    // Chapter 1: Binary Search
    std::cout << "\n---- Chapter 1: Binary Search ----\n";
    std::cout << "Enter the title of the book you want to search for: ";
    std::string book_to_search;
    std::getline(std::cin, book_to_search);

    auto start_search_time = std::chrono::high_resolution_clock::now();
    int index = binary_search(sorted_titles, book_to_search);
    auto end_search_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> search_time_taken = end_search_time - start_search_time;

    if (index != -1) {
        std::cout << "Book '" << book_to_search << "' found at index " << index << ".\n";
    } else {
        std::cout << "Book '" << book_to_search << "' not found.\n";
    }
    std::cout << "Search took " << search_time_taken.count() << " seconds.\n";
    std::cout << "\n---- First 20 books before sorting ----\n";
    display_books(books, 20);

    // Chapter 2: Selection Sort
    std::cout << "\n---- Chapter 2: Selection Sort by Rating ----\n";
    auto start_sort_time = std::chrono::high_resolution_clock::now();
    selection_sort(books);
    auto end_sort_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> sort_time_taken = end_sort_time - start_sort_time;

    std::cout << "Books sorted by rating using selection sort.\n";
    std::cout << "Sorting took " << sort_time_taken.count() << " seconds.\n";

    std::cout << "\n---- First 20 books after selection sort ----\n";
    display_books(books, 20);

    // Chapter 3: Merge Sort
    std::vector<Book> top_books(books.begin(), books.begin() + 100);

    std::cout << "\n---- First 20 books before merge sort ----\n";
    display_books(top_books, 20);

    std::cout << "\n---- Chapter 3: Merge Sort by Rating ----\n";
    start_sort_time = std::chrono::high_resolution_clock::now();
    merge_sort(top_books);
    end_sort_time = std::chrono::high_resolution_clock::now();
    sort_time_taken = end_sort_time - start_sort_time;

    std::cout << "Books sorted by rating using merge sort.\n";
    std::cout << "Sorting took " << sort_time_taken.count() << " seconds.\n";

    std::cout << "\n---- First 20 books after merge sort ----\n";
    display_books(top_books, 20);
    // Chapter 4: Quick Sort
    top_books = std::vector<Book>(books.begin(), books.begin() + 100);

    std::cout << "\n---- First 20 books before quick sort ----\n";
    display_books(top_books, 20);

    std::cout << "\n---- Chapter 4: Quick Sort by Rating ----\n";
    start_sort_time = std::chrono::high_resolution_clock::now();
    quick_sort(top_books);
    end_sort_time = std::chrono::high_resolution_clock::now();
    sort_time_taken = end_sort_time - start_sort_time;

    std::cout << "Books sorted by rating using quick sort.\n";
    std::cout << "Sorting took " << sort_time_taken.count() << " seconds.\n";

    std::cout << "\n---- First 20 books after quick sort ----\n";
    display_books(top_books, 20);
    // Chapter 5: Hash Tables
    std::cout << "\n---- Chapter 5: Hash Tables ----\n";
    HashTable hash_table;

    for (const auto& book : books) {
        hash_table.insert(book.title, book.rating);
    }

    std::string book_title = "Partials";
    auto start_lookup_time = std::chrono::high_resolution_clock::now();
    double rating = hash_table.get(book_title);
    auto end_lookup_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> lookup_time_taken = end_lookup_time - start_lookup_time;

    if (rating != -1) {
        std::cout << "Rating for book '" << book_title << "' is " << rating << ".\n";
    } else {
        std::cout << "Book '" << book_title << "' not found in hash table.\n";
    }
    std::cout << "Lookup took " << lookup_time_taken.count() << " seconds.\n";

    return 0;
}
