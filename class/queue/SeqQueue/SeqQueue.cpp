/*************************************************************
    date: April 2017
    copyright: Zhu En
    DO NOT distribute this code without my permission.
**************************************************************/
// 循环顺序的队列实现文件
/////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include "SeqQueue.h"

SeqQueue *SQ_Create(int maxlen)
// 创建顺序队列, 队列最多存储maxlen个队列元素。
{
    SeqQueue *sq = (SeqQueue *)malloc(sizeof(SeqQueue));
    sq->data = (T *)malloc(sizeof(T) * (maxlen + 1));
    sq->front = sq->rear = 0;
    sq->max = maxlen + 1;
    return sq;
}

void SQ_Free(SeqQueue *sq)
// 释放队列空间，以删除队列。
{
    free(sq->data);
    free(sq);
}

void SQ_MakeEmpty(SeqQueue *sq)
// 将队列置空。
{
    sq->front = 0;
    sq->rear = 0;
}

bool SQ_IsEmpty(SeqQueue *sq)
// 判断队列是否为空，为空返回true，否则返回false。
{
    // 请在Begin-End之间补充代码，完成队列是否为空的判断。
    /********** Begin *********/
    if (sq->front == sq->rear)
        return true;
    else
        return false;
    /********** End **********/
}

bool SQ_IsFull(SeqQueue *sq)
// 判断队列是否为满。为满返回true,否则返回false。
{
    // 请在Begin-End之间补充代码，完成队列是否为满的判断。
    /********** Begin *********/
    // if(sq->front == (sq->rear + 1) % sq->max)
    //     return true;
    // else
    //     return false;
    if ((sq->front == 0 && sq->rear == sq->max - 1) || (sq->front == sq->rear + 1))
    {
        return true;
    }
    else
        return false;
    /********** End **********/
}

int SQ_Length(SeqQueue *sq)
// 队列长度。
{
    // 请在Begin-End之间补充代码，获取队列长度。
    /********** Begin *********/
    if (sq->front <= sq->rear)
        return sq->rear - sq->front;
    else
        return sq->rear + sq->max - sq->front;
    /********** End **********/
}

bool SQ_In(SeqQueue *sq, T x)
// 将x入队。若入队失败(队列满)，则返回false，否则返回true。
{
    // 请在Begin-End之间补充代码，将 x 入队。
    /********** Begin *********/
    if (SQ_IsFull(sq))
        return false;
    else
    {
        sq->data[sq->rear] = x;
        sq->rear = (sq->rear + 1) % sq->max;
        return true;
    }
    /********** End **********/
}

bool SQ_Out(SeqQueue *sq, T &item)
// 从队列sq出队一个元素，返回时item为出队的元素的值。若出队成功(队列不为空)，则返回true，否则(队列空)，返回false，此时item不会返回有效值。
{
    // 请在Begin-End之间补充代码，完成元素出队操作。
    /********** Begin *********/
    if (SQ_IsEmpty(sq))
        return false;
    else
    {
        item = sq->data[sq->front];
        sq->front = (sq->front + 1) % sq->max;
        return true;
    }
    /********** End **********/
}

bool SQ_Head(SeqQueue *sq, T &head)
// 获取队列头结点元素，返回时head保存头结点元素。
// 若获取失败(队列空)，则返回值为false，否则返回值为true。
{
    if (SQ_IsEmpty(sq))
    {
        return false;
    }
    else
    {
        head = sq->data[sq->front];
        return true;
    }
}

void SQ_Print(SeqQueue *sq)
// 依次打印出队列中的每个元素。
{
    int i = sq->front;
    if (SQ_IsEmpty(sq))
    {
        printf("queue is emtpy");
        return;
    }
    for (i = sq->front; i != sq->rear; i = (i + 1) % sq->max)
    {
        printf("%d  ", sq->data[i]);
    }
    printf("\n");
}
