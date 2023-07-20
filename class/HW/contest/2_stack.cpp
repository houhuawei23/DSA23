#include <bits/stdc++.h>
using namespace std;

char s1[1000005], s2[1000005], s3[1000005];
int main(){
    scanf("%s%s", s1, s2);
    int len1 = strlen(s1), len2 = strlen(s2);
    int top = 0;
    for (int i = 0; i < len1; i++) {
        s3[top++] = s1[i];
        if (top >= len2) {
            bool flag = true;
            for (int j = 0; j < len2; j++) {
                if (s3[top - len2 + j] != s2[j]) {
                    flag = false;
                    break;
                }
            }
            if (flag) {
                top -= len2;
            }
        }
    }
    s3[top] = '\0';
    printf("%s\n", s3);
}