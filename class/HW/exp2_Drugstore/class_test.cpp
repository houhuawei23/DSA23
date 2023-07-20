#include <bits/stdc++.h>
using namespace std;

class C {
public:
    int a;
    void print() {
        cout << "a: " << a << endl;
    }
} g_c[10];

C* h_c[10];


int main() {
    for (int i = 0; i < 10; i++) {
        h_c[i] = &(g_c[i]);
        h_c[i]->a = i;
    }

    // 通过 h_c 指针数组访问 C 类的数据成员 a
    for (int i = 0; i < 10; i++) {
        h_c[i]->print();
    }

    return 0;
}