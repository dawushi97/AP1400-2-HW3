# 高级编程 - 作业3
<p  align="center"> <b>作业3 - 2022年春季学期 <br> 截止日期：Farvardin 14日 周日 - 晚上11:59</b> </p>

## 概述

在本次作业中，我们将实现一个 *Binary Search Tree（二叉搜索树，简称BST）*。*Binary tree（二叉树）* 是一种树形图结构，其中每个节点最多只能有2个子节点。*Binary Search Tree（二叉搜索树）* 是一种特殊的二叉树，其中每个节点的右子节点的值大于左子节点的值。

我们需要实现2个类：一个是 `Node` 类，表示图中的每个节点；另一个是 `BST` 类，负责以适当的方式连接节点来构建二叉搜索树。由于 `Node` 类是 `BST` 类的直接属性，因此它应该定义在 BST 类内部。

**注意：** 你只能修改 `bst.cpp/h` 文件，以及 `main.cpp` 中的 debug 部分。

</br>

# Node 类
使用下面的代码片段来实现这个类。**注意：** 如有必要，你可能需要为这些函数添加一些关键字。除了这些关键字之外，你不允许更改函数或向此类添加新的成员函数，**除非在下文中另有说明**。

```cpp
class Node
{
public:
	Node(int value, Node* left, Node* right);
	Node();
	Node(const Node& node);

	int value;
	Node* left;
	Node* right;
};
```

---

每个节点都有一个整数值，并可以使用 left（左）和 right（右）指针指向其子节点。如果一个或多个子节点不存在，则将它们赋值为 `nullptr`（空指针）。

- **std::cout**
实现 `<<` 运算符，使你能够使用 `std::cout` 在一行中以美观的方式打印节点，输出应包含节点的地址、节点的值、节点左子节点的地址和节点右子节点的地址。

- **与 int 的不等式比较**
实现适当的函数，使节点与整数之间可以进行所有可能的不等式比较，即：

	```cpp
	node > 4	node >= 5	node < 6	node <= 5	node == 3
	5 < node	6 <= node	2 > node	2 >= node	3 == node
	```


</br>

# BST 类
使用下面的代码片段来实现这个类。**注意：** 如有必要，你可能需要为这些函数添加一些关键字。除了这些关键字之外，你不允许更改函数或向此类添加新的成员函数，**除非在下文中另有说明**。

```cpp
class BST
{
public:
    Node*& get_root();
    void bfs(std::function<void(Node*& node)> func);
    size_t length();
    bool add_node(int value);
    Node** find_node(int value);
    Node** find_parrent(int value);
    Node** find_successor(int value);
    bool delete_node(int value);

private:
    Node* root;
};
```

---
此类负责通过以适当的方式连接节点来构建 BST 图。`root`（根节点）是此类唯一的成员变量，它指向二叉搜索树的第一个节点。

- **get_root**
返回私有成员变量 `root`。

- **bfs**
*Breadth-first search（广度优先搜索，简称BFS）* 是一种通过遍历每个节点来搜索树的算法；请实现这个算法！</br> 此函数接受一个 `std::function` 类型的输入参数，此类型的行为类似于函数指针，可以包装 C++ 中任何可调用对象，如普通函数或 lambda 函数（匿名函数）。在本次作业中你将使用 lambda 函数，请随意搜索和学习相关知识。</br> 用户应该能够使用此参数对树中的节点应用任何函数，即在 BFS 算法找到的每个节点上调用 `func` 对象。

- **length**
返回 BST 中存在的节点数量。

- **add_node**
在适当的位置向 BST 添加新节点。**注意：** 用户不应该能够添加树中已存在的值。

- **find_node**
在树中查找具有指定值的节点，并返回指向该节点指针的指针（即二级指针）。</br> **注意：** 不要使用 BFS 算法来查找节点，而应使用二叉搜索树的特性：*这就是我们使用它们的原因*。

- **find_parrent**
查找具有指定值的节点的父节点，并返回指向该父节点指针的指针。</br> **注意：** 不要使用 BFS 算法来查找节点。

- **find_successor**
查找具有指定值的节点的 successor（后继节点）。后继节点是指在中序遍历中紧跟在该节点之后的节点，通常是右子树中的最小值节点。

- **delete_node**
删除具有指定值的节点。如果不存在具有该值的节点，则返回 false。

- **std::cout**
实现 `<<` 运算符，使你能够使用 `std::cout` 以美观的方式打印 BST。为此，请打印 BST 的每个节点。如果你能够生成与下面完全相同的输出（星号是输出的一部分），将获得额外加分。

	```cpp
	********************************************************************************
	0x188dee70       => value:25        left:0x188dedd0      right:0x188dedf0
	0x188dedd0       => value:10        left:0x188dee30      right:0x188ded90
	0x188dedf0       => value:50        left:0               right:0x188dee50
	0x188dee30       => value:7         left:0               right:0
	0x188ded90       => value:15        left:0               right:0
	0x188dee50       => value:53        left:0               right:0
	binary search tree size: 6
	********************************************************************************
	```

- **operator++（自增运算符）**
实现两种 `++` 运算符，使它们能够将树中每个节点的值加1。<br/> 不要忘记 `bst++`（后置自增）和 `++bst`（前置自增）之间的区别。

- **destructor（析构函数）**
如你所知，在类中处理动态对象时，创建析构函数是必要的。幸运的是，我将为你承担析构函数的实现，因此请将下面的代码作为你的类析构函数实现。

	```cpp
	BST::~BST()
	{
		std::vector<Node*> nodes;
		bfs([&nodes](BST::Node*& node){nodes.push_back(node);});
		for(auto& node: nodes)
			delete node;
	}
	```

- **Constructors（构造函数）**
为该类实现3个构造函数：**I)** default constructor（默认构造函数）。**II)** copy constructor（拷贝构造函数）。**III)** move constructor（移动构造函数）。

- **operator=（赋值运算符）**
实现两个版本的 `operator=`（copy 拷贝版本和 move 移动版本）。

</br>

# 挑战
- 如果你到达了这一部分，恭喜你，只剩下最后一个简单的部分了。做出适当的安排，使你可以使用构造函数添加任意数量的节点。也就是说，下面的代码应该能够正常工作。


	```cpp
	BST bst1{5, 1, 10, 2, 8, 50, 4, 60};
    BST bst2{3, 2, 100, 20, 8, 50, 4, 60, 44, 23};
	```

这需要使用 initializer_list（初始化列表）或可变参数模板来实现。

</br>

# 最后
如前所述，除非另有说明，否则不要修改已有内容的其他文件。如果你想测试你的代码，可以使用 `main.cpp` 中的 `debug` 部分。

```cpp
if (true) // 改为 false 以运行单元测试
{
	// debug 调试部分
}
else
{
	::testing::InitGoogleTest(&argc, argv);
	std::cout << "RUNNING TESTS ..." << std::endl;
	int ret{RUN_ALL_TESTS()};
	if (!ret)
		std::cout << "<<<SUCCESS>>>" << std::endl;
	else
	  std::cout << "FAILED" << std::endl;
}
return 0;
```
<br/>
<p  align="center"> <b>祝你好运！</b> </p>
