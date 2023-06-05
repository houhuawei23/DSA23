/*
测试创建的HalfEdge, Vertex, Face, Mesh结构体以及相关函数
编译：
gcc -o -g -Wall main main.c halfedge.c vertex.c face.c mesh.c
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "halfedge.h"
#include "vertex.h"
#include "face.h"
#include "mesh.h"


int main(){
    // 全局数据
    Mesh *mesh;
    int vertex_count = 4;
    int half_edge_count = 10;
    int face_count = 2;
    // mesh
    mesh = InitMesh("mymesh", 0, vertex_count, half_edge_count, face_count);
// 添加vertex 半边NULL
    // 0 (0,0,0); 1 (1,0,0); 2 (0,1,0); 3 (0,0,1) 
    AddVertex(mesh, *InitVertex(0, 0.0, 0.0, 0.0, NULL)); 
    AddVertex(mesh, *InitVertex(1, 1.0, 0.0, 0.0, NULL));
    AddVertex(mesh, *InitVertex(2, 0.0, 1.0, 0.0, NULL));
    AddVertex(mesh, *InitVertex(3, 0.0, 0.0, 1.0, NULL));
// 添加半边，pair,next,face置位NULL
    // he0 0->1; he1 1->0; he2 1->2; he3 2->1; he4 2->3; 
    // he5 3->2; he6 3->0; he7 0->3; he8 0->2; he9 2->0;
    int he0_idx = AddHalfEdge(mesh, *InitHalfEdge(0,&mesh->vertices[1], NULL, NULL, NULL));
    int he1_idx = AddHalfEdge(mesh, *InitHalfEdge(1,&mesh->vertices[0], NULL, NULL, NULL));
    int he2_idx = AddHalfEdge(mesh, *InitHalfEdge(2,&mesh->vertices[2], NULL, NULL, NULL));
    int he3_idx = AddHalfEdge(mesh, *InitHalfEdge(3,&mesh->vertices[1], NULL, NULL, NULL));
    int he4_idx = AddHalfEdge(mesh, *InitHalfEdge(4,&mesh->vertices[3], NULL, NULL, NULL));
    int he5_idx = AddHalfEdge(mesh, *InitHalfEdge(5,&mesh->vertices[2], NULL, NULL, NULL));
    int he6_idx = AddHalfEdge(mesh, *InitHalfEdge(6,&mesh->vertices[0], NULL, NULL, NULL));
    int he7_idx = AddHalfEdge(mesh, *InitHalfEdge(7,&mesh->vertices[3], NULL, NULL, NULL));
    int he8_idx = AddHalfEdge(mesh, *InitHalfEdge(8,&mesh->vertices[2], NULL, NULL, NULL));
    int he9_idx = AddHalfEdge(mesh, *InitHalfEdge(9,&mesh->vertices[0], NULL, NULL, NULL));
// 更新所有半边的pair
    // he0-he1; he2-he3; he4-he5; he6-he7; he8-he9;
    UpdateEdgePair(&(mesh->half_edges[he0_idx]), &(mesh->half_edges[he1_idx])); // 0-1
    UpdateEdgePair(&(mesh->half_edges[he1_idx]), &(mesh->half_edges[he0_idx]));
    UpdateEdgePair(&(mesh->half_edges[he2_idx]), &(mesh->half_edges[he3_idx])); // 2-3
    UpdateEdgePair(&(mesh->half_edges[he3_idx]), &(mesh->half_edges[he2_idx]));
    UpdateEdgePair(&(mesh->half_edges[he4_idx]), &(mesh->half_edges[he5_idx])); // 4-5
    UpdateEdgePair(&(mesh->half_edges[he5_idx]), &(mesh->half_edges[he4_idx]));
    UpdateEdgePair(&(mesh->half_edges[he6_idx]), &(mesh->half_edges[he7_idx])); // 6-7
    UpdateEdgePair(&(mesh->half_edges[he7_idx]), &(mesh->half_edges[he6_idx]));
    UpdateEdgePair(&(mesh->half_edges[he8_idx]), &(mesh->half_edges[he9_idx])); // 8-9
    UpdateEdgePair(&(mesh->half_edges[he9_idx]), &(mesh->half_edges[he8_idx]));
// 更新所有半边的next()
    UpdateEdgeNext(&(mesh->half_edges[he0_idx]), &(mesh->half_edges[he2_idx]));// he0->he2;
    UpdateEdgeNext(&(mesh->half_edges[he1_idx]), &(mesh->half_edges[he7_idx]));// he1->he7;
    UpdateEdgeNext(&(mesh->half_edges[he2_idx]), &(mesh->half_edges[he9_idx]));// he2->he9;
    // he3->NULL
    UpdateEdgeNext(&(mesh->half_edges[he4_idx]), &(mesh->half_edges[he6_idx]));// he4->he6;
    // he5->NULL
    UpdateEdgeNext(&(mesh->half_edges[he6_idx]), &(mesh->half_edges[he8_idx]));// he6->he8;
    // he7->NULL
    UpdateEdgeNext(&(mesh->half_edges[he8_idx]), &(mesh->half_edges[he4_idx]));// he8->he4;
    UpdateEdgeNext(&(mesh->half_edges[he9_idx]), &(mesh->half_edges[he0_idx]));// he9->he0;
// 添加面
    AddFace(mesh, *InitFace(0, &mesh->half_edges[he0_idx]));
    AddFace(mesh, *InitFace(1, &mesh->half_edges[he4_idx]));
// 更新所有半边的face
    UpdateEdgeFace(&mesh->half_edges[he0_idx], &mesh->faces[0]);
    UpdateEdgeFace(&mesh->half_edges[he1_idx], &mesh->faces[0]);
    UpdateEdgeFace(&mesh->half_edges[he2_idx], &mesh->faces[0]);
    // he3->NULL
    UpdateEdgeFace(&mesh->half_edges[he4_idx], &mesh->faces[1]);
    // he5->face = NULL
    UpdateEdgeFace(&mesh->half_edges[he6_idx], &mesh->faces[1]);
    // he7->face = NULL
    UpdateEdgeFace(&mesh->half_edges[he8_idx], &mesh->faces[1]);
    // he9->face = NULL

// 更新顶点的outedge
    UpdateOutEdge(&mesh->vertices[0], &mesh->half_edges[he0_idx]);
    UpdateOutEdge(&mesh->vertices[1], &mesh->half_edges[he2_idx]);
    UpdateOutEdge(&mesh->vertices[2], &mesh->half_edges[he4_idx]);
    UpdateOutEdge(&mesh->vertices[3], &mesh->half_edges[he6_idx]);
    // 打印Mesh信息
    printf("Mesh Information:\n");
    PrintMesh(mesh);

    // 测试Mesh遍历vertex, halfedge, face
    printf("\nTraverse Mesh Vertices:\n");
    TraverseMeshVertices(mesh);

    printf("\nTraverse Mesh HalfEdges:\n");
    TraverseMeshHalfEdges(mesh);

    printf("\nTraverse Mesh Faces:\n");
    TraverseMeshFaces(mesh);

    // 测试查询
    Vertex *v1 = GetVertex(mesh, 0);
    Vertex *v2 = GetVertex(mesh, 1);
    // 测试两点间距离
    printf("\nDistance between Vertex 0 and Vertex 1: %f\n", DisOf2Vertex(v1, v2));
    // 查找两点间半边
    printf("\nHalfEdge between Vertex 0 and Vertex 1:\n");
    printf("inedge index: %d\n",Find2VertexHalfEdge(v1, v2)->index);
    // 测试结点遍历邻接边，邻接面，邻接点
    printf("\nTraverse Vertex 0 Adjacent Edges:\n");
    TraverseVertexAdjEdge(v1);

    printf("\nTraverse Vertex 0 Adjacent Faces:\n");
    TraverseVertexAdjFace(v1);

    printf("\nTraverse Vertex 0 Adjacent Vertices:\n");
    TraverseVertexAdjVertex(v1);
    // 测试半边遍历邻接面
    printf("\nTraverse HalfEdge 0 Adjacent Faces:\n");
    TraverseEdgeAdjFace(&mesh->half_edges[he0_idx]);
    // 测试面遍历邻接边，邻接点，邻接面
    printf("\nTraverse Face 0 Adjacent Edges:\n");
    TraverseFaceAdjEdge(&mesh->faces[0]);
    printf("\nTraverse Face 0 Adjacent Vertices:\n");
    TraverseFaceAdjVertex(&mesh->faces[0]);
    printf("\nTraverse Face 0 Adjacent Faces:\n");
    TraverseFaceAdjFace(&mesh->faces[0]);
    // 销毁Mesh
    DestroyMesh(mesh);

    return 0;
}