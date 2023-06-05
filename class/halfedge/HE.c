
typedef struct HE_edge
{

    struct HE_vert *vert; // vertex at the end of the half-edge
    struct HE_edge *pair; // oppositely oriented adjacent half-edge
    struct HE_face *face; // face the half-edge borders
    struct HE_edge *next; // next half-edge around the face
}HE_edge;
typedef struct HE_vert
{

    float x;
    float y;
    float z;
    // 从此顶点出发的任意一条半边
    struct HE_edge *edge; // one of the half-edges emantating from the vertex
}HE_vert;

typedef struct HE_face
{

    struct HE_edge *edge; // one of the half-edges bordering the face
}HE_face;

int main()
{ // 查询一条半边的邻接面和邻接半边
    HE_edge *edge;
    HE_vert *vert1 = edge->vert;
    HE_vert *vert2 = edge->pair->vert;

    HE_face *face1 = edge->face;
    HE_face *face2 = edge->pair->face;
}