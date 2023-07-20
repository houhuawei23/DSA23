#include <iostream>
#include <string>

std::string decrypt(const std::string& encrypted, const std::string& decryptionKey) {
    std::string decrypted = encrypted;
    size_t pos = decrypted.find(decryptionKey);
    
    while (pos != std::string::npos) {
        decrypted.erase(pos, decryptionKey.length());
        pos = decrypted.find(decryptionKey);
    }
    
    return decrypted;
}

int main() {
    std::string S1 = "impooooooooooooooortant";  // 替换为实际的加密信息
    std::string S2 = "oo";  // 替换为实际的解密密钥

    std::string decryptedInfo = decrypt(S1, S2);

    std::cout << "解密后的重要信息: " << decryptedInfo << std::endl;

    return 0;
}
