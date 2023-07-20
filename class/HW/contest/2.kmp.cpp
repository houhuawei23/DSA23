#include <iostream>
#include <string>
#include <vector>

using namespace std;
vector<int> computeLPS(const string& pattern) {
    int m = pattern.length();
    vector<int> lps(m, 0);
    int len = 0;
    int i = 1;

    while (i < m) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }

    return lps;
}

string decrypt(const string& encrypted, const string& decryptionKey) {
    string decrypted = encrypted;
    int n = decrypted.length();
    int m = decryptionKey.length();

    vector<int> lps = computeLPS(decryptionKey);
    cout << "lps: ";
    for (int i = 0; i < lps.size(); i++) {
        cout << lps[i] << " ";
    }
    cout << endl;
    int i = 0;
    int j = 0;

    while (i < n) {
        if (decrypted[i] == decryptionKey[j]) {
            i++;
            j++;
        }

        if (j == m) {
            decrypted.erase(i - j, m);
            n = decrypted.length();
            i = i - j;
            j = 0;
        } else if (i < n && decrypted[i] != decryptionKey[j]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }

    return decrypted;
}

int main() {
    string S1, S2;
    cin >> S1 >> S2;

    string decryptedInfo = decrypt(S1, S2);

    // cout << "解密后的重要信息: " << 
    cout<< decryptedInfo << endl;

    return 0;
}
