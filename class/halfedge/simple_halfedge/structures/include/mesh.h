#ifndef __MESH_H__
#define __MESH_H__

typedef struct Vertex Vertex;
typedef struct Face Face;
typedef struct HalfEdge HalfEdge;

typedef struct Mesh
{
    char* name;
    int index;
    Vertex *vertices;
    int vertex_count;
    int max_vertex_count;
    HalfEdge *half_edges;
    int half_edge_count;
    int max_half_edge_count;
    Face *faces;
    int face_count;
    int max_face_count;
} Mesh;
// init with name, index, vertex_count, half_edge_count, face_count
Mesh *InitMesh(char *name, int index, int vertex_count, int half_edge_count, int face_count);
//int InitMesh(Mesh *mesh, int vertex_count, int half_edge_count, int face_count);
int DestroyMesh(Mesh *mesh);
void PrintMesh(Mesh *mesh);
// return the listid of the vertex, not global index
int AddVertex(Mesh *mesh, Vertex vertex);    
//  return the listid of the half edge    
int AddHalfEdge(Mesh *mesh, HalfEdge half_edge);
// return the listid of the face 
int AddFace(Mesh *mesh, Face face);

void UpdateMeshVertex(Mesh *mesh, int index, Vertex vertex);
void UpdateMeshHalfEdge(Mesh *mesh, int index, HalfEdge half_edge);
void UpdateMeshFace(Mesh *mesh, int index, Face face);
//根据全局索引获取顶点，半边，面
Vertex *GetVertex(Mesh *mesh, int index); 
HalfEdge *GetHalfEdge(Mesh *mesh, int index);
Face *GetFace(Mesh *mesh, int index);

void TraverseMeshVertices(Mesh *mesh);
void TraverseMeshHalfEdges(Mesh *mesh);
void TraverseMeshFaces(Mesh *mesh);

#endif

/*
Mesh:
Data:
    Vertex *vertices;
    int vertex_count;
    HalfEdge *half_edges;
    int half_edge_count;
    Face *faces;
    int face_count;
OP:
    InitMesh:
        Input: Mesh *mesh, int vertex_count, int half_edge_count, int face_count;
        Preconditions: mesh is not NULL
        Process: allocate memory for vertices, half_edges, faces
        Output: 0 for success, -1 for failure
        Postconditions: mesh->vertices, mesh->half_edges, mesh->faces are not NULL
    DestroyMesh:
        Input: Mesh *mesh
        Preconditions: mesh is not NULL
        Process: free memory for vertices, half_edges, faces
        Output: 0 for success, -1 for failure
        Postconditions: mesh->vertices, mesh->half_edges, mesh->faces are NULL
    PrintMesh:
        Input: Mesh *mesh
        Preconditions: mesh is not NULL
        Process: print mesh
        Output: None
        Postconditions: mesh is not changed
    AddVertex:
        Input: Mesh *mesh, Vertex vertex
        Preconditions: mesh is not NULL
        Process: add vertex to mesh
        Output: the index of the vertex
        Postconditions: mesh->vertices are not NULL
    AddHalfEdge:
        Input: Mesh *mesh, HalfEdge half_edge
        Preconditions: mesh is not NULL
        Process: add half_edge to mesh
        Output: the index of the half_edge
        Postconditions: mesh->half_edges are not NULL
    AddFace:
        Input: Mesh *mesh, Face face
        Preconditions: mesh is not NULL
        Process: add face to mesh
        Output: the index of the face
        Postconditions: mesh->faces are not NULL
    TraverseMeshVertices:
        Input: Mesh *mesh
        Preconditions: mesh is not NULL
        Process: traverse mesh vertices
        Output: None
        Postconditions: mesh is not changed
    TraverseMeshHalfEdges:
        Input: Mesh *mesh
        Preconditions: mesh is not NULL
        Process: traverse mesh half_edges
        Output: None
        Postconditions: mesh is not changed
    TraverseMeshFaces:
        Input: Mesh *mesh
        Preconditions: mesh is not NULL
        Process: traverse mesh faces
        Output: None
        Postconditions: mesh is not changed
*/