#ifndef AUTHMANAGER_H
#define AUTHMANAGER_H

#include <string>

class AuthManager{
    public:
        static std::string hashPassword(const std::string& password);
        static bool verifyMasterPassword(const std::string &input, const std::string& hashFilePath);
};

#endif