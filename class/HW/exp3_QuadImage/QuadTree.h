#ifndef __QUADTREE_H__
#define __QUADTREE_H__
#include <stdlib.h>
typedef struct point {
    int x;
    int y;
}point;

typedef struct color {
    unsigned char r;
    unsigned char g;
    unsigned char b;
}color;

typedef struct qNode {
    point*          lu_point_p;     // left up point
    int             height, width;  // height and width of the node
    struct qNode*   zone[4];        // 0: left up, 1: right up, 2: left down, 3: right down
}qNode;

point* init_point(int x, int y);

qNode* init_qNode(point* lu_point_p, int height, int width);

void print_node(qNode* root);
// void print_color(color* c){
//     printf("r: %d, g: %d, b: %d\n", c->r, c->g, c->b);
// }

void recur(qNode* root, color** _pic, int _tolerance);
int check(qNode* root, color** _pic, int _tolerance);
color get_average_color(color** _pic, int _x, int _y, int _h, int _w);
double get_variance(color** _pic, int _x, int _y, int _h, int _w);
int quad_process(color** _pic, int _width, int _height, int _tolerance);
void free_tree(qNode* root);

color get_median_color(color** _pic, int _x, int _y, int _h, int _w);

double get_entropy(color** _pic, int _x, int _y, int _h, int _w);

double get_gradient(color** _pic, int _x, int _y, int _h, int _w);
#endif // !__QUADTREE_H__