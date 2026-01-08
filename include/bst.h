#ifndef BST_H
#define BST_H

#include <cstddef>
#include <functional>
#include <ostream>
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
  friend bool operator>=(int, const Node &noden);
  friend bool operator<(int, const Node &noden);
  friend bool operator<=(int, const Node &noden);
  friend bool operator==(int, const Node &noden);

  int value;
  Node *left;
  Node *right;
};

class BST {
public:
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
