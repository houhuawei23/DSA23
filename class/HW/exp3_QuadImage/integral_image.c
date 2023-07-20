#include <stdio.h>

// 假设图像是一个二维灰度图像
typedef struct Image {
    int width;
    int height;
    unsigned char* data;  // 像素数据，按行优先顺序存储
} Image;

// 建立积分图像和积分平方图像
void computeIntegralImages(Image* image, int** integralImage, int** integralImageSq) {
    *integralImage = (int*)malloc(sizeof(int) * image->width * image->height);
    *integralImageSq = (int*)malloc(sizeof(int) * image->width * image->height);

    for (int i = 0; i < image->height; i++) {
        for (int j = 0; j < image->width; j++) {
            int pixel = image->data[i * image->width + j];
            int top = (i == 0) ? 0 : (*integralImage)[(i - 1) * image->width + j];
            int left = (j == 0) ? 0 : (*integralImage)[i * image->width + j - 1];
            int topleft = (i == 0 || j == 0) ? 0 : (*integralImage)[(i - 1) * image->width + j - 1];
            (*integralImage)[i * image->width + j] = pixel + left + top - topleft;

            int pixelSq = pixel * pixel;
            int topSq = (i == 0) ? 0 : (*integralImageSq)[(i - 1) * image->width + j];
            int leftSq = (j == 0) ? 0 : (*integralImageSq)[i * image->width + j - 1];
            int topleftSq = (i == 0 || j == 0) ? 0 : (*integralImageSq)[(i - 1) * image->width + j - 1];
            (*integralImageSq)[i * image->width + j] = pixelSq + leftSq + topSq - topleftSq;
        }
    }
}

// 使用积分图像计算区域平均值和方差
void computeMeanAndVariance(int x, int y, int width, int height, int* integralImage, int* integralImageSq, int imageWidth, double* mean, double* variance) {
    int x1 = x - 1;
    int y1 = y - 1;
    int x2 = x + width - 1;
    int y2 = y + height - 1;

    int area = width * height;

    int sum = integralImage[y2 * imageWidth + x2]
        - ((x1 >= 0) ? integralImage[y2 * imageWidth + x1] : 0)
        - ((y1 >= 0) ? integralImage[y1 * imageWidth + x2] : 0)
        + ((x1 >= 0 && y1 >= 0) ? integralImage[y1 * imageWidth + x1] : 0);

    int sumSq = integralImageSq[y2 * imageWidth + x2]
        - ((x1 >= 0) ? integralImageSq[y2 * imageWidth + x1] : 0)
        - ((y1 >= 0) ? integralImageSq[y1 * imageWidth + x2] : 0)
        + ((x1 >= 0 && y1 >= 0) ? integralImageSq[y1 * imageWidth + x1] : 0);

    *mean = (double)sum / area;
    *variance = ((double)sumSq - sum * sum / (double)area) / (area - 1);
}
