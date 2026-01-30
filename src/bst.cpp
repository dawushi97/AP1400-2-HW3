#include "bst.h"
#include <compare>
#include <cstddef>
#include <iomanip>
#include <queue>
#include <sys/resource.h>
using namespace std;

std::ostream &operator<<(std::ostream &os, const Node &n) {
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

bool Node::operator>(int n) const { return value > n; }
bool Node::operator>=(int n) const { return value >= n; }
bool Node::operator<(int n) const { return value < n; }
bool Node::operator<=(int n) const { return value <= n; }
bool Node::operator==(int n) const { return value == n; }

bool operator>(int n, const Node &node) { return n > node.value; }
bool operator>=(int n, const Node &node) { return n >= node.value; }
bool operator<(int n, const Node &node) { return n < node.value; }
bool operator<=(int n, const Node &node) { return n <= node.value; }
bool operator==(int n, const Node &node) { return n == node.value; }

Node *&BST::get_root() { return root; }
void BST::bfs(std::function<void(Node *&node)> func) {
  if (!root)
    return;
  queue<Node *> q;
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
  // 情况1: 树为空
  if (!root) {
    root = new Node(value, nullptr, nullptr);
    return true;
  }

  // 情况2: 树不为空，需要找到正确的插入位置
  Node *current = root;

  while (true) {
    // TODO(human): 实现 BST 插入的核心逻辑
    // 根据 value 和 current->value 的比较结果：
    // - 如果相等：返回 false（不允许重复）
    if (*current == value)
      return false;
    // - 如果 value 更小：往左走（或插入左边）
    else if (value < *current) {
      if (current->left == nullptr) {

        current->left = new Node(value, nullptr, nullptr);
        return true;
      } else {
        current = current->left;
      }
    }
    // - 如果 value 更大：往右走（或插入右边）
    else {
      if (current->right == nullptr) {
        current->right = new Node(value, nullptr, nullptr);
        return true;
      } else {
        current = current->right;
      }
    }
    //
    // 提示：你可以使用已实现的运算符，如 *current == value
  }
}

Node **BST::find_node(int value) {
  // // 旧版本（有问题）：
  // // 问题1: 返回局部变量地址
  // // 问题2: nullptr检查位置错误，会先解引用再判空
  // if (!root)
  //   return nullptr;
  // Node *current = root;
  // while (true) {
  //   if (*current == value)
  //     return &current;  // ❌ 返回局部变量地址
  //   else if (value < *current) {
  //     current = current->left;
  //   } else if (value > *current) {
  //     current = current->right;
  //   } else if (current == nullptr) {  // ❌ 永远执行不到
  //     return nullptr;
  //   }
  // }

  // 新版本：使用 Node** 遍历，明确三分支
  Node **current = &root;

  while (*current != nullptr) {
    if (**current == value)
      return current;
    else if (value < **current)
      current = &((*current)->left);
    else if (value > **current)
      current = &((*current)->right);
  }

  return nullptr;
}
Node **BST::find_parrent(int value) {
  if (root == nullptr || *root == value)
    return nullptr;
  Node **current = &root;
  while (*current != nullptr) {
    Node *left = (*current)->left;
    Node *right = (*current)->right;
    if (left && *left == value)
      return current;
    if (right && *right == value)
      return current;

    if (value < **current)
      current = &((*current)->left);
    else if (value > **current)
      current = &((*current)->right);
    else
      return nullptr;
    ;
  }
  return nullptr;
}
Node **BST::find_successor(int value) {
  if (root == nullptr)
    return nullptr;
  Node **current = &root;
  while (*current != nullptr) {
    Node *left = (*current)->left;
    Node *right = (*current)->right;

    if (**current == value) {
      if (left != nullptr)
        return left;
      else if (right != nullptr)
        return right;
      else
        return nullptr;
      ;
    }
  }
  return nullptr;
}
bool BST::delete_node(int value);
