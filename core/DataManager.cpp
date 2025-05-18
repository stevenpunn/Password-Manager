#include "DataManager.h"
#include "CryptoManager.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

DataManager::DataManager(const string &key) : masterKey(key) {}

DataManager::DataManager(){}

void DataManager::loadVault(const string &path){
    ifstream file(path);
    if(!file){
        return;
    }

    stringstream buffer;
    buffer << file.rdbuf();     // read the entire file
    string encryptedData = buffer.str();
    string decryptedData = CryptoManager::decrypt(encryptedData, masterKey);

    istringstream iss(decryptedData);
    string line;
    while(getline(file, line)){
        istringstream iss(line);
        string site, user, pass;
        getline(iss, site, ',');
        getline(iss, user, ',');
        getline(iss, pass, ',');
        entries.emplace_back(site, user, pass);
    }
}

void DataManager::saveVault(const string &path){
    ostringstream oss;
    for (const auto &[site, user, pass] : entries) {
        oss << site << "," << user << "," << pass << "\n";
    }
    string plaintextData = oss.str();
    string encryptedData = CryptoManager::encrypt(plaintextData, masterKey);

    ofstream file(path);
    file << encryptedData;
}

void DataManager::addEntry(const string &site, const string &username, const string &password){
    entries.emplace_back(site, username, password);
    cout << "Entry added." << endl;
}

void DataManager::printEntries() const{
    if (entries.empty()){
        cout << "No entries were found." << endl;
        return;
    }
    cout << "Entries found:" << endl;
    for (const auto &[site, user, pass] : entries){
        cout << "Site: " << site << ", Username: " << user << ", Password: " << pass << endl;
    }
}