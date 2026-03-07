#ifndef BKASH_ACCOUNTS_H
#define BKASH_ACCOUNTS_H

#include <string>
#include <map>

class BKashAccounts {
private:
    std::map<std::string, double> accounts;

public:
    void loadAccounts(const std::string &filename);
    void saveAccounts(const std::string &filename);

    bool accountExists(const std::string &number);
    double getBalance(const std::string &number);

    bool deductBalance(const std::string &number, double amount);
};

#endif