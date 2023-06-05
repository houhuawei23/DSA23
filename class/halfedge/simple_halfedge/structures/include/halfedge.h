/*declare HalfEdge sructures and operations*/
#ifndef _HALFEDGE_H_
#define _HALFEDGE_H_

typedef struct Vertex Vertex;
typedef struct Face Face;
typedef struct Mesh Mesh;
typedef struct HalfEdge HalfEdge;
typedef struct HalfEdge{
    int index;
    Vertex *dest;
    Face *face;
    HalfEdge *pair;
    HalfEdge *next;
}HalfEdge;

HalfEdge *InitHalfEdge(int index, Vertex *dest, Face *face, HalfEdge *pair, HalfEdge *next);
void DestroyHalfEdge(HalfEdge *he);
void PrintHalfEdge(HalfEdge *he);
void UpdateEdgeDest(HalfEdge *he, Vertex *dest);
void UpdateEdgeFace(HalfEdge *he, Face *face);
void UpdateEdgePair(HalfEdge *he, HalfEdge *pair);
void UpdateEdgeNext(HalfEdge *he, HalfEdge *next);
void TraverseEdgeAdjFace(HalfEdge *he);

#endif
/*
HalfEdge:
Data:
    one dest vertex     : Vertex pointer
    one face            : Face pointer
    one pair HalfEdge   : HalfEdge pointer
    one next HalfEdge   : HalfEdge pointer
OP:
    InitHalfEdge:
        Input: dest,face,pair,next
        Precondition: legal dest,face,pair,next
        Process: Init a halfedge
        Output: a halfedge pointer
        Postcondition: None
    DestroyHalfEdge:
        Input: a halfedge pointer
        Precondition: legal halfedge pointer
        Process: free the halfedge
        Output: None
        Postcondition: None
    PrintHalfEdge:
        Input: a halfedge pointer
        Precondition: legal halfedge pointer
        Process: print the halfedge info: dest,face,pair,next
        Output: None
        Postcondition: None
    TraverseEdgeAdjFace:
        Input: a halfedge pointer
        Precondition: legal halfedge pointer
        Process: traverse the adjacent face of the halfedge
        Output: None
        Postcondition: None
    
*/
