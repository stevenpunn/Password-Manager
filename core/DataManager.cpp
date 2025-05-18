#include "DataManager.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

DataManager::DataManager(const string &key) : masterKey(key) {}

void DataManager::loadVault(const string &path){
    ifstream file(path);
    if(!file){
        return;
    }

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
    ofstream file(path);
    for (const auto &[site, user, pass] : entries) {
        file << site << "," << user << "," << pass << "\n";
    }
}

void DataManager::addEntry(const string &site, const string &username, const string &password){
    entries.emplace_back(site, username, password);
    cout << "Entry added." << endl;
}

void DataManager::printEntries(){
    for (const auto &[site, user, pass] : entries){
        cout << "Site: " << site << ", Username: " << user << ", Password: " << pass << endl;
    }
}