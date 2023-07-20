#include "QuadTree.h"
#include <stdio.h>

point init_point(int x, int y) {
    // point* p = (point*)malloc(sizeof(point));
    point p = { x, y };
    return p;
}

qNode* init_qNode(point lu_point, int height, int width) {
    qNode* node = (qNode*)malloc(sizeof(qNode));
    node->lu_point = lu_point;
    node->height = height;
    node->width = width;
    for (int i = 0; i < 4; i++)
    {
        node->zone[i] = NULL;
    }
    return node;
}

int quad_process(color **_pic, int _width, int _height, int _tolerance)
{
    printf("quad_process\n");
    // printf("r: %d, g: %d, b: %d\n", _pic[0][0].r, _pic[0][0].g, _pic[0][0].b);
    // l
    qNode *root = init_qNode(init_point(0, 0), _height, _width);
    recur(root, _pic, _tolerance);
    return 1;
}

void recur(qNode *root, color **_pic, int _tolerance)
{
    // printf("recur\n");
    
    if (root->height == 1 && root->width == 1)
    {
        return;
    }
    int res = check(root, _pic, _tolerance);
    if (res == 0)
        return;

    int x = root->lu_point.x;
    int y = root->lu_point.y;
    int h = root->height;
    int w = root->width;
    // debug
    // printf("x: %d, y: %d, h: %d, w: %d\n", x, y, h, w);
    // debug
    root->zone[0] = init_qNode(init_point(x, y), h / 2, w / 2);
    root->zone[1] = init_qNode(init_point(x , y + w/2), h / 2, w / 2);
    root->zone[2] = init_qNode(init_point(x + h/2, y), h / 2, w / 2);
    root->zone[3] = init_qNode(init_point(x + h/2, y + w/2), h / 2, w / 2);

    recur(root->zone[0], _pic, _tolerance);
    recur(root->zone[1], _pic, _tolerance);
    recur(root->zone[2], _pic, _tolerance);
    recur(root->zone[3], _pic, _tolerance);
    return;
}

int check(qNode *root, color **_pic, int _tolerance){
    // printf("check\n");
    int x = root->lu_point.x;
    int y = root->lu_point.y;
    int h = root->height;
    int w = root->width;
    color avg = get_average_color(_pic, x, y, h, w);
    double var = get_variance(_pic, x, y, h, w);
    // printf("var: %lf\n", var);
    if (var <= _tolerance)
    {
        for (int i = x; i < x + h; i++)
        {
            for (int j = y; j < y + w; j++)
            {
                _pic[i][j] = avg;
            }
        }
        return 0;
    }
    return 1;
}

color get_average_color(color **_pic, int _x, int _y, int _h, int _w)
{
    // printf("get_average_color\n");
    int r = 0, g = 0, b = 0;
    for (int i = _x; i < _x + _h; i++)
    {
        for (int j = _y; j < _y + _w; j++)
        {
            // printf("i: %d, j: %d\n", i, j);
            r += _pic[i][j].r;
            g += _pic[i][j].g;
            b += _pic[i][j].b;
        }
    }
    color c;
    c.r = r / (_h * _w);
    c.g = g / (_h * _w);
    c.b = b / (_h * _w);
    return c;
}

double get_variance(color **_pic, int _x, int _y, int _h, int _w){
    // printf("get_variance\n");
    color avg = get_average_color(_pic, _x, _y, _h, _w);
    double r = 0, g = 0, b = 0;
    for (int i = _x; i < _x + _h; i++)
    {
        for (int j = _y; j < _y + _w; j++)
        {
            r += (_pic[i][j].r - avg.r) * (_pic[i][j].r - avg.r);
            g += (_pic[i][j].g - avg.g) * (_pic[i][j].g - avg.g);
            b += (_pic[i][j].b - avg.b) * (_pic[i][j].b - avg.b);
        }
    }
    return (double)(r + g + b) / (double) (_h * _w);
}