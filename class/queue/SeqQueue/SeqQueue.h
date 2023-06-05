// 顺序存储的队列头文件。
//////////////////////////////////////////////////////////////
#if !defined(SEQUENCE_QUEUE_H_LIELJE7398CNHD_INCLUDE_)
#define SEQUENCE_QUEUE_H_LIELJE7398CNHD_INCLUDE_
/////////////////////////////////////////////////////////////
typedef int T;
struct SeqQueue
{
    T *data;   // 指向数据元素数组的指针。
    int front; // 下一个出队元素的数组下标。
    int rear;  // 下一个入队元素应该存放的单元的数组下标。
    int max;   // 队列中最多可放max-1个数据元素，留一个空数据单元以区分空和满。
};

SeqQueue *SQ_Create(int maxlen);
void SQ_Free(SeqQueue *sq);
void SQ_MakeEmpty(SeqQueue *sq);
bool SQ_IsEmpty(SeqQueue *sq);
bool SQ_IsFull(SeqQueue *sq);
int SQ_Length(SeqQueue *sq);

bool SQ_In(SeqQueue *sq, T x);
bool SQ_Out(SeqQueue *sq, T &item);
bool SQ_Head(SeqQueue *sq, T &head);

void SQ_Print(SeqQueue *sq);

#endif