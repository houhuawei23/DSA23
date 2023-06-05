/*declare face structure and operations*/
#ifndef _FACE_H_
#define _FACE_H_

typedef struct Vertex Vertex;
typedef struct Mesh Mesh;
typedef struct HalfEdge HalfEdge;

typedef struct Face{
    int index;
    HalfEdge *edge;
}Face;

Face *InitFace(int index, HalfEdge *edge);
void DestroyFace(Face *face);
void PrintFace(Face *face);
void UpdateFaceEdge(Face *face, HalfEdge *edge);
void TraverseFaceAdjEdge(Face *face);
void TraverseFaceAdjVertex(Face *face);
void TraverseFaceAdjFace(Face *face);
#endif
/*
Face:
Data: 
    one edge : HalfEdge pointer
OP:
    InitFace:
        Input: edge
        Precondition: legal edge
        Process: Init a face
        Output: a face pointer
        Postcondition: None
    DestroyFace:
        Input: a face pointer
        Precondition: legal face pointer
        Process: free the face
        Output: None
        Postcondition: None
    PrintFace:
        Input: a face pointer
        Precondition: legal face pointer
        Process: print the face info: 3 points, edge
        Output: None
        Postcondition: None
    TraverseFaceAdjEdge:
        Input: a face pointer
        Precondition: legal face pointer
        Process: traverse the adjacent edge of the face
        Output: None
        Postcondition: None
    TraverseFaceAdjVertex:
        Input: a face pointer
        Precondition: legal face pointer
        Process: traverse the adjacent vertex of the face
        Output: None
        Postcondition: None
    
*/
