#include <bits/stdc++.h>
using namespace std;

vector<int> getNext(string& str) {
    int n = str.length();
    vector<int> next(n, 0);
    int len = 0;
    int i = 1;

    while (i < n) {
        if (str[i] == str[len]) {
            len++;
            next[i] = len;
            i++;
        }
        else {
            if (len != 0) {
                len = next[len - 1];
            }
            else {
                next[i] = 0;
                i++;
            }
        }
    }

    return next;
}

string decrypt(string& encrypted, string decryptionKey) {
    string decrypted = encrypted;
    int n = decrypted.length();
    int m = decryptionKey.length();

    vector<int> next = getNext(decryptionKey);
    // cout << "next: ";
    // for (int i = 0; i < next.size(); i++) {
    //     cout << next[i] << " ";
    // }
    // cout << endl;
    int i = 0;
    int j = 0;
    while (i < n) {
        if (decrypted[i] == decryptionKey[j]) {
            i++;
            j++;
        }
        if (j == m) { // found
            decrypted.erase(i - j, m);
            // cout << "decrypted: " << decrypted << endl;
            n = decrypted.length();
            // cout << "i0: " << i << endl;
            i = i - m - m;
            // i = i - j;
            i = max(0, i);
            // cout << "i1: " << i << endl;
            j = 0;
        }
        else if (i < n && decrypted[i] != decryptionKey[j]) {
            // mismatch after j matches
            if (j != 0) {
                j = next[j - 1];
            }
            else {
                i++;
            }
        }
    }


    return decrypted;

}

int main() {
    string s1, s2;
    cin >> s1 >> s2;
    // s1 = "ababababca";
    // s2 = "abababca";
    cout << decrypt(s1, s2) << endl;
}