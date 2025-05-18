#ifndef AUTHMANAGER_H
#define AUTHMANAGER_H

#include <string>

class AuthManager{
    public:
        static bool verifyMasterPassword(const std::string &input);
};

#endif