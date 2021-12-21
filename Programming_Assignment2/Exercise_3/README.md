# Programming Assignment 2 EX3

**注意：本目录版本为<u>使用了</u>B+树、B树和哈希进行数据库读写优化的版本**。

## 🧡系统示意图💙

<img src=".\diagram.png" alt="diagram" style="zoom:80%;" />

## ✨文件夹介绍

- **include**文件夹放置头文件
- **src**文件夹放置源码文件
- **database_auto**文件夹放置自动测试模式需要用到的数据
- **report**文件夹放置生成的report

## 💎文件介绍

- **BPlus_node.h**：B+树节点相关定义
- **BPlus_tree.h**：B+树相关定义
- **btree.h**，**map.h**，**set.h**：B树相关定义
- **dataType.h**：数据库相关定义
- **information.h**：来自Programming Assignment1的相关定义，包括原始数据类、报告类、斐波拉契堆类
- **BPlus_node.cpp**：B+树节点的实现
- **BPlus_tree.cpp**：B+树的实现
- **helper.cpp**：一些协助函数，例如计算日期差，生成随机病人信息等
- **information.cpp**：大部分实现的代码，包括原始数据类、报告类、斐波拉契堆类、数据库类等
- **main.cpp**：主程序

## 🖍思路介绍

一个Database中有四个Relation，分别保存了每个病人的Person、Medical Status、Registration、Treatment这四类信息。每一个relation里有多个row，每个row代表一条记录。

在我们的实现中，Relation由Block列表实现，数据储存在Block中，索引储存在B+树中，实现了键-值分离。

在查询主键的过程中，我们使用B+树进行索引优化；在查询辅键的过程中，我们使用了B树和哈希表进行优化。

具体来说，当我们进行病人的增删查改的时候，以往我们需要遍历整个数据库来找到该病人，现在我们只需要用B+树维护一个病人ID到病人数据库位置的映射，然后直接对该数据库位置进行操作即可；当我们进行报告生成的时候，以往我们需要遍历整个数据库来找出需要统计的病人的信息，现在我们用B树和哈希表维护一个时间和病人ID的映射，即可实现快速的需统计病人的查找。

为了简单起见，三种治疗优先度分别定义为：原始的那种、以年龄作为优先度（类似于一种针对老人的服务）和以预约时间作为优先度（类似于先到先得）。

## 👉main的使用：

我们的程序支持自动测试和手动测试两种模式。在自动测试模式中，程序会自动准备病人信息并在合适的时间把病人信息输入到系统中，每一天的变化都会在控制台上显示出来，并在7天和30天的时候生成每周报告和每月报告；在手动测试模式中，你可以手动输入每个病人的信息（不推荐），或使用自动信息生成来生成你需要的任意数量的病人信息（推荐），并控制系统的运行和报告的生成。

**注意：在运行main之前，请确保report文件夹存在；在运行自动测试前，请解压缩database_auto.zip并确保database_auto文件夹及其中的文件存在。**

## 👋用到的开源代码：

B+树：[B+树（C++实现）_handerliu的博客-CSDN博客](https://blog.csdn.net/liu1064782986/article/details/7982290)

B树：[Kronuz/cpp-btree: Modern C++ B-tree containers (github.com)](https://github.com/Kronuz/cpp-btree)

哈希表：STL中的unordered_map