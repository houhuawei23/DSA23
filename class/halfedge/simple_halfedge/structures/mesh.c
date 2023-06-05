/*defination of struct mesh*/

#include <stdio.h>
#include <stdlib.h>

#include "mesh.h"
#include "halfedge.h"
#include "vertex.h"
#include "face.h"

// int InitMesh(Mesh *mesh, int max_vertex_count, int max_half_edge_count, int max_face_count){
//     if(mesh == NULL){
//         return -1;
//     }
//     if(max_vertex_count <0 || max_half_edge_count < 0 || max_face_count < 0){
//         return -1;
//     }
//     mesh->vertices = (Vertex *)malloc(sizeof(Vertex) * max_vertex_count);
//     if(mesh->vertices == NULL){
//         return -1;
//     }
//     mesh->vertex_count = 0;
//     mesh->max_vertex_count = max_vertex_count;
//     mesh->half_edges = (HalfEdge *)malloc(sizeof(HalfEdge) * max_half_edge_count);
//     if(mesh->half_edges == NULL){
//         return -1;
//     }
//     mesh->half_edge_count = 0;
//     mesh->max_half_edge_count = max_half_edge_count;
//     mesh->faces = (Face *)malloc(sizeof(Face) * max_face_count);
//     if(mesh->faces == NULL){
//         return -1;
//     }
//     mesh->face_count = 0;
//     mesh->max_face_count = max_face_count;
//     return 0;
    
// }
Mesh *InitMesh(char *name, int index, int vertex_count, int half_edge_count, int face_count){
    if(vertex_count <0 || half_edge_count < 0 || face_count < 0){
        return NULL;
    }
    Mesh *mesh = (Mesh *)malloc(sizeof(Mesh));
    if(mesh == NULL){
        return NULL;
    }

    mesh->vertices = (Vertex *)malloc(sizeof(Vertex) * vertex_count);
    if(mesh->vertices == NULL){
        return NULL;
    }
    mesh->half_edges = (HalfEdge *)malloc(sizeof(HalfEdge) * half_edge_count);
    if(mesh->half_edges == NULL){
        return NULL;
    }
    mesh->faces = (Face *)malloc(sizeof(Face) * face_count);
    if(mesh->faces == NULL){
        return NULL;
    }
    mesh->name = name;
    mesh->index = index;
    mesh->face_count = 0;
    mesh->vertex_count = 0;
    mesh->half_edge_count = 0;
    mesh->max_vertex_count = vertex_count;
    mesh->max_half_edge_count = half_edge_count;
    mesh->max_face_count = face_count;
    return mesh;
}
int DestroyMesh(Mesh *mesh){
    if(mesh == NULL){
        return -1;
    }
    free(mesh->vertices);
    mesh->vertices = NULL;
    mesh->vertex_count = 0;
    free(mesh->half_edges);
    mesh->half_edges = NULL;
    mesh->half_edge_count = 0;
    free(mesh->faces);
    mesh->faces = NULL;
    mesh->face_count = 0;
    return 0;
}
void PrintMesh(Mesh *mesh){
    printf("mesh: %s, index: %d\n", mesh->name, mesh->index);
    printf("num of vertices: %d, num of half_edges: %d, num of faces: %d\n", \
            mesh->vertex_count, mesh->half_edge_count, mesh->face_count);
    for(int i = 0; i < mesh->vertex_count; i++){
        printf("vertex %d: ", i);
        printf("index of vertex: %d\n", mesh->vertices[i].index);
    }
    for(int i = 0; i < mesh->half_edge_count; i++){
        printf("half_edge %d: ", i);
        printf("index of half_edge: %d\n", mesh->half_edges[i].index);
    }
    for(int i = 0; i < mesh->face_count; i++){
        printf("face %d: ", i);
        printf("index of face: %d\n", mesh->faces[i].index);
    }
}

int AddVertex(Mesh *mesh, Vertex vertex){
    if(mesh == NULL){
        return -1;
    }
    if(mesh->vertex_count >= mesh->max_vertex_count){
        return -1;
    }
    mesh->vertices[mesh->vertex_count] = vertex;
    mesh->vertex_count++;
    return mesh->vertex_count - 1;
}
int AddHalfEdge(Mesh *mesh, HalfEdge half_edge){
    if(mesh == NULL){
        return -1;
    }
    if(mesh->half_edge_count >= mesh->max_half_edge_count){
        return -1;
    }
    mesh->half_edges[mesh->half_edge_count] = half_edge;
    mesh->half_edge_count++;
    return mesh->half_edge_count - 1;
}
int AddFace(Mesh *mesh, Face face){
    if(mesh == NULL){
        return -1;
    }
    if(mesh->face_count >= mesh->max_face_count){
        return -1;
    }
    mesh->faces[mesh->face_count] = face;
    mesh->face_count++;
    return mesh->face_count - 1;
}
// update
void UpdateMeshVertex(Mesh *mesh, int index, Vertex vertex){
    if(mesh == NULL){
        return;
    }
    if(index < 0 || index >= mesh->vertex_count){
        return;
    }
    mesh->vertices[index] = vertex;
}
void UpdateMeshHalfEdge(Mesh *mesh, int index, HalfEdge half_edge){
    if(mesh == NULL){
        return;
    }
    if(index < 0 || index >= mesh->half_edge_count){
        return;
    }
    mesh->half_edges[index] = half_edge;
}
void UpdateMeshFace(Mesh *mesh, int index, Face face){
    if(mesh == NULL){
        return;
    }
    if(index < 0 || index >= mesh->face_count){
        return;
    }
    mesh->faces[index] = face;
}
//根据全局索引获取顶点，半边，面
Vertex *GetVertex(Mesh *mesh, int index){
    if(mesh == NULL){
        return NULL;
    }
    if(index < 0 || index >= mesh->vertex_count){
        return NULL;
    }
    return &(mesh->vertices[index]);
}
HalfEdge *GetHalfEdge(Mesh *mesh, int index){
    if(mesh == NULL){
        return NULL;
    }
    if(index < 0 || index >= mesh->half_edge_count){
        return NULL;
    }
    return &(mesh->half_edges[index]);
}
Face *GetFace(Mesh *mesh, int index){
    if(mesh == NULL){
        return NULL;
    }
    if(index < 0 || index >= mesh->face_count){
        return NULL;
    }
    return &(mesh->faces[index]);
}
void TraverseMeshVertices(Mesh *mesh){
    for(int i = 0; i < mesh->vertex_count; i++){
        printf("vertex %d: ", i);
        printf("index of vertex: %d\n", mesh->vertices[i].index);
    }
}
void TraverseMeshHalfEdges(Mesh *mesh){
    for(int i = 0; i < mesh->half_edge_count; i++){
        printf("half_edge %d: ", i);
        printf("index of half_edge: %d\n", mesh->half_edges[i].index);
    }
}
void TraverseMeshFaces(Mesh *mesh){
    for(int i = 0; i < mesh->face_count; i++){
        printf("face %d: ", i);
        printf("index of face: %d\n", mesh->faces[i].index);
    }
}