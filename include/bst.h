#ifndef BST_H
#define BST_H

#include <cstddef>
#include <functional>
#include <initializer_list>
#include <ostream>

class BST {
public:
  class Node {
  public:
    Node(int value, Node *left, Node *right);
    Node();
    Node(const Node &node);

    friend std::ostream &operator<<(std::ostream &os, const Node &n);

    bool operator>(int n) const;
    bool operator>=(int n) const;
    bool operator<(int n) const;
    bool operator<=(int n) const;
    bool operator==(int n) const;

    friend bool operator>(int n, const Node &node);
    friend bool operator>=(int n, const Node &node);
    friend bool operator<(int n, const Node &node);
    friend bool operator<=(int n, const Node &node);
    friend bool operator==(int n, const Node &node);

    int value;
    Node *left;
    Node *right;
  };

  BST();
  BST(const BST &bst);
  BST(BST &&bst);
  BST(std::initializer_list<int> list);
  ~BST();

  BST &operator=(const BST &bst);
  BST &operator=(BST &&bst);
  BST &operator++();
  BST operator++(int);

  friend std::ostream &operator<<(std::ostream &os, const BST &bst);

  Node *&get_root();
  void bfs(std::function<void(Node *&node)> func);
  size_t length();
  bool add_node(int value);
  Node **find_node(int value);
  Node **find_parrent(int value);
  Node **find_successor(int value);
  bool delete_node(int value);

private:
  Node *root;
};

#endif // BST_H
