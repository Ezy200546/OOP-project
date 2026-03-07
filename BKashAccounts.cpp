#include "BKashAccounts.h"
#include <fstream>
#include <iostream>

using namespace std;

void BKashAccounts::loadAccounts(const string &filename) {
    ifstream file(filename);

    if(!file.is_open()) {
        cout << "Cannot open accounts file!" << endl;
        return;
    }

    string number;
    double balance;

    while(file >> number >> balance) {
        accounts[number] = balance;
    }

    file.close();
}

void BKashAccounts::saveAccounts(const string &filename) {
    ofstream file(filename);

    if(!file.is_open()) {
        cout << "Cannot write accounts file!" << endl;
        return;
    }

    for(auto &acc : accounts) {
        file << acc.first << " " << acc.second << endl;
    }

    file.close();
}

bool BKashAccounts::accountExists(const string &number) {
    return accounts.find(number) != accounts.end();
}

double BKashAccounts::getBalance(const string &number) {
    if(accountExists(number))
        return accounts[number];

    return -1;
}

bool BKashAccounts::deductBalance(const string &number, double amount) {
    if(accountExists(number) && accounts[number] >= amount) {
        accounts[number] -= amount;
        return true;
    }
    return false;
}
