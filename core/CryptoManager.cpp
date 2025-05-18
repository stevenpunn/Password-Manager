#include "CryptoManager.h"
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <sstream>
#include <iomanip>
#include <vector>

// Program uses an AES-256 encryption algorithm

static const int KEY_LENGTH = 32;   // 256 bits
static const int IV_LENGTH = 16;    // 128 bits

// Convert bytes to hex
static string toHex(const vector<unsigned char> &data){
    ostringstream oss;
    for (auto b : data){
        oss << hex << setw(2) << setfill('0') << (int)b;
    }
    return oss.str();
}

// Convert hex to bytes
static vector<unsigned char> fromHex(const string &hex){
    vector<unsigned char> bytes;
    for (size_t i = 0; i < hex.length(); i+= 2){
        string byteString = hex.substr(i, 2);
        unsigned char byte = (unsigned char)strtol(byteString.c_str(), nullptr, 16);
        bytes.push_back(byte);
    }
    return bytes;
}

string CryptoManager::encrypt(const string &plaintext, const string &key){
    vector<unsigned char> iv(IV_LENGTH);
    RAND_bytes(iv.data(), IV_LENGTH);

    vector<unsigned char> ciphertext(plaintext.size() + EVP_MAX_BLOCK_LENGTH);
    int len = 0;
    int ciphertext_len = 0;

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, (unsigned char*)key.data(), iv.data());
    EVP_EncryptUpdate(ctx, ciphertext.data(), &len, (unsigned char*)plaintext.data(), plaintext.size());
    ciphertext_len = len;
    EVP_EncryptFinal_ex(ctx, ciphertext.data() + len, &len);
    ciphertext_len += len;
    EVP_CIPHER_CTX_free(ctx);

    ciphertext.resize(ciphertext_len);

    string hexIV = toHex(iv);
    string hexCipher = toHex(ciphertext);
    return hexIV + hexCipher;
}

string CryptoManager::decrypt(const string &cipherHex, const string &key){
    string hexIV = cipherHex.substr(0, IV_LENGTH * 2);
    string hexCipher = cipherHex.substr(IV_LENGTH * 2);

    vector<unsigned char> iv = fromHex(hexIV);
    vector<unsigned char> ciphertext = fromHex(hexCipher);

    vector<unsigned char> plaintext(ciphertext.size());
    int len = 0;
    int plaintext_len = 0;

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, (unsigned char*)key.data(), iv.data());
    EVP_DecryptUpdate(ctx, plaintext.data(), &len, ciphertext.data(), ciphertext.size());
    plaintext_len = len;
    EVP_DecryptFinal_ex(ctx, plaintext.data() + len, &len);
    plaintext_len += len;
    EVP_CIPHER_CTX_free(ctx);

    return string((char*)plaintext.data(), plaintext_len);
}