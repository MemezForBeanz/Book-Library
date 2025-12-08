#ifndef HASH_TABLE_H
#define HASH_TABLE_H
#include <iostream>
#include <string>
#include <unordered_map>
class HashTable {
private:
  std::unordered_map<std::string, double> table;

public:
  void insert(const std::string &key, double value) { table[key] = value; }
  double get(const std::string &key) {
    auto search = table.find(key);
    if (search != table.end()) {
      return search->second;
    }
    return -1; // Returns -1 if the key is not found
  }
  void remove(const std::string &key) { table.erase(key); }
  void display() const {
    // Don't display all entries due to the large dataset
    for (const auto &entry : table) {
      std::cout << entry.first << ": " << entry.second << std::endl;
    }
  }
};
#endif // HASH_TABLE_H