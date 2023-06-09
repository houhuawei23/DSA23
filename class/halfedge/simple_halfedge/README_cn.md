# 半边表数据结构

该项目用c语言实现了一个用于三维网格操作的半边表数据结构。半边表数据结构是一种功能强大且多功能的多边形网格表示法，可以有效地遍历和操作网格的元素（顶点、边和面）。

## 功能

- 支持具有顶点、半边和面的三维网格
- 有效地遍历和操作网格元素
- 支持网格查询，例如查找相邻的顶点、边和面
- 计算顶点之间的距离并检索连接两个顶点的半边
- 允许添加和更新网格元素

### 半边表结构与原理示意图

<img title="struct_schematic" src="./pictures/struct_schematic.jpg" alt="struct_schematic.jpg" width="466" data-align="center">

<img src="./pictures/both.png">


## 实验环境

本项目在以下环境中进行了测试：

- 操作系统：Windows 11 Pro
- 版本：22H2
- 处理器：11 代 Intel(R) Core(TM) i7-11800H @ 2.30GHz 2.30 GHz
- 系统类型：64 位操作系统，基于 x64 的处理器

请确保您的开发环境与上述环境相似，以确保项目正常运行。如有不同，请根据您的系统环境进行适当调整。

## 项目结构

项目由以下文件和目录组成：

- `README`：提供项目概述、功能和使用说明。
- `Makefile`：自动化项目的构建过程。
- `main/`：
  - `main.c`：主程序，演示如何使用半边表数据结构及其相关函数。
- `structures/`：
  - `vertex.c`：实现顶点结构及其相关函数的文件。
  - `halfedge.c`：实现半边结构及其相关函数的文件。
  - `face.c`：实现面结构及其相关函数的文件。
  - `mesh.c`：实现网格结构及其相关函数的文件。
  - `include/`：
    - `vertex.h`：顶点结构及其相关函数的头文件。
    - `halfedge.h`：半边结构及其相关函数的头文件。
    - `face.h`：面结构及其相关函数的头文件。
    - `mesh.h`：网格结构及其相关函数的头文件。

## 使用方法

1. 克隆仓库。
    `git clone https://github.com/houhuawei23/DSA23.git`
    项目地址：https://github.com/houhuawei23/DSA23
2. 使用提供的Makefile编译项目，通过在命令提示符或终端中运行 `make`。
3. 运行编译后的可执行文件 `main.exe`，查看半边表数据结构的演示。

## 示例

`main.c` 文件演示了如何使用半边表数据结构，通过创建一个由4个顶点、10个半边和2个面组成的简单网格。然后，示例演示了各种操作，如向网格添加元素、更新其属性以及查询网格信息。最后，示例展示了顶点、半边和面的遍历，以及每个组件的相邻元素遍历。

测试图形示意：
<img src="./pictures/test_mesh.jpg" width = 450>

## 作者信息

- 作者：侯华玮

- 邮箱：2589622350@qq.com

- Github：[houhuawei23](https://github.com/houhuawei23)
  
  ## 许可证

本项目在MIT许可证下提供。有关更多信息，请参阅 `LICENSE` 文件。