#include "bst.h"
#include <iomanip>
#include <queue>
#include <vector>

// ─── Node constructors ──────────────────────────────────────────────────────

BST::Node::Node(int value, Node *left, Node *right)
    : value(value), left(left), right(right) {}

BST::Node::Node() : value(0), left(nullptr), right(nullptr) {}

BST::Node::Node(const Node &node)
    : value(node.value), left(node.left), right(node.right) {}

// ─── Node operators ─────────────────────────────────────────────────────────

std::ostream &operator<<(std::ostream &os, const BST::Node &n) {
  os << std::setw(14) << &n << " => value:" << std::setw(4) << n.value;
  os << " | left:";
  if (n.left)
    os << std::setw(14) << n.left;
  else
    os << std::setw(14) << "null";
  os << " | right:";
  if (n.right)
    os << std::setw(14) << n.right;
  else
    os << std::setw(14) << "null";
  return os;
}

bool BST::Node::operator>(int n) const { return value > n; }
bool BST::Node::operator>=(int n) const { return value >= n; }
bool BST::Node::operator<(int n) const { return value < n; }
bool BST::Node::operator<=(int n) const { return value <= n; }
bool BST::Node::operator==(int n) const { return value == n; }

bool operator>(int n, const BST::Node &node) { return n > node.value; }
bool operator>=(int n, const BST::Node &node) { return n >= node.value; }
bool operator<(int n, const BST::Node &node) { return n < node.value; }
bool operator<=(int n, const BST::Node &node) { return n <= node.value; }
bool operator==(int n, const BST::Node &node) { return n == node.value; }

// ─── BST constructors / destructor ──────────────────────────────────────────

BST::BST() : root(nullptr) {}

BST::BST(const BST &bst) : root(nullptr) {
  if (!bst.root)
    return;
  std::queue<Node *> q;
  q.push(bst.root);
  while (!q.empty()) {
    auto *node = q.front();
    q.pop();
    add_node(node->value);
    if (node->left)
      q.push(node->left);
    if (node->right)
      q.push(node->right);
  }
}

BST::BST(BST &&bst) : root(bst.root) { bst.root = nullptr; }

BST::BST(std::initializer_list<int> list) : root(nullptr) {
  for (int val : list)
    add_node(val);
}

BST::~BST() {
  std::vector<Node *> nodes;
  bfs([&nodes](BST::Node *&node) { nodes.push_back(node); });
  for (auto &node : nodes)
    delete node;
}

// ─── BST assignment operators ───────────────────────────────────────────────

BST &BST::operator=(const BST &bst) {
  if (this == &bst)
    return *this;
  // 释放现有节点
  std::vector<Node *> nodes;
  bfs([&nodes](Node *&node) { nodes.push_back(node); });
  for (auto &node : nodes)
    delete node;
  root = nullptr;
  // 从源树 BFS 拷贝
  if (bst.root) {
    std::queue<Node *> q;
    q.push(bst.root);
    while (!q.empty()) {
      auto *n = q.front();
      q.pop();
      add_node(n->value);
      if (n->left)
        q.push(n->left);
      if (n->right)
        q.push(n->right);
    }
  }
  return *this;
}

BST &BST::operator=(BST &&bst) {
  if (this == &bst)
    return *this;
  // 释放现有节点
  std::vector<Node *> nodes;
  bfs([&nodes](Node *&node) { nodes.push_back(node); });
  for (auto &node : nodes)
    delete node;
  // 窃取源树的 root
  root = bst.root;
  bst.root = nullptr;
  return *this;
}

// ─── BST increment operators ────────────────────────────────────────────────

BST &BST::operator++() {
  bfs([](Node *&node) { node->value++; });
  return *this;
}

BST BST::operator++(int) {
  BST copy{*this};
  ++(*this);
  return copy;
}

// ─── BST stream operator ────────────────────────────────────────────────────

std::ostream &operator<<(std::ostream &os, const BST &bst) {
  os << std::string(80, '*') << std::endl;
  size_t count = 0;
  if (bst.root) {
    std::queue<BST::Node *> q;
    q.push(bst.root);
    while (!q.empty()) {
      auto *node = q.front();
      q.pop();
      count++;
      os << *node << std::endl;
      if (node->left)
        q.push(node->left);
      if (node->right)
        q.push(node->right);
    }
  }
  os << "binary search tree size: " << count << std::endl;
  os << std::string(80, '*');
  return os;
}

// ─── BST core methods ───────────────────────────────────────────────────────

BST::Node *&BST::get_root() { return root; }

void BST::bfs(std::function<void(Node *&node)> func) {
  if (!root)
    return;
  std::queue<Node *> q;
  q.push(root);
  while (!q.empty()) {
    auto *node = q.front();
    q.pop();
    func(node);
    if (node->left)
      q.push(node->left);
    if (node->right)
      q.push(node->right);
  }
}

size_t BST::length() {
  size_t count = 0;
  bfs([&count](Node *&node) { count++; });
  return count;
}

bool BST::add_node(int value) {
  if (!root) {
    root = new Node(value, nullptr, nullptr);
    return true;
  }

  Node *current = root;
  while (true) {
    if (*current == value)
      return false;
    else if (value < *current) {
      if (!current->left) {
        current->left = new Node(value, nullptr, nullptr);
        return true;
      }
      current = current->left;
    } else {
      if (!current->right) {
        current->right = new Node(value, nullptr, nullptr);
        return true;
      }
      current = current->right;
    }
  }
}

BST::Node **BST::find_node(int value) {
  Node **current = &root;
  while (*current) {
    if (**current == value)
      return current;
    else if (value < **current)
      current = &((*current)->left);
    else
      current = &((*current)->right);
  }
  return nullptr;
}

BST::Node **BST::find_parrent(int value) {
  if (!root || *root == value)
    return nullptr;
  Node **current = &root;
  while (*current) {
    Node *left = (*current)->left;
    Node *right = (*current)->right;
    if ((left && *left == value) || (right && *right == value))
      return current;
    if (value < **current)
      current = &((*current)->left);
    else if (value > **current)
      current = &((*current)->right);
    else
      return nullptr;
  }
  return nullptr;
}

BST::Node **BST::find_successor(int value) {
  Node **node = find_node(value);
  if (!node || !*node || !(*node)->left)
    return nullptr;
  node = &((*node)->left);
  Node **successor = node;
  while (*node) {
    successor = node;
    node = &((*node)->right);
  }
  return successor;
}

bool BST::delete_node(int value) {
  Node **node = find_node(value);
  if (!node || !*node)
    return false;

  Node *target = *node;

  if (target->left && target->right) {
    Node **successor = find_successor(value);
    target->value = (*successor)->value;
    target = *successor;
    *successor = target->left;
  } else {
    *node = target->left ? target->left : target->right;
  }

  delete target;
  return true;
}
