#include <iostream>
#include <string>
#include <limits>
#include "core/AuthManager.h"
#include "core/DataManager.h"

using namespace std;

/* Temporarily use console until GUI is implemented */
void printMenu(){
    cout << "-------- Password Manager --------" << endl;
    cout << "1. View Entries\n";
    cout << "2. Add an Entry\n";
    cout << "3. Save Vault\n";
    cout << "4. Exit\n";
    cout << "Choose an option: ";

}
int main(int argc, char* argv[]){
    const string vaultPath = "vault.dat";
    const string masterPasswordHashPath = "master.hash";

    string masterPassword;
    cout << "Enter the master password: ";
    getline(cin, masterPassword);

    //! Temporary verification, need to change later
    if (!AuthManager::verifyMasterPassword(masterPassword, masterPasswordHashPath)){
        cout << "Incorrect password. Exiting..." << endl;
        return 1;
    }

    cout << "Authentication successful!" << endl;

    DataManager manager;
    if (!manager.loadVault(vaultPath, masterPassword)){
        cout << "No vault found. Creating a new one now..." << endl;
    }

    int choice;
    do{
        printMenu();
        cin >> choice;
        cin.ignore();       // ignore newline

        if (choice == 1){
            manager.printEntries();
        }
        else if (choice == 2){
            string site, username, password;
            cout << "Enter Site: ";
            getline(cin, site);
            cout << "Enter Username: ";
            getline(cin, username);
            cout << "Enter Password: ";
            getline(cin, password);
            manager.addEntry(site, username, password);
        }
        else if (choice == 3){
            if(manager.saveVault(vaultPath, masterPassword)){
                cout << "Vault saved.\n";
            }
            else {
                cerr << "Failed to save vault\n";
            }
        }
        else if (choice == 4){
            cout << "Exiting now.\n";
        }
        else {
            cout << "Invalid choice. Please pick from above.\n";
        }
    }
    while (choice != 4);
    return 0;
}