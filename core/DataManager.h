#ifndef DATAMANAGER_H
#define DATAMANAGER_H
#include <string>
#include <vector>
#include <tuple>

using namespace std;

class DataManager {
    public:
    DataManager();
        explicit DataManager(const string &key);
        bool loadVault(const string &path, const string& masterKey);
        bool saveVault(const string &path, const string& masterKey);
        void addEntry(const string &site, const string &username, const string &password);
        void printEntries() const;

    private:
        string masterKey;
        vector<tuple<string, string, string>> entries;
};

#endif