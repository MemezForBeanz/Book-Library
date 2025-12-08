#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <unordered_map>
#include <vector>

#include "avl_tree.h"
#include "dijkstra.h"
#include "nlohmann/json.hpp"

using json = nlohmann::json;

std::unordered_map<std::string, std::vector<std::string>> load_books(const std::string &filename) {
	std::ifstream file(filename);
	json booksJson;
	file >> booksJson;

	std::unordered_map<std::string, std::vector<std::string>> book_graph;
	for (const auto &book : booksJson) {
		std::string title = book.value("title", "");
		if (title.empty()) {
			continue;
		}

		auto it = book.find("connections");
		if (it != book.end() && it->is_array()) {
			for (const auto &neighbor : *it) {
				if (neighbor.is_string()) {
					book_graph[title].push_back(neighbor.get<std::string>());
				}
			}
		}
	}
	return book_graph;
}

std::vector<Book> load_books_vector(const std::string &filename) {
	std::ifstream file(filename);
	json booksJson;
	file >> booksJson;

	std::vector<Book> books;
	books.reserve(booksJson.size());
	for (const auto &book : booksJson) {
		books.push_back(Book{book.value("title", ""), book.value("author", ""), book.value("rating", 0.0),
							 book.value("pages", 0)});
	}
	return books;
}

void display_books(const std::vector<Book> &books, int count) {
	for (int i = 0; i < std::min(count, static_cast<int>(books.size())); ++i) {
		std::cout << books[i].title << " (Rating: " << books[i].rating << ", Pages: " << books[i].pages
				  << ")\n";
	}
}

int main() {
	auto books = load_books_vector("data/books.json");

	if (books.empty()) {
		std::cout << "No books loaded.\n";
		return 0;
	}

	std::cout << "\n---- Chapter 8: AVL Trees ----" << std::endl;
	std::cout << "Building AVL tree with subset of books...\n";
	AVLTree avl_tree;
	int subset_size = std::min<int>(100, books.size());
	std::vector<Book> subset_books(books.begin(), books.begin() + subset_size);
	for (const auto &book : subset_books) {
		avl_tree.insertBook(book);
	}
	auto sorted_books = avl_tree.getSortedBooks();
	std::cout << "\nFirst 20 books in order of rating (AVL tree inorder traversal):\n";
	display_books(sorted_books, 20);

	std::cout << "\n---- Chapter 9: Dijkstra's Algorithm ----" << std::endl;
	auto weighted_graph = create_book_graph(books);

	std::string start_book = books.front().title;
	std::string end_book = books.size() > 50 ? books[50].title : books.back().title;
	std::cout << "\nFinding shortest path between:\n";
	std::cout << "Start: " << start_book << "\n";
	std::cout << "End: " << end_book << "\n";

	auto [distances, previous] = dijkstra(weighted_graph, start_book);
	if (distances.find(end_book) != distances.end() && distances[end_book] != std::numeric_limits<double>::infinity()) {
		auto path = find_shortest_path(previous, start_book, end_book);
		std::cout << "\nShortest path found:\n";
		for (size_t i = 0; i < path.size(); ++i) {
			const auto &book_title = path[i];
			auto it = std::find_if(books.begin(), books.end(), [&book_title](const Book &b) { return b.title == book_title; });
			if (it != books.end()) {
				std::cout << i + 1 << ". " << book_title << " (Rating: " << it->rating << ")\n";
			}
		}
		std::cout << "\nTotal path weight: " << distances[end_book] << std::endl;
	} else {
		std::cout << "\nNo path found between these books" << std::endl;
	}

	return 0;
}