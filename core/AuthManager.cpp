#include "AuthManager.h"
#include <fstream>
#include <iostream>
#include <openssl/sha.h>

static std::string storedHash = "5e884898da28047151d0e56f8dc6292773603d0d6aabbdd62a11ef721d1542d8"; // SHA256("password")

bool AuthManager::verifyMasterPassword(const std::string &input){
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<const unsigned char*>(input.c_str()), input.length(), hash);

    char hashString[65];
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++){
        sprintf(&hashString[i*2], "%02x", hash[i]);

    return storedHash == std::string(hashString);
    }
}