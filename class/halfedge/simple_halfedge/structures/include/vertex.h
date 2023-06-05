/*declare vertex structure and operations*/

#ifndef _VERTEX_H_
#define _VERTEX_H_

typedef struct Vertex Vertex;
typedef struct Mesh Mesh;
typedef struct HalfEdge HalfEdge;

typedef struct Vertex{
    int index;
    double x, y, z;
    struct HalfEdge *outedge;
}Vertex;

Vertex *InitVertex(int index, double x, double y, double z, struct HalfEdge *outedge);
void DestroyVertex(Vertex *v);
void PrintVertex(Vertex *v);

void UpdateXYZ(Vertex *v, double x, double y, double z);
void UpdateOutEdge(Vertex *v, struct HalfEdge *outedge);

double DisOf2Vertex(Vertex *v1, Vertex *v2);
HalfEdge *Find2VertexHalfEdge(Vertex *v1, Vertex *v2);
void TraverseVertexAdjEdge(Vertex *v);
void TraverseVertexAdjFace(Vertex *v);
void TraverseVertexAdjVertex(Vertex *v);

#endif
/*
Vertex:
Data:
    Index index: int
    Coordinate xyz : double
    one outedge : HalfEdge pointer
OP:
    InitVertex:
        Input: x,y,z,outedge
        Precondition: legal x,y,z,outedge 
        Process: Init a vertex
        Output: a vertex pointer
        Postcondition: None
    DestroyVertex:
        Input: a vertex pointer
        Precondition: legal vertex pointer
        Process: free the vertex
        Output: None
        Postcondition: None
    PrintVertex:
        Input: a vertex pointer
        Precondition: legal vertex pointer
        Process: print the vertex 
        Output: None
        Postcondition: None
    DisOf2Vertex:
        Input: two vertex pointer
        Precondition: legal vertex pointer
        Process: calculate the distance between two vertex
        Output: the distance
        Postcondition: None
    Find2VertexHalfEdge:
        Input: two vertex pointer
        Precondition: legal vertex pointer
        Process: find the halfedge between two vertex
        Output: the halfedge pointer
        Postcondition: None
    TraverseVertexAdjEdge:
        Input: a vertex pointer
        Precondition: legal vertex pointer
        Process: traverse the adjacent edge of the vertex
        Output: None
        Postcondition: None
    TraverseVertexAdjFace:
        Input: a vertex pointer
        Precondition: legal vertex pointer
        Process: traverse the adjacent face of the vertex
        Output: None
        Postcondition: None
    TraverseVertexAdjVertex:
        Input: a vertex pointer
        Precondition: legal vertex pointer
        Process: traverse the adjacent vertex of the vertex
        Output: None
        Postcondition: None
*/

