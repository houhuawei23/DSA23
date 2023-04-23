/*
定义实现半边表结构
*/
#include <stdio.h>
#include <stdlib.h>

// 顶点结构
typedef struct Vertex
{
    float x, y, z;
    struct HalfEdge *half_edge; // 从此顶点出发的任意一条半边
} Vertex;

// 半边结构
typedef struct HalfEdge
{
    struct Vertex *origin; // 起始顶点
    struct HalfEdge *twin; // 对偶半边
    struct HalfEdge *next; // 下一条半边
    struct HalfEdge *prev; // 上一条半边
    struct Face *face;     // 所属面
} HalfEdge;

// 面结构
typedef struct Face
{
    struct HalfEdge *half_edge;
} Face;

// 半边表结构
typedef struct HalfEdgeMesh
{
    Vertex *vertices;   // 顶点数组
    int vertex_count;   // 顶点数量
    HalfEdge *half_edges;// 半边数组
    int half_edge_count;//  半边数量
    Face *faces;// 面数组
    int face_count;// 面数量
} HalfEdgeMesh;

// 初始化半边表结构
void init_half_edge_mesh(HalfEdgeMesh *mesh);

// 添加顶点
// 输入：mesh - 半边表结构指针, x, y, z - 顶点坐标
// 输出：新添加的顶点在数组中的索引
int add_vertex(HalfEdgeMesh *mesh, float x, float y, float z);

// 添加面
// 输入：mesh - 半边表结构指针, vertex_indices - 顶点索引数组，按逆时针顺序排列, vertex_count - 顶点数量
// 输出：新添加的面在数组中的索引
int add_face(HalfEdgeMesh *mesh, int *vertex_indices, int vertex_count);

// 删除顶点
// 输入：mesh - 半边表结构指针, vertex_index - 顶点索引
void delete_vertex(HalfEdgeMesh *mesh, int vertex_index);

// 删除面
// 输入：mesh - 半边表结构指针, face_index - 面索引
void delete_face(HalfEdgeMesh *mesh, int face_index);

// 查找给定起始顶点和目标顶点之间的半边
// 输入：mesh - 半边表结构指针, origin_vertex_index - 起始顶点索引, destination_vertex_index - 目标顶点索引
// 输出：指向找到的半边的指针，如果没有找到，则返回NULL
HalfEdge *find_half_edge(HalfEdgeMesh *mesh, int origin_vertex_index, int destination_vertex_index);

// 遍历所有面
void traverse_faces(HalfEdgeMesh *mesh, void (*callback)(Face *));

// 遍历所有顶点
void traverse_vertices(HalfEdgeMesh *mesh, void (*callback)(Vertex *));

// 遍历所有半边
void traverse_half_edges(HalfEdgeMesh *mesh, void (*callback)(HalfEdge *));

// 遍历以给定顶点为起点的所有半边
void traverse_half_edges_of_vertex(HalfEdgeMesh *mesh, int vertex_index, void (*callback)(HalfEdge *));

// 遍历一个面的所有顶点
void traverse_vertices_of_face(
    HalfEdgeMesh *mesh, int face_index, void
    // 遍历一个面的所有顶点
    // 输入：mesh - 半边表结构指针, face_index - 面索引, callback - 遍历时调用的回调函数，接受一个Vertex指针作为参数
    void traverse_vertices_of_face(HalfEdgeMesh *mesh, int face_index, void (*callback)(Vertex *)) {
        if (face_index < 0 || face_index >= mesh->face_count)
        {
            printf("Error: Invalid face index.\n");
            return;
        }

        Face *face = &(mesh->faces[face_index]);
        HalfEdge *start_edge = face->half_edge;
        HalfEdge *current_edge = start_edge;

        do
        {
            Vertex *vertex = current_edge->origin;
            callback(vertex);
            current_edge = current_edge->next;
        } while (current_edge != start_edge);
    }

    (*callback)(Vertex *));

// 遍历与给定顶点关联的所有面
void traverse_faces_of_vertex(HalfEdgeMesh *mesh, int vertex_index, void (*callback)(Face *));

// 遍历与给定顶点相邻的所有顶点
void traverse_adjacent_vertices(HalfEdgeMesh *mesh, int vertex_index, void (*callback)(Vertex *));

// 实现以上函数的具体代码，以及释放内存的函数
// ...

int main()
{
    HalfEdgeMesh mesh;
    init_half_edge_mesh(&mesh);

    // 添加顶点和面，执行其他操作
    // ...

    // 遍历示例
    traverse_faces(&mesh, &print_face_info);
    traverse_vertices(&mesh, &print_vertex_info);
    traverse_half_edges(&mesh, &print_half_edge_info);

    // 释放内存
    free_half_edge_mesh(&mesh);

    return 0;
}
