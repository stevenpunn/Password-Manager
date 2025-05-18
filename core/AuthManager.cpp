#include "AuthManager.h"
#include <fstream>
#include <iostream>
#include <openssl/sha.h>
#include <iomanip>

static std::string storedHash = "5e884898da28047151d0e56f8dc6292773603d0d6aabbdd62a11ef721d1542d8"; // SHA256("password")

std::string AuthManager::hashPassword(const std::string& password){
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((const unsigned char*)password.c_str(), password.size(), hash);

    std::ostringstream oss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++){
        oss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }
    return oss.str();
}

bool AuthManager::verifyMasterPassword(const std::string &input, const std::string& hashFilePath){
    std::ifstream file(hashFilePath);
    if(!file.is_open()){
        std::cerr << "Could not open the master password hash file: " << hashFilePath << std::endl;
        return false;
    }
    
    std::string storedHash;
    std::getline(file, storedHash);
    file.close();

    std::string inputHash = hashPassword(input);
    return inputHash == storedHash;
}