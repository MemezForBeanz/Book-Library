#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <nlohmann/json.hpp>

#include "breadth_first_search.h"
#include "hash_table.h"
#include "merge_sort.h"
#include "quick_sort.h"
#include "search_algorithms.h"
#include "sort_algorithms.h"

using json = nlohmann::json;

std::vector<Book> load_books(const std::string& filename) {
	std::ifstream file(filename);
	json booksJson;
	file >> booksJson;

	std::vector<Book> books;
	books.reserve(booksJson.size());

	for (const auto& book : booksJson) {
		std::string title = book["title"].get<std::string>();
		std::string author = book["author"].is_string() ? book["author"].get<std::string>() : "";
		double rating = book.contains("rating") ? book["rating"].get<double>() : 0;
		books.push_back({title, author, rating});
	}
	return books;
}

void display_books(const std::vector<Book>& books, int count) {
	for (int i = 0; i < std::min(count, static_cast<int>(books.size())); ++i) {
		std::cout << books[i].title << " (Rating: " << books[i].rating << ")\n";
	}
}

std::unordered_map<std::string, std::vector<std::string>> create_graph_by_author(const std::vector<Book>& books) {
	std::unordered_map<std::string, std::vector<std::string>> graph;
	std::unordered_map<std::string, std::unordered_set<std::string>> author_to_books;

	for (const auto& book : books) {
		if (!book.author.empty()) {
			std::istringstream ss(book.author);
			std::string token;
			while (std::getline(ss, token, ',')) {
				token.erase(0, token.find_first_not_of(' '));
				token.erase(token.find_last_not_of(' ') + 1);
				author_to_books[token].insert(book.title);
			}
		}
	}

	for (const auto& [author, book_set] : author_to_books) {
		(void)author;
		for (const auto& book1 : book_set) {
			for (const auto& book2 : book_set) {
				if (book1 != book2) {
					graph[book1].push_back(book2);
				}
			}
		}
	}

	return graph;
}

int main() {
	std::vector<Book> books = load_books("data/books.json");

	std::vector<std::string> sorted_titles;
	sorted_titles.reserve(books.size());
	for (const auto& book : books) {
		sorted_titles.push_back(book.title);
	}

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

	std::cout << "\n---- Chapter 2: Selection Sort by Rating ----\n";
	auto start_selection_sort_time = std::chrono::high_resolution_clock::now();
	selection_sort(books);
	auto end_selection_sort_time = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> selection_sort_time_taken = end_selection_sort_time - start_selection_sort_time;

	std::cout << "Books sorted by rating using selection sort.\n";
	std::cout << "Selection sorting took " << selection_sort_time_taken.count() << " seconds.\n";

	std::cout << "\n---- First 20 books after selection sort ----\n";
	display_books(books, 20);

	std::vector<Book> top_books(books.begin(), books.begin() + 100);

	std::cout << "\n---- First 20 books before merge sort ----\n";
	display_books(top_books, 20);

	std::cout << "\n---- Chapter 3: Merge Sort by Rating ----\n";
	auto start_merge_sort_time = std::chrono::high_resolution_clock::now();
	merge_sort(top_books);
	auto end_merge_sort_time = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> merge_sort_time_taken = end_merge_sort_time - start_merge_sort_time;

	std::cout << "Books sorted by rating using merge sort.\n";
	std::cout << "Merge sorting took " << merge_sort_time_taken.count() << " seconds.\n";

	std::cout << "\n---- First 20 books after merge sort ----\n";
	display_books(top_books, 20);

	top_books.assign(books.begin(), books.begin() + 100);

	std::cout << "\n---- First 20 books before quick sort ----\n";
	display_books(top_books, 20);

	std::cout << "\n---- Chapter 4: Quick Sort by Rating ----\n";
	auto start_quick_sort_time = std::chrono::high_resolution_clock::now();
	quick_sort(top_books);
	auto end_quick_sort_time = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> quick_sort_time_taken = end_quick_sort_time - start_quick_sort_time;

	std::cout << "Books sorted by rating using quick sort.\n";
	std::cout << "Quick sorting took " << quick_sort_time_taken.count() << " seconds.\n";

	std::cout << "\n---- First 20 books after quick sort ----\n";
	display_books(top_books, 20);

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

	std::cout << "\n---- Chapter 6: Breadth-First Search ----\n";
	auto book_graph = create_graph_by_author(books);

	std::cout << "\nStarting BFS from 'Les Misérables' to 'The Hunchback of Notre-Dame':\n";
	bool path_exists = bfs(book_graph, "Les Misérables", "The Hunchback of Notre-Dame");

	if (!path_exists) {
		std::cout << "No path found from Les Misérables to The Hunchback of Notre-Dame.\n";
	}

	return 0;
}