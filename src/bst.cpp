#include "bst.h"
#include <iomanip>
#include <queue>
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

BST::BST() : root(nullptr) {}

BST::BST(const BST &bst) {
  root = nullptr; // 初始化

  // 深拷贝
  if (bst.root != nullptr) {
    // 递归辅助函数用于复制整棵树
    std::function<Node *(Node *)> copyTree =
        [&](Node *node) -> Node * { // 添加 [&] 进行捕获
      if (node == nullptr)
        return nullptr;
      // 创建新节点，并递归复制左右子树
      Node *newNode = new Node(node->value, nullptr, nullptr);
      newNode->left = copyTree(node->left);   // 现在可以访问 copyTree
      newNode->right = copyTree(node->right); // 现在可以访问 copyTree
      return newNode;
    };

    root = copyTree(bst.root);
  }
}

BST::BST(BST &&bst) {
  this->root = bst.root;
  bst.root = nullptr;
}
BST &BST::operator=(const BST &bst) {
  if (this != &bst) {
    this->~BST();
    root = nullptr;
    if (bst.root != nullptr) {
      std::function<Node *(Node *)> copyTree = [&](Node *node) -> Node * {
        if (node == nullptr)
          return nullptr;
        // 创建新节点，并递归复制左右子树
        Node *newNode = new Node(node->value, nullptr, nullptr);
        newNode->left = copyTree(node->left);   // 现在可以访问 copyTree
        newNode->right = copyTree(node->right); // 现在可以访问 copyTree
        return newNode;
      };
      root = copyTree(bst.root);
    }
  }
  return *this;
}

BST &BST::operator=(BST &&bst) {
  if (this != &bst) {
    delete root;
    this->root = bst.root;
    bst.root = nullptr;
  }
  return *this;
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

bool BST::add_node(int value) {
  if (root == nullptr) {
    root = new Node(value, nullptr, nullptr);
    return true;
  }
  Node *current = root;
  while (true) {
    if (value < current->value) {
      if (current->left == nullptr) {
        current->left = new Node(value, nullptr, nullptr);
        return true;
      }
      current = current->left;
    } else if (value > current->value) {
      if (current->right == nullptr) {
        current->right = new Node(value, nullptr, nullptr);
        return true;
      }
      current = current->right;
    } else {
      return false;
    }
  }
}

Node **BST::find_node(int value) {
  Node **current = &root;
  while (*current != nullptr) {
    if (value < (*current)->value)
      current = &(*current)->left;
    else if (value > (*current)->value)
      current = &(*current)->right;
    else
      return current;
  }
  return nullptr;
}

Node **BST::find_parrent(int value) {
  if (root == nullptr || root->value == value)
    return nullptr;

  Node **current = &root;
  Node **parent = nullptr;

  while (*current != nullptr) {
    if (value < (*current)->value) {
      parent = current;
      current = &(*current)->left;
    } else if (value > (*current)->value) {
      parent = current;
      current = &(*current)->right;
    } else {
      return parent;
    }
  }
  return nullptr;
}

Node **BST::find_successor(int value) {
  Node **node = find_node(value);
  if (node == nullptr)
    return nullptr;

  // 如果有左子树，successor 是左子树中最大的节点
  if ((*node)->left != nullptr) {
    Node **current = &(*node)->left;
    while ((*current)->right != nullptr) {
      current = &(*current)->right;
    }
    return current;
  }

  // 如果没有左子树，successor 是第一个小于该节点的祖先
  Node **current = &root;
  Node **successor = nullptr;
  while (*current != nullptr) {
    if (value > (*current)->value) {
      successor = current;
      current = &(*current)->right;
    } else if (value < (*current)->value) {
      current = &(*current)->left;
    } else {
      break;
    }
  }
  return successor;
}

bool BST::delete_node(int value) {
  Node **target = find_node(value);
  if (target == nullptr)
    return false;

  Node *node = *target;

  // Case 1: 叶子节点
  if (node->left == nullptr && node->right == nullptr) {
    delete node;
    *target = nullptr;
  }
  // Case 2: 只有左子树
  else if (node->right == nullptr) {
    *target = node->left;
    delete node;
  }
  // Case 3: 只有右子树
  else if (node->left == nullptr) {
    *target = node->right;
    delete node;
  }
  // Case 4: 有两个子节点
  else {
    // 找到右子树中最小的节点（后继节点）
    Node **successor = &(node->right);
    while ((*successor)->left != nullptr) {
      successor = &((*successor)->left);
    }

    // 保存后继节点的右子树
    Node *successorRight = (*successor)->right;

    // 如果后继节点不是直接的右子节点
    if (successor != &(node->right)) {
      // 将后继节点的右子树连接到后继节点的父节点
      *successor = successorRight;

      // 将原节点的右子树连接到后继节点
      (*target)->right = node->right;
    }

    // 将原节点的左子树连接到后继节点
    (*target)->left = node->left;

    // 删除原节点
    delete node;
    *target = *successor;
  }

  return true;
}

std::ostream &operator<<(std::ostream &os, const BST &bst) {
  os << std::string(80, '*') << std::endl; // 打印上边界

  // 使用 lambda 函数打印每个节点
  std::vector<Node *> nodes;
  const_cast<BST &>(bst).bfs([&nodes](Node *&node) { nodes.push_back(node); });

  // 打印每个节点的信息
  for (const auto &node : nodes) {
    os << std::hex << node << std::dec << std::setw(8)
       << "=> value:" << node->value << std::setw(8)
       << "left:" << (node->left ? node->left : 0) << std::setw(8)
       << "right:" << (node->right ? node->right : 0) << std::endl;
  }

  // 打印树的大小
  os << "binary search tree size: " << nodes.size() << std::endl;

  os << std::string(80, '*') << std::endl; // 打印下边界
  return os;
}

BST &BST::operator++() {
  bfs([](Node *&node) { node->value += 1; });
  return *this;
}

BST BST::operator++(int) {
  BST temp(*this);

  ++(*this);

  return temp;
}

BST::BST(std::initializer_list<int> init) {
  root = nullptr;
  for (auto nodeValue : init) {
    add_node(nodeValue);
  }
}

BST::~BST() {
  std::vector<Node *> nodes;
  bfs([&nodes](BST::Node *&node) { nodes.push_back(node); });
  for (auto &node : nodes)
    delete node;
}
