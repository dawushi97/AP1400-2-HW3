#include "bst.h"
#include <iomanip>

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
