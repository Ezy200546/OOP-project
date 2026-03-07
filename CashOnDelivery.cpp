#include <iostream>
#include "CashOnDelivery.h"
#include "BKashAccounts.h"

using namespace std;

CashOnDelivery::CashOnDelivery(double amt) : Payment(amt) {}

bool CashOnDelivery::validate() {
    return true;
}

bool CashOnDelivery::process(BKashAccounts &accounts) {
    return true;
}

void CashOnDelivery::display() {
    cout << "Payment Method: Cash On Delivery" << endl;
    cout << "Amount to pay on delivery: " << amount << " Taka" << endl;
}