# Programming Assignment 2 Ex4

## 🧡文件夹介绍

- **include**文件夹放置头文件
- **src**文件夹放置源码文件

## 💛文件介绍

- **database.h**: 数据库相关定义
- **dataType.h**: 病人信息相关定义
- **databse.cpp**:数据库的读入和相邻距离的寻找，包含输出函数
- **test.cpp**：放置测试需要用到的数据

## 💜思路介绍

一个Database中有四个Relation，分别保存了每个病人的Person、Medical Status、Registration、Treatment这四类信息。每个relation中由有序的block储存数据，每个Block中有长度固定的缓冲区和主储存区。

在输入病人信息时，相关地址信息会被读取，用于距离计算。

对于不同的条件判断，可以给出不同邻居的信息。