#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// get kmp next
// void GetKMPNext(int *next, char* s){
//     int i= 0, j = -1;
//     next[0] = -1;
//     while(i < strlen(s)){
//         if(j == -1 || s[i] == s[j]){
//             i++;
//             j++;
//             next[i] = j;
//         }else{
//             j = next[j];
//         }
//     }
// }

void GetKMPNext(int *next, char *s)
{
    int i = 0, j = -1;
    next[0] = -1;
    while (i < strlen(s))
    {
        // 如果不匹配，则回退
        while (j >= 0 && s[i] != s[j])
        {
            j = next[j];
        } // j == -1 or s[i] == s[j]
        i++;
        j++;
        // 
        if (s[i] == s[j])
        {
            next[i] = next[j];
        }
        else
        {
            next[i] = j;
        }
    }
    for(i = 0; i<strlen(s); i++){
        printf("%d ", next[i]);
    }
    printf("\n");
}

int Find(char*s, char*p){
    int i,j;
    int next[strlen(p)];
    GetKMPNext(next, p);
    int slen = strlen(s);
    int plen = strlen(p);
    for(i=0, j=0; i < slen && j <plen; ){
        if(s[i] == p[j]){
            i++;
            j++;
        }
        else if(next[j]>=0){
            j = next[j];
        }
        else{
            i++;
            j = 0;
        }
        if(j == plen){
            return i - plen;
        }
    }

    return -1;

}
int main()
{
    char s[] = "aaabcaabcabcda";
    char p[] = "abcabcd";
    int res = Find(s, p);
    printf("%d\n", res);
    return 0;
}