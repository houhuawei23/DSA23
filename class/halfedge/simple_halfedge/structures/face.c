/*defination of face*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "face.h"
#include "vertex.h"
#include "halfedge.h"

Face *InitFace(int index, HalfEdge* he)
{
    Face *f = (Face*)malloc(sizeof(Face));
    if(f == NULL){
        printf("Face malloc failed!\n");
        return NULL;
    }
    f->index = index;
    f->edge = he;
    return f;
}

void DestroyFace(Face *f)
{
    free(f);
}

void PrintFace(Face *f)
{
    printf("3 adj points of face:\n");
    TraverseFaceAdjVertex(f);
}
void UpdateEdge(Face *face, HalfEdge *edge){
    face->edge = edge;
}


void TraverseFaceAdjVertex(Face *f)
{
    int cnt = 0;
    HalfEdge *tmphe = f->edge;
    // 3 adj edges formed a Circular List of the face
    do{
        cnt++;
        // print adj vertex
        // avoid recursive call
        printf("adj vertex %d:\n", cnt);
        PrintVertex(tmphe->dest);
        // next edge
        tmphe = tmphe->next;
    }while(tmphe != f->edge);
}

void TraverseFaceAdjEdge(Face *f)
{
    int cnt = 0;
    HalfEdge *tmphe = f->edge;
    // 3 adj edges formed a Circular List of the face
    do{
        cnt++;
        printf("adj edge index %d:\n", tmphe->index);
        // print adj edge
        // avoid recursive call
        // printf("dest vertex of adj edge %d:\n", cnt);
        // PrintVertex(tmphe->dest);
        // next edge
        tmphe = tmphe->next;
    }while(tmphe != f->edge);
}

void TraverseFaceAdjFace(Face *face){
    HalfEdge* he = face->edge;
    for(int cnt = 0; cnt < 3; cnt++){
        if(he->pair->face != NULL){
            printf("adj face %d:", cnt);
            printf("face index: %d\n",he->pair->face->index);
        }
        he = he->next;
    }
}