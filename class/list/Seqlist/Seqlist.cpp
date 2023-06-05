/*************************************************************
    date: April 2017
    copyright: Zhu En
    DO NOT distribute this code without my permission.
**************************************************************/
// 顺序表操作实现文件
//////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include "Seqlist.h"

SeqList* SL_Create(int maxlen)
// 创建一个顺序表。
// 与SqLst_Free()配对。
{
	SeqList* slist=(SeqList*)malloc(sizeof(SeqList));
	slist->data = (T*)malloc(sizeof(T)*maxlen);
	slist->max=maxlen;
	slist->len=0;
	return slist;
}

void SL_Free(SeqList* slist)
// 释放/删除 顺序表。
// 与SqLst_Create()配对。
{
	free(slist->data);
	free(slist);
}

void SL_MakeEmpty(SeqList* slist)
// 置为空表。
{
	slist->len=0;
}

int SL_Length(SeqList* slist)
// 获取长度。
{
	return slist->len;
}

bool SL_IsEmpty(SeqList* slist)
// 判断顺序表是否空。
{
	return 0==slist->len;
}

bool SL_IsFull(SeqList* slist)
// 判断顺序表是否满。
{
	return slist->len==slist->max;
}

T SL_GetAt(SeqList* slist, int i)
// 获取顺序表slist的第i号结点数据。
// 返回第i号结点的值。
{
	if(i<0||i>=slist->len) {
		printf("SL_GetAt(): location error when reading elements of the slist!\n");		
		SL_Free(slist);
		exit(0);
	}
	else 
		return slist->data[i];
}

void SL_SetAt(SeqList* slist, int i, T x)
// 设置第i号结点的值（对第i号结点的数据进行写）。
{
	if(i<0||i>=slist->len) {
		printf("SL_SetAt(): location error when setting elements of the slist!\n");		
		SL_Free(slist);
		exit(0);
	}
	else 
		slist->data[i]=x;
}

bool SL_InsAt(SeqList* slist, int i, T x)
// 在顺序表的位置i插入结点x, 插入d[i]之前。
// i 的有效范围[0,plist->len]。
{
    // 请在下面的Begin-End之间补充代码，插入结点。
    /********** Begin *********/
	if(i<0||i>slist->len) {
		printf("SL_SetAt(): location error when setting elements of the slist!\n");		
		SL_Free(slist);
		exit(0);
	}
    else{
        for(int j = slist->len; j > i; j--){
            slist->data[j] = slist->data[j-1];
        }
    }
    slist->data[i] = x;
    slist->len++;
    /********** End **********/
}

T SL_DelAt(SeqList* slist, int i)
// 删除顺序表plist的第i号结点。
// i的有效范围应在[0,plist->len)内，否则会产生异常或错误。
// 返回被删除的数据元素的值。
{
    // 在下面的Begin-End之间补充代码，删除第i号结点。
    /********** Begin *********/
    if(i<0||i>=slist->len) {
        printf("SL_SetAt(): location error when setting elements of the slist!\n");
        SL_Free(slist);
        exit(0);
    }
    else{
        T x = slist->data[i];
        for(int j = i; j < slist->len-1; j++){
            slist->data[j] = slist->data[j+1];
        }
        slist->len--;
        return x;
    }

    /********** End **********/
}

int SL_FindValue(SeqList* slist, T x)
// 在顺序表表中查找第一个值为x的结点，返回结点的编号。
// 返回值大于等于0时表示找到值为x的结点的编号，-1表示没有找到。
{
	int i=0;
	while(i<slist->len && slist->data[i]!=x) i++;
	if (i<slist->len) return i;
	else return -1;
}

int SL_DelValue(SeqList* slist, T x)
// 删除第一个值为x的结点。
// 存在值为x的结点则返回结点编号, 未找到返回－1。
{
    // 在下面的Begin-End之间补充代码，删除第一个值为 x 的结点。
    /********** Begin *********/
    int i = SL_FindValue(slist, x);
    if(i == -1){
        return -1;
    }
    else{
        SL_DelAt(slist, i);
        return i;
    }

    /********** End **********/
}

void SL_Print(SeqList* slist)
// 打印整个顺序表。
{
	if (slist->len==0) {
		printf("The slist is empty.\n");		
		return;
	}

	//printf("The slist contains: ");
	for (int i=0; i<slist->len; i++) {
		printf("%d  ", slist->data[i]);
	}

	printf("\n");	
	
}