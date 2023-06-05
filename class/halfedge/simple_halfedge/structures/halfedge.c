/*defination of halfedge*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "halfedge.h"
#include "vertex.h"
#include "face.h"

HalfEdge *InitHalfEdge(int index, Vertex *dest, Face *face, HalfEdge *pair, HalfEdge *next)
{
    HalfEdge *he = (HalfEdge *)malloc(sizeof(HalfEdge));
    if (he == NULL)
    {
        printf("HalfEdge malloc failed!\n");
        return NULL;
    }
    he->index = index;
    he->dest = dest;
    he->face = face;
    he->pair = pair;
    he->next = next;
    return he;
}

void DestroyHalfEdge(HalfEdge *he)
{
    free(he);
}

void PrintHalfEdge(HalfEdge *he)
{
    printf("half edge index: %d\n", he->index);
    printf("dest vertex:\n");
    PrintVertex(he->dest);
    printf("face index:%d\n", he->face->index);
    printf("pair edge index: %d\n", he->pair->index);
    printf("next edge index: %d\n", he->next->index);
    // PrintFace(he->face);
    // printf("pair edge dest vertex:\n");
    // PrintVertex(he->pair->dest);
    // printf("next edge dest vertex:\n");
    // PrintVertex(he->next->dest);
}
void UpdateEdgeDest(HalfEdge *he, Vertex *dest)
{
    he->dest = dest;
}
void UpdateEdgeFace(HalfEdge *he, Face *face)
{
    he->face = face;
}
void UpdateEdgePair(HalfEdge *he, HalfEdge *pair)
{
    he->pair = pair;
}
void UpdateEdgeNext(HalfEdge *he, HalfEdge *next)
{
    he->next = next;
}
void TraverseEdgeAdjFace(HalfEdge *he)
{
    printf("adj face0:\n");
    printf("face index:%d\n", he->face->index);
    // PrintFace(he->face);
    if (he->pair->face != NULL)
    {
        printf("adj face1:\n");
        PrintFace(he->pair->face);
    }
}