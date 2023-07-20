#ifndef __QUADTREE_H__
#define __QUADTREE_H__
#include <stdlib.h>
typedef struct point{
    int x;
    int y;
}point;

typedef struct color{
    unsigned char r;
    unsigned char g;
    unsigned char b;
}color;

typedef struct qNode{
    point lu_point;
    int height, width;
    struct qNode *zone[4];
}qNode;

point init_point(int x, int y);

qNode* init_qNode(point lu_point, int height, int width);

void recur(qNode *root, color **_pic, int _tolerance);
int check(qNode *root, color **_pic, int _tolerance);
color get_average_color(color **_pic, int _x, int _y, int _h, int _w);
double get_variance(color **_pic, int _x, int _y, int _h, int _w);
int quad_process(color **_pic, int _width, int _height, int _tolerance);


#endif // !__QUADTREE_H__