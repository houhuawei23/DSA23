#include <bits/stdc++.h>
using namespace std;

int main(){
    string s1, s2;
    cin >> s1 >> s2;
    // s1 = "impooooooooooooooortant";
    // s2 = "oo";
    while (s1.find(s2) != string::npos) {
        s1.erase(s1.find(s2), s2.length());
    }
    cout << s1 << endl;
}








/*
你在对NFC卡进行重要信息泄露的时候发现泄露出来的信息经过加密的，经过一些玄学操作，
你得到了解密算法， 假设你泄露出来的信息为S1，你的解密密钥为S2，
解密过程就是在S.中找到字串S2并删除，直到Si中找不到S2
现在给你泄露信息Si与解密密钥S2，请你计算出解密后的重要信息
*/