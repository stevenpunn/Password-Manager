#ifndef DATAMANAGER_H
#define DATAMANAGER_H
#include <string>
#include <vector>
#include <tuple>

using namespace std;

class DataManager {
    public:
        explicit DataManager(const string &key);
        void loadVault(const string &path);
        void saveVault(const string &path);
        void addEntry(const string &site, const string &username, const string &password);
        void printEntries();

    private:
        string masterKey;
        vector<tuple<string, string, string>> entries;
};

#endif