#ifndef AVL_TREE_H
#define AVL_TREE_H
#include "sort_algorithms.h"
#include <memory>


class AVLNode {

public:
  Book book;
  std::shared_ptr<AVLNode> left;
  std::shared_ptr<AVLNode> right;
  int height;
  AVLNode(const Book &b) : book(b), height(1) {}
};

class AVLTree {

private:
  std::shared_ptr<AVLNode> root;
  int height(const std::shared_ptr<AVLNode> &node) {
    if (!node)
      return 0;
    return node->height;
  }
  int balanceFactor(const std::shared_ptr<AVLNode> &node) {
    if (!node)
      return 0;
    return height(node->left) - height(node->right);
  }
  void updateHeight(std::shared_ptr<AVLNode> &node) {
    if (!node)
      return;
    node->height = std::max(height(node->left), height(node->right)) + 1;
  }


  std::shared_ptr<AVLNode> rightRotate(std::shared_ptr<AVLNode> y) {
    auto x = y->left;
    auto T2 = x->right;
    x->right = y;
    y->left = T2;
    updateHeight(y);
    updateHeight(x);
    return x;
  }


  std::shared_ptr<AVLNode> leftRotate(std::shared_ptr<AVLNode> x) {
    auto y = x->right;
    auto T2 = y->left;
    y->left = x;
    x->right = T2;
    updateHeight(x);
    updateHeight(y);
    return y;
  }


  std::shared_ptr<AVLNode> insert(std::shared_ptr<AVLNode> node,
                                  const Book &book) {
    if (!node)
      return std::make_shared<AVLNode>(book);
    if (book.rating < node->book.rating)
      node->left = insert(node->left, book);
    else if (book.rating > node->book.rating)
      node->right = insert(node->right, book);
    else
      return node;
    updateHeight(node);
    int balance = balanceFactor(node);
    // Left Left Case
    if (balance > 1 && book.rating < node->left->book.rating)
      return rightRotate(node);
    // Right Right Case
    if (balance < -1 && book.rating > node->right->book.rating)
      return leftRotate(node);
    // Left Right Case
    if (balance > 1 && book.rating > node->left->book.rating) {
      node->left = leftRotate(node->left);
      return rightRotate(node);
    }
    // Right Left Case
    if (balance < -1 && book.rating < node->right->book.rating) {
      node->right = rightRotate(node->right);
      return leftRotate(node);
    }
    return node;
  }


  void inorderTraversal(std::shared_ptr<AVLNode> node,
                        std::vector<Book> &books) {
    if (!node)
      return;
    inorderTraversal(node->left, books);
    books.push_back(node->book);
    inorderTraversal(node->right, books);
  }


public:
  AVLTree() : root(nullptr) {}
  void insertBook(const Book &book) { root = insert(root, book); }
  std::vector<Book> getSortedBooks() {
    std::vector<Book> books;
    inorderTraversal(root, books);
    return books;
  }
};

#endif // AVL_TREE_H