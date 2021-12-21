# Programming Assignment 2 EX1&EX2

**注意：本目录版本为<u>不使用</u>B+树、B树和哈希进行数据库读写优化的版本，仅仅实现了数据库**。

## ✨文件夹介绍

- **include**文件夹放置头文件
- **src**文件夹放置源码文件
- **database_auto**文件夹放置自动测试模式需要用到的数据
- **report**文件夹放置生成的report

## 💎文件介绍

- **database.h**：Block与Relation相关函数的定义
- **dataType.h**：数据库相关定义
- **information.h**：来自Programming Assignment1的相关定义，包括原始数据类、报告类、斐波拉契堆类
- **helper.cpp**：一些协助函数，例如计算日期差，生成随机病人信息等
- **information.cpp**：大部分实现的代码，包括原始数据类、报告类、斐波拉契堆类、数据库类等
- **main.cpp**：主程序

## 🖍思路介绍

一个Database中有四个Relation，分别保存了每个病人的Person、Medical Status、Registration、Treatment这四类信息。每一个relation里有多个row，每个row代表一条记录。

在我们的实现中，Relation由Block列表实现，每个Block中有长度固定的缓冲区和主储存区。

在查询主键的过程中，我们将斐波那契堆每一个node存储的数据由assignment 1的整个person类，变成了只存person的id，这样极大的减少了内存的空间。另外，不同于assignment1，我们对于数据的操作不再依赖于文件，而是直接用数据库进行person的存储、修改、治疗等工作，这样可以减少程序读写文件的时间，加快程序运行速度。

## 👉main的使用：

我们的程序支持自动测试和手动测试两种模式。在自动测试模式中，程序会自动准备病人信息并在合适的时间把病人信息输入到系统中，每一天的变化都会在控制台上显示出来，并在7天和30天的时候生成每周报告和每月报告；在手动测试模式中，你可以手动输入每个病人的信息（不推荐），或使用自动信息生成来生成你需要的任意数量的病人信息（推荐），并控制系统的运行和报告的生成。

**注意：在运行main之前，请确保report文件夹存在；在运行自动测试前，请解压缩database.zip并确保database文件夹及其中的文件存在。**

