#include "QuadTree.h"
#include "utils.h"
#include <stdio.h>
#include <math.h>
// #define DEBUG
point* init_point(int x, int y) {
    point* p = (point*)malloc(sizeof(point));
    p->x = x;
    p->y = y;
    return p;
}

qNode* init_qNode(point* lu_point_p, int height, int width) {
#ifdef DEBUG_INIT_QNODE
    printf("init_qNode\n");
    printf("lu_point_p: (%d, %d), height: %d, width: %d\n", lu_point_p->x, lu_point_p->y, height, width);
#endif
    qNode* node = (qNode*)malloc(sizeof(qNode));
    node->lu_point_p = lu_point_p;
    node->height = height;
    node->width = width;
    for (int i = 0; i < 4; i++)
    {
        node->zone[i] = NULL;
    }
    return node;
}
void print_node(qNode* root) {
    printf("lu_point_p: (%d, %d), height: %d, width: %d\n", root->lu_point_p->x, root->lu_point_p->y, root->height, root->width);
}




void free_tree(qNode* root) {
#ifdef DEBUG_FREE
    printf("free_tree\n");
#endif
    if (root == NULL)
        return;
    qNode* zone[4];
    for (int i = 0; i < 4; i++)
    {
        zone[i] = root->zone[i];
    }
    free(root->lu_point_p);
    free(root);
    for (int i = 0; i < 4; i++)
    {
        if (zone[i] != NULL) {
            free_tree(zone[i]);
        }
    }
#ifdef DEBUG_FREE
    printf("end of free_tree\n");
#endif
    return;
}

int quad_process(color** _pic, int _width, int _height, int _tolerance)
{
    printf("quad_process\n");
    qNode* root = init_qNode(init_point(0, 0), _height, _width);
    recur(root, _pic, _tolerance);
    free_tree(root);
    return 1;
}

void recur(qNode* root, color** _pic, int _tolerance)
{

#ifdef DEBUG_RECUR
    printf("start recur\n");
#endif
    if (root == NULL) {
#ifdef DEBUG_RECUR
        printf("end recur: root == NULL\n");
#endif
        return;
    }

    if (root->height < 2 || root->width < 2)
    {
#ifdef DEBUG_RECUR
        printf("end recur: root->height < 2 || root->width < 2 \n");
#endif
        return;
    }

    int res = check(root, _pic, _tolerance);

    if (res == 0) {
#ifdef DEBUG_RECUR
        printf("end recur: res == 0\n");
#endif
        return;
    }

    int x = root->lu_point_p->x;
    int y = root->lu_point_p->y;
    int h = root->height;
    int w = root->width;

    root->zone[0] = init_qNode(init_point(x, y), h / 2, w / 2);
    root->zone[1] = init_qNode(init_point(x, y + w / 2), h / 2, w / 2);
    root->zone[2] = init_qNode(init_point(x + h / 2, y), h / 2, w / 2);
    root->zone[3] = init_qNode(init_point(x + h / 2, y + w / 2), h / 2, w / 2);

    recur(root->zone[0], _pic, _tolerance);
    recur(root->zone[1], _pic, _tolerance);
    recur(root->zone[2], _pic, _tolerance);
    recur(root->zone[3], _pic, _tolerance);
#ifdef DEBUG_RECUR
    printf("end recur\n");
#endif
    return;

}

int check(qNode* root, color** _pic, int _tolerance) {
#ifdef DEBUG_CHECK
    printf("check\n");
#endif
    int x = root->lu_point_p->x;
    int y = root->lu_point_p->y;
    int h = root->height;
    int w = root->width;
    color avg = get_average_color(_pic, x, y, h, w);
    // color med = get_median_color(_pic, x, y, h, w);
    double var = get_variance(_pic, x, y, h, w);
    // double entropy = get_entropy(_pic, x, y, h, w);
    // double gradient = get_gradient(_pic, x, y, h, w);
    // printf("entropy: %lf\n", entropy);
    // printf("gradient: %lf\n", gradient);
    // if (entropy <= _tolerance)
    // {
    //     for (int i = x; i < x + h; i++)
    //     {
    //         for (int j = y; j < y + w; j++)
    //         {
    //             _pic[i][j] = avg;
    //         }
    //     }
    //     return 0;
    // }

    // gauss blur
    double kernel[5][5] = {
        {1.0 / 273, 4.0 / 273, 7.0 / 273, 4.0 / 273, 1.0 / 273},
        {4.0 / 273, 16.0 / 273, 26.0 / 273, 16.0 / 273, 4.0 / 273},
        {7.0 / 273, 26.0 / 273, 41.0 / 273, 26.0 / 273, 7.0 / 273},
        {4.0 / 273, 16.0 / 273, 26.0 / 273, 16.0 / 273, 4.0 / 273},
        {1.0 / 273, 4.0 / 273, 7.0 / 273, 4.0 / 273, 1.0 / 273}
    };
    if (var <= _tolerance) {
        for (int i = 2; i < h - 2; i++)
        {
            for (int j = 2; j < w - 2; j++)
            {
                double r = 0, g = 0, b = 0;
                for (int k = -2; k <= 2; k++)
                {
                    for (int l = -2; l <= 2; l++)
                    {
                        r += _pic[x + i + k][y + j + l].r * kernel[k + 2][l + 2];
                        g += _pic[x + i + k][y + j + l].g * kernel[k + 2][l + 2];
                        b += _pic[x + i + k][y + j + l].b * kernel[k + 2][l + 2];
                    }
                }
                _pic[x + i][y + j].r = (unsigned char)r;
                _pic[x + i][y + j].g = (unsigned char)g;
                _pic[x + i][y + j].b = (unsigned char)b;
            }
        }
    }
    return 1;
}
/*
    get_average_color: get average color of a region
    return value: color
*/
color get_average_color(color** _pic, int _x, int _y, int _h, int _w)
{
#ifdef DEBUG
    printf("get_average_color\n");
#endif
    int r = 0, g = 0, b = 0;
    for (int i = _x; i < _x + _h; i++)
    {
        for (int j = _y; j < _y + _w; j++)
        {
            r += _pic[i][j].r;
            g += _pic[i][j].g;
            b += _pic[i][j].b;
        }
    }
    color c;
    c.r = r / (_h * _w);
    c.g = g / (_h * _w);
    c.b = b / (_h * _w);
#ifdef DEBUG
    printf("end get_average_color\n");
#endif
    return c;
}

/*
    get_variance: get variance of a region
    return value: double
*/
double get_variance(color** _pic, int _x, int _y, int _h, int _w) {
#ifdef DEBUG
    printf("get_variance\n");
#endif
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
#ifdef DEBUG
    printf("end get_variance\n");
#endif

    return (double)(r + g + b) / (double)(_h * _w);
}

/*
    sort: sort an array
    return value: void
*/
// void sort(int* arr, int size)
// {
// #ifdef DEBUG
//     printf("sort\n");
//     printf("size: %d\n", size);
// #endif
//     quickSort(arr, 0, size - 1);
// #ifdef DEBUG
//     printf("end sort\n");
// #endif
// }
// void sort(int* arr, int size){
//     // 简单排序
//     for (int i = 0; i < size; i++)
//     {
//         int min = i;
//         for (int j = i + 1; j < size; j++)
//         {
//             if (arr[j] < arr[min])
//                 min = j;
//         }
//         swap(&arr[i], &arr[min]);
//     }
// }
void sort(int* arr, int size)
{
#ifdef DEBUG
    printf("sort\n");
    printf("size: %d\n", size);
#endif
    for (int i = 0; i < size; i++)
    {
        int min = arr[i];
        int index = i;
        for (int j = i + 1; j < size; j++)
        {
            if (arr[j] < min)
            {
                min = arr[j];
                index = j;
            }
        }
        int tmp = arr[i];
        arr[i] = arr[index];
        arr[index] = tmp;

    }
}
/*
    get_median_color: get median color of a region
    return value: color
*/
color get_median_color(color** _pic, int _x, int _y, int _h, int _w)
{
#ifdef DEBUG
    printf("get_median_color\n");
#endif
    int size = _h * _w;
    int* r_arr = (int*)malloc(sizeof(int) * size);
    int* g_arr = (int*)malloc(sizeof(int) * size);
    int* b_arr = (int*)malloc(sizeof(int) * size);
    int index = 0;
    for (int i = _x; i < _x + _h; i++)
    {
        for (int j = _y; j < _y + _w; j++)
        {
            r_arr[index] = _pic[i][j].r;
            g_arr[index] = _pic[i][j].g;
            b_arr[index] = _pic[i][j].b;
            index++;
            // printf("# i: %d, j: %d\n", i, j);
        }
    }

    sort(r_arr, size);
    sort(g_arr, size);
    sort(b_arr, size);
    color c;
    // c.r = get_med(r_arr, size);
    // c.g = get_med(g_arr, size);
    // c.b = get_med(b_arr, size);
    c.r = r_arr[size / 2];
    c.g = g_arr[size / 2];
    c.b = b_arr[size / 2];

    free(r_arr);
    free(g_arr);
    free(b_arr);
#ifdef DEBUG
    printf("end get_median_color\n");
#endif
    return c;
}
/*
    get_gauss_blur: get gauss blur of a region
    return value: color
*/

// color get_gauss_blur(color** )

double get_entropy(color** _pic, int _x, int _y, int _h, int _w) {
    // printf("get_entropy\n");
    double entropy = 0.0;
    double grayscale[256] = { 0 };
    double totalPixels = _h * _w;
    for (int i = _x; i < _x + _h; i++) {
        for (int j = _y; j < _y + _w; j++) {
            unsigned char gray = (_pic[i][j].r + _pic[i][j].g + _pic[i][j].b) / 3;
            grayscale[gray]++;
        }
    }
    for (int i = 0; i < 256; i++) {
        double probability = grayscale[i] / totalPixels;
        if (probability > 0.0) {
            entropy -= probability * log2(probability);
        }
    }
    return entropy;
}

// double get_gradient(color** _pic, int _x, int _y, int _h, int _w) {
//     printf("get_gradient\n");
//     // Calculate gradient using central differences
//     int dx = (_pic[_x][_y + 1].r - _pic[_x][_y - 1].r) / 2;
//     int dy = (_pic[_x + 1][_y].r - _pic[_x - 1][_y].r) / 2;

//     // Calculate gradient magnitude using Euclidean distance
//     double gradient = sqrt(dx * dx + dy * dy);

//     return gradient;
// }

// double get_gradient(color** _pic, int _x, int _y, int _h, int _w) {
//     // Calculate gradient using central differences
//     int dx = (_pic[_y][_x + 1].r - _pic[_y][_x - 1].r) / 2;
//     int dy = (_pic[_y + 1][_x].r - _pic[_y - 1][_x].r) / 2;

//     // Calculate gradient magnitude using Euclidean distance
//     double gradient = sqrt(dx * dx + dy * dy);

//     return gradient;
// }



// double get_entropy(color** _pic, int _width, int _height){
//     double entropy = 0.0;
//     double grayscale[256] = {0};
//     double totalPixels = _height * _width;
//     for (int i = 0; i < _height; i++) {
//         for (int j = 0; j < _width; j++) {
//             unsigned char gray = (_pic[i][j].r + _pic[i][j].g + _pic[i][j].b) / 3;
//             grayscale[gray]++;
//         }
//     }
//     for (int i = 0; i < 256; i++) {
//         double probability = grayscale[i] / totalPixels;
//         if (probability > 0.0) {
//             entropy -= probability * log2(probability);
//         }
//     }
//     return entropy;
// }

// double calculateEntropy(color** image, int height, int width) {
//     // Step 2: Convert to grayscale
//     double grayscale[256] = {0};
//     double totalPixels = height * width;

//     for (int i = 0; i < height; i++) {
//         for (int j = 0; j < width; j++) {
//             unsigned char gray = (image[i][j].r + image[i][j].g + image[i][j].b) / 3;
//             grayscale[gray]++;
//         }
//     }

//     // Step 4: Calculate pixel value probabilities
//     double entropy = 0.0;
//     for (int i = 0; i < 256; i++) {
//         double probability = grayscale[i] / totalPixels;
//         if (probability > 0.0) {
//             entropy -= probability * log2(probability);
//         }
//     }

//     // Step 5: Calculate entropy
//     return entropy;
// }