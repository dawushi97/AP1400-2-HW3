#include "bst.h"
#include <iomanip>
#include <queue> // 添加在文件开头
using Node = BST::Node;
Node::Node(int value, Node *left, Node *right)
    : value(value), left(left), right(right) {}

Node::Node() {
  value = 0;
  left = nullptr;
  right = nullptr;
}

Node::Node(const Node &node)
    : value(node.value), left(node.left), right(node.right) {}

std::ostream &operator<<(std::ostream &os, const Node &node) {
  os << &node << std::setw(8) << "=> value:" << node.value << std::setw(8)
     << "left:" << &node.left << std::setw(8) << "right:" << &node.right;
  return os;
}

bool operator<(int value, const Node &node) { return value < node.value; }

bool operator<=(int value, const Node &node) { return value <= node.value; }

bool operator>(int value, const Node &node) { return value > node.value; }

bool operator>=(int value, const Node &node) { return value >= node.value; }

bool operator==(int value, const Node &node) { return value == node.value; }

BST::BST() { root = nullptr; }

BST::BST(const BST &bst) {}

BST::BST(BST &bst) {}

BST::~BST() {
  std::vector<Node *> nodes;
  bfs([&nodes](BST::Node *&node) { nodes.push_back(node); });
  for (auto &node : nodes)
    delete node;
}
void BST::bfs(std::function<void(Node *&node)> func) {
  if (root == nullptr)
    return;

  std::queue<Node *> q;
  q.push(root);

  while (!q.empty()) {
    Node *current = q.front();
    q.pop();

    func(current);

    if (current->left)
      q.push(current->left);
    if (current->right)
      q.push(current->right);
  }
}

size_t BST::length() {
  size_t count = 0;
  bfs([&count](Node *&node) { ++count; });
  return count;
}

bool BST::add_node(int value) {}

Node **BST::find_node(int value) {}

Node **BST::find_parrent(int value) {}

Node **BST::find_successor(int value) {}

bool BST::delete_node(int value) {}
