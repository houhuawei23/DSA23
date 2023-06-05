// 写一个集合数据结构
// 元素是整数
// 要求实现集合交和并的函数操作
// 用数组实现

// 集合结构
#include <stdio.h>
#include <stdlib.h>
typedef struct set {
    int *data;
    int size;
} Set;

// 初始化集合
Set *init(int length) {
    Set *s = (Set *)malloc(sizeof(Set));
    s->data = (int *)malloc(sizeof(int) * length);
    s->size = 0;
    return s;
}

// 插入元素
void insert(Set *s, int value) {
    s->data[s->size++] = value;
}
// 交集
Set *intersection(Set *s1, Set *s2) {
    Set *s3 = init(s1->size + s2->size);
    for (int i = 0; i < s1->size; i++) {
        for (int j = 0; j < s2->size; j++) {
            if (s1->data[i] == s2->data[j]) {
                insert(s3, s1->data[i]);
            }
        }
    }
    return s3;
}
// 并集
Set *union_set(Set *s1, Set *s2) {
    Set *s3 = init(s1->size + s2->size);
    for (int i = 0; i < s1->size; i++) {
        insert(s3, s1->data[i]);
    }
    for (int i = 0; i < s2->size; i++) {
        insert(s3, s2->data[i]);
    }
    return s3;
}
// 打印集合
void output(Set *s) {
    printf("Set = {");
    for (int i = 0; i < s->size; i++) {
        printf("%d ", s->data[i]);
    }
    printf("}");
    printf("\n");
}

// 测试
int main() {
    Set *s1 = init(100);
    Set *s2 = init(100);
    for (int i = 0; i < 10; i++) {
        insert(s1, i);
        insert(s2, i + 5);
    }
    output(s1);
    output(s2);
    Set *s3 = intersection(s1, s2);
    output(s3);
    Set *s4 = union_set(s1, s2);
    output(s4);
    return 0;
}