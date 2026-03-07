#include "BKashPayment.h"
#include <iostream>

BKashPayment::BKashPayment(double amt, const std::string &num)
    : Payment(amt), number(num) {}

bool BKashPayment::validate() {
    if (number.length() != 11) {
        std::cout << "Invalid bKash number\n";
        return false;
    }
    return true;
}

bool BKashPayment::process(BKashAccounts &accounts) {

    if (!accounts.accountExists(number)) {
        std::cout << "Account not found\n";
        return false;
    }

    if (!accounts.deductBalance(number, amount)) {
        std::cout << "Insufficient balance\n";
        return false;
    }

    double remaining = accounts.getBalance(number);

    std::cout << "bKash Payment Successful\n";
    std::cout << "Paid: " << amount << " Taka\n";
    std::cout << "Remaining Balance: " << remaining << " Taka\n";

    accounts.saveAccounts("bKashAccounts.txt");

    return true;
}

void BKashPayment::display() {
    std::cout << "Payment Method: bKash\n";
    std::cout << "Account Number: " << number << "\n";
}