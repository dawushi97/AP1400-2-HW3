#ifndef BST_H
#define BST_H
#include <functional>
#include <iostream>
using std::cout;
using std::endl;

class BST {
public:
  class Node {
  public:
    // Node consturctor
    Node(int value, Node *left, Node *right);
    Node();
    Node(const Node &node);

    int value;
    Node *left;
    Node *right;
    // Node count<<
    friend std::ostream &operator<<(std::ostream &os, const Node &node);

    // Node inequality
    bool operator>(int value) const { return this->value > value; }
    bool operator>=(int value) const { return this->value >= value; }
    bool operator<(int value) const { return this->value < value; }
    bool operator<=(int value) const { return this->value <= value; }
    bool operator==(int value) const { return this->value == value; }

    friend bool operator<(int value, const Node &node);
    friend bool operator<=(int value, const Node &node);
    friend bool operator>(int value, const Node &node);
    friend bool operator>=(int value, const Node &node);
    friend bool operator==(int value, const Node &node);
  };

  BST();
  BST(const BST &bst);
  BST &operator=(const BST &bst); // copy assignment
  BST(BST &&bst);
  BST &operator=(BST &&bst);      // move assignment
  ~BST();

  BST(std::initializer_list<int> init); // initializer list constructor
  Node *&get_root() { return root; }
  void bfs(std::function<void(Node *&node)> func);
  size_t length();
  bool add_node(int value);
  Node **find_node(int value);
  Node **find_parrent(int value);
  Node **find_successor(int value);
  bool delete_node(int value);

  friend std::ostream &operator<<(std::ostream &os,
                                  const BST &bst); // output operator
  BST &operator++();                               // prefix increment
  BST operator++(int);                             // postfix increment

private:
  Node *root;
};

#endif // BST_H
