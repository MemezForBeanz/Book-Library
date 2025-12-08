#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "avl_tree.h"
#include "depth_first_search.h"
#include "nlohmann/json.hpp"

using json = nlohmann::json;

std::unordered_map<std::string, std::vector<std::string>> load_books(const std::string &filename) {
	std::ifstream file(filename);
	json booksJson;
	file >> booksJson;

	std::unordered_map<std::string, std::vector<std::string>> book_graph;
	for (const auto &book : booksJson) {
		std::string title = book.value("title", "");
		if (title.empty()) continue;

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
		books.push_back(Book{
			book.value("title", ""),
			book.value("author", ""),
			book.value("rating", 0.0),
			book.value("pages", 0)});
	}
	return books;
}

void display_books(const std::vector<Book> &books, int count) {
	for (int i = 0; i < std::min(count, static_cast<int>(books.size())); ++i) {
		std::cout << books[i].title << " (Rating: " << books[i].rating << ", Pages: " << books[i].pages << ")\n";
	}
}

int main() {
	auto book_graph = load_books("data/books.json");
	auto books = load_books_vector("data/books.json");

	std::cout << "\n---- Chapter 7: Depth-First Search ----\n";
	std::cout << "\nStarting DFS from 'Les Misérables' to 'The Hunchback of Notre-Dame':\n";
	bool dfs_path_exists = dfs(book_graph, "Les Misérables", "The Hunchback of Notre-Dame");
	if (!dfs_path_exists) {
		std::cout << "No path found from Les Misérables to The Hunchback of Notre-Dame using DFS.\n";
	}

	std::cout << "\n---- Chapter 8: AVL Trees ----\n";
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

	return 0;
}