#include <iostream>
#include <string>
#include "core/AuthManager.h"
#include "core/DataManager.h"

using namespace std;

int main(int argc, char* argv[]){
    string masterPassword;
    cout << "Enter the master password" << endl;
    cin >> masterPassword;

    if (!AuthManager::verifyMasterPassword(masterPassword)){
        cout << "Incorrect password. Exiting..." << endl;
        return 1;
    }
}