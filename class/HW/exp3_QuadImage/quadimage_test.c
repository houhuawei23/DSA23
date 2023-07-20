#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define VAR 20 // 方差阈值

typedef enum
{
	FALSE,
	TRUE
} Bool;

typedef struct color
{
	unsigned char r;
	unsigned char g;
	unsigned char b;

} color;

color **colors;

int readImage(int p, char *inFile, char *outFile);
void printImage(char *fileName, int width, color **a);

// To get ppm image from jpeg file, please visit https://convertio.co/jpg-ppm/
int readImage(int p, char *inFile, char *outFile)
{
	FILE *f = fopen(inFile, "rb");

	char u[3]; // placehoder
	int width, height, max_value;
	fscanf(f, "%s%d%d%d%c", u, &width, &height, &max_value, &u[0]);

	int i;

	colors = (color **)malloc(height * sizeof(color *));

	for (i = 0; i < height; i++)
		colors[i] = (color *)malloc(width * sizeof(color));

	for (i = 0; i < height; i++)
		fread(colors[i], sizeof(color), width, f);
	// printImage(outFile, width, colors);
	fclose(f);
	return width;
}

void printImage(char *fileName, int width, color **a)
{
	FILE *f = fopen(fileName, "wb");

	fprintf(f, "P6\n");
	fprintf(f, "%d %d\n", width, width);
	fprintf(f, "255\n");

	int i;
	for (i = 0; i < width; i++)
		fwrite(a[i], sizeof(color), width, f);

	fclose(f);
}

typedef struct quadtree // 建立四叉树
{
	// 坐标
	int left;
	int right;
	int up;
	int down;
	// 子树
	struct quadtree *one;
	struct quadtree *two;
	struct quadtree *three;
	struct quadtree *four;
} QTree;

int division(int a, int b) // 分四个区域时的一个小算法，防止分重叠
{
	if ((a + b) % 2 == 1)
		return (a + b - 1) / 2;
	else
		return (a + b) / 2;
}

Bool ismakenewdepth(QTree *root) // 计算要不要往下划分，如果要，实现进一步划分，如果不要，则直接赋平均值
{
	/*
	for(int j=0;j<root->right;j++)
	{
		if(colors[1][1].r)
		;
		else if(colors[1][1].r)
		;
		else
			printf("%d",j);
	}
	*/
	double rvar = 0, gvar = 0, bvar = 0, gave = 0, rave = 0, bave = 0;

	for (int i = root->left; i < root->right; i++) // 处理每一块现分区域
		for (int j = root->down; j < root->up; j++)
		{
			rave += (int)(colors[j][i].r);
			gave += (int)(colors[j][i].g);
			bave += (int)(colors[j][i].b); // 现分区域的所有r值加和
		}
	int summ = (root->up - root->down) * (root->right - root->left);
	rave /= summ; // 除以最小单元块数得平均值
	gave /= summ;
	bave /= summ;

	for (int i = root->left; i < root->right; i++) // 类似原理得现分区域的方差
		for (int j = root->down; j < root->up; j++)
		{
			rvar += (rave - (double)(colors[j][i].r)) * (rave - (double)(colors[j][i].r));
			gvar += (gave - (double)(colors[j][i].g)) * (gave - (double)(colors[j][i].g));
			bvar += (bave - (double)(colors[j][i].b)) * (bave - (double)(colors[j][i].b));
		}
	rvar /= summ;
	gvar /= summ;
	bvar /= summ;

	printf("%lf %lf %lf\n", rvar, gvar, bvar);
	if (rvar > VAR || gvar > VAR || bvar > VAR) // 判断现分区域每个单元间的方差是否太大，太大则需要递归
	// 继续拆分
	{
		QTree *twoo = (QTree *)malloc(sizeof(QTree)); // 左上区域（第一象限）拆分的时候左上不动，动右下,其它区域同理
		twoo->up = root->up;
		twoo->down = division(root->down, root->up);
		twoo->left = root->left;
		twoo->right = division(root->right, root->left);
		twoo->one = NULL;
		twoo->two = NULL;
		twoo->three = NULL;
		twoo->four = NULL;
		root->two = twoo;

		QTree *threee = (QTree *)malloc(sizeof(QTree));
		threee->up = division(root->up, root->down);
		threee->down = root->down;
		threee->left = root->left;
		threee->right = division(root->right, root->left);
		threee->one = NULL;
		threee->two = NULL;
		threee->three = NULL;
		threee->four = NULL;
		root->three = threee;

		QTree *onee = (QTree *)malloc(sizeof(QTree));
		onee->up = root->up;
		onee->down = division(root->down, root->up);
		onee->left = division(root->left, root->right);
		onee->right = root->right;
		onee->one = NULL;
		onee->two = NULL;
		onee->three = NULL;
		onee->four = NULL;
		root->one = onee;

		QTree *fourr = (QTree *)malloc(sizeof(QTree));
		fourr->up = division(root->up, root->down);
		fourr->down = root->down;
		fourr->left = division(root->left, root->right);
		fourr->right = root->right;
		fourr->one = NULL;
		fourr->two = NULL;
		fourr->three = NULL;
		fourr->four = NULL;
		root->four = fourr;

		return TRUE; // 继续拆分
	}

	else // 要是方差不大，就给现分区域内所有的r都赋予平均值，g,b同理
	{
		for (int i = root->left; i < root->right; i++)
			for (int j = root->down; j < root->up; j++)
			{
				colors[j][i].b = bave;
				colors[j][i].g = gave;
				colors[j][i].r = rave;
			}

		return FALSE; // 方差满足要求
	}
}

void recur(QTree *root) // 递归函数，从根节点开始按要求完全划分
{
	Bool r = ismakenewdepth(root);
	if (r == FALSE)
		return;

	recur(root->one); // 要是一直不满足方差要求，就一直划分下去，其中新建结点已经在ismakenewdepth中弄过了
	recur(root->two);
	recur(root->three);
	recur(root->four);
}

void runQTree(int width) // 建立根节点并完全划分
{
	QTree *root = (QTree *)malloc(sizeof(QTree)); // 建立一个最大矩形的根节点
	root->down = 0;
	root->left = 0;
	root->right = width; // 建立类似于第一象限的坐标系的感觉
	root->up = width;
	root->one = NULL;
	root->two = NULL;
	root->three = NULL;
	root->four = NULL;
	recur(root); // 一直递归下去
}

/*第二部分：高斯模糊*/
void Guass(int width) // 对处理过的图像（细分矩阵的程度不同）进行高斯模糊，半径为1
{
	double quanzhong[3][3] = {{0.0453542, 0.0566406, 0.0453542},
							  {0.0566406, 0.0707355, 0.0566406},
							  {0.0453542, 0.0566406, 0.0453542}};
	for (int i = 1; i < width - 1; i++)
		for (int j = 1; j < width - 1; j++)
		{
			double gave = 0, rave = 0, bave = 0;
			for (int k = -1; k <= 1; k++) // 对于每一个点都进行高斯模糊，之前每一个点都处理过了，相当于压缩后（抛去细节）再模糊？
				for (int l = -1; l <= 1; l++)
				{
					rave += (double)(colors[j + k][i + l].r) * quanzhong[k + 1][l + 1] / 0.4787147;
					gave += (double)(colors[j + k][i + l].g) * quanzhong[k + 1][l + 1] / 0.4787147;
					bave += (double)(colors[j + k][i + l].b) * quanzhong[k + 1][l + 1] / 0.4787147;
				}
			colors[j][i].r = rave;
			colors[j][i].g = gave;
			colors[j][i].b = bave;
		}
}

int main(int argc, char **argv)
{
	int tolerance = 0;
	char *inFile;
	char *outFile;
	if (argc > 1)
	{
		tolerance = atoi(argv[1]);
		inFile = argv[2];
		outFile = argv[3];

		int width = readImage(tolerance, inFile, outFile);
		runQTree(width);
		// for (int i = 0; i < 20; i++)
		// {
		// 	Guass(width);
		// }
		printImage(outFile, width, colors);

		for (int i = 0; i < width; i++)
			free(colors[i]);
		free(colors);
	}
	return 0;
}

