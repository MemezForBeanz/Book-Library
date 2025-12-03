# Book Algorithms Project

## Overview
This is a C++ project that demonstrates fundamental computer science algorithms using a book dataset. The project showcases:
- **Binary Search** for finding books by title
- **Selection Sort** for sorting books by rating
- **Merge Sort** for efficient recursive sorting with visualization of recursion depth

## Project Structure
- `main.cpp` - Main program that loads book data and demonstrates the algorithms
- `search_algorithms.h` - Binary search implementation
- `sort_algorithms.h` - Selection sort implementation and Book struct definition
- `merge_sort.h` - Merge sort implementation with recursion tracking
- `data/books.json` - Large dataset of books with titles, authors, ratings, and metadata
- `Makefile` - Build configuration using clang++

## Current State
The project is fully functional and compiles successfully. The program:
1. Loads book data from JSON file
2. Prompts user to search for a book using binary search
3. Sorts books by rating using selection sort
4. Demonstrates merge sort on a subset of 100 books with recursion depth visualization

## Dependencies
- C++ compiler (clang++)
- nlohmann/json library for JSON parsing

## Recent Changes
- December 03, 2025: Initial setup with C++ toolchain installed and workflow configured

## User Preferences
None recorded yet.
