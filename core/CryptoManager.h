#ifndef CRYPTOMANAGER_H
#define CRYPTOMANAGER_H

#include <string>

using namespace std;

class CryptoManager{
    public:
        static string encrypt(const string &data, const string &key);
        static string decrypt(const string &data, const string &key);
};

#endif  