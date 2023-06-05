# Half-Edge Data Structure

This project implements a Half-Edge data structure for 3D mesh manipulation. The Half-Edge data structure is a powerful and versatile representation of polygonal meshes that allows for efficient traversal and manipulation of the mesh's elements (vertices, edges, and faces).

## Features

- Supports 3D mesh with vertices, half-edges, and faces
- Efficient traversal and manipulation of mesh elements
- Supports mesh queries such as finding adjacent vertices, edges, and faces
- Calculates distances between vertices and retrieves half-edges connecting two vertices
- Allows for mesh element addition and updates

## Experimental Environment

This project has been tested in the following environment:

- Operating System: Windows 11 Pro
- Version: 22H2
- Processor: 11th Gen Intel(R) Core(TM) i7-11800H @ 2.30GHz 2.30 GHz
- System Type: 64-bit operating system, x64-based processor

Please ensure that your development environment is similar to the one mentioned above to ensure the proper functioning of the project. If there are differences, please make appropriate adjustments based on your system environment.

## Project Structure

The project consists of the following files and directories:

- `README`: Provides an overview of the project, its features, and usage instructions.
- `Makefile`: Automates the build process of the project.
- `main/`:
    - `main.c`: The main program demonstrating the use of the Half-Edge data structure and its associated functions.
- `structures/`:
    - `vertex.c`: Implementation file for the Vertex structure and related functions.
    - `halfedge.c`: Implementation file for the Half-Edge structure and related functions.
    - `face.c`: Implementation file for the Face structure and related functions.
    - `mesh.c`: Implementation file for the Mesh structure and related functions.
    - `include/`:
        - `vertex.h`: Header file for the Vertex structure and related functions.
        - `halfedge.h`: Header file for the Half-Edge structure and related functions.
        - `face.h`: Header file for the Face structure and related functions.
        - `mesh.h`: Header file for the Mesh structure and related functions.
## Usage

1. Clone the repository.
    `git clone https://github.com/houhuawei23/DSA23.git`
    项目地址：https://github.com/houhuawei23/DSA23
2. Compile the project using the provided Makefile by running `make` in the command prompt or terminal.
3. Run the compiled executable `main.exe` to see a demonstration of the Half-Edge data structure.

## Example

The `main.c` file demonstrates the usage of the Half-Edge data structure by creating a simple mesh consisting of 4 vertices, 10 half-edges, and 2 faces. The example then demonstrates various operations such as adding elements to the mesh, updating their properties, and querying the mesh for information. Finally, the example showcases traversals for vertices, half-edges, and faces, as well as adjacent elements for each of these components.

## Information

- Author：HUA WEIHOU
- Email：2589622350@qq.com
- Github：[houhuawei23](https://github.com/houhuawei23)

## License

This project is provided under the MIT License. See the `LICENSE` file for more information.