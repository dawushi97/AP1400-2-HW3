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
  BST(BST &bst);
  ~BST();

  Node *&get_root() { return root; };
  void bfs(std::function<void(Node *&node)> func);
  size_t length();
  bool add_node(int value);
  Node **find_node(int value);
  Node **find_parrent(int value);
  Node **find_successor(int value);
  bool delete_node(int value);

  BST& operator=(const BST& bst);  // 拷贝赋值
  BST& operator=(BST&& bst);  // 移动赋值
  friend std::ostream& operator<<(std::ostream& os, const BST& bst);  // 输出运算符
  BST& operator++();  // 前缀递增
  BST operator++(int);  // 后缀递增

private:
  Node *root;
};

#endif // BST_H
