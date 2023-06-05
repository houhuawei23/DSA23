/*defination of vertex*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "face.h"
#include "vertex.h"
#include "halfedge.h"
Vertex *InitVertex (int index, double x, double y, double z, \
                    struct HalfEdge *outedge)
{
    Vertex *v = (Vertex *)malloc(sizeof(Vertex));
    v->index = index;
    v->x = x;
    v->y = y;
    v->z = z;
    v->outedge = outedge;
    return v;
}
void DestroyVertex(Vertex *v)
{
    free(v);
}
void PrintVertex(Vertex *v)
{
    printf("Vertex %d: (%f, %f, %f)\n", v->index,v->x, v->y, v->z);
}
void UpdateXYZ(Vertex *v, double x, double y, double z){
    v->x = x;
    v->y = y;
    v->z = z;
}
void UpdateOutEdge(Vertex *v, struct HalfEdge *outedge){
    v->outedge = outedge;
}

double DisOf2Vertex(Vertex *v1, Vertex *v2)
{
    return sqrt((v1->x - v2->x) * (v1->x - v2->x) +
                (v1->y - v2->y) * (v1->y - v2->y) +
                (v1->z - v2->z) * (v1->z - v2->z));
}
HalfEdge *Find2VertexHalfEdge(Vertex *v1, Vertex *v2){
    HalfEdge *tmphe = v1->outedge;
    Vertex *tmpv;
    do{
        tmpv = tmphe->dest;
        if(tmpv == v2){
            printf("Find the halfedge between two vertex\n");
            return tmphe;
        }
        tmphe = tmphe->pair->next;
    }while(tmphe != v1->outedge);
    printf("Can't find the halfedge between two vertex\n");
    return NULL;
}
void TraverseVertexAdjEdge(Vertex *v){
    int cnt = 0;
    HalfEdge *tmphe = v->outedge;
    do{
        cnt++;
        printf("adj edge index: %d\n", tmphe->index);
        // print adj edge dest vertex
        // avoid recursive call
        // printf("adj edge dest vertex %d:\n", cnt);
        // PrintVertex(tmphe->dest);
        // next edge
        tmphe = tmphe->pair->next;
    }while(tmphe != v->outedge);
}
void TraverseVertexAdjFace(Vertex *v){
    int cnt = 0;
    HalfEdge *tmphe = v->outedge;
    do{
        cnt++;
        if(tmphe->face != NULL)
            printf("adj face index: %d\n", tmphe->face->index);
        // tmpface = InitFace(0,tmphe);
        // PrintFace(tmpface);
        // next edge
        tmphe = tmphe->pair->next;
    }while(tmphe != v->outedge);

}
void TraverseVertexAdjVertex(Vertex *v){
    int cnt = 0;
    HalfEdge *tmphe = v->outedge;
    do{
        cnt++;
        // print adj edge dest vertex
        // avoid recursive call
        printf("adj vertex %d:\n", cnt);
        PrintVertex(tmphe->dest);
        // next edge
        tmphe = tmphe->pair->next;
    }while(tmphe != v->outedge);
}