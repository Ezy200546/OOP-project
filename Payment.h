#ifndef PAYMENT_H
#define PAYMENT_H

#include <string>

class BKashAccounts; // forward declaration

class Payment {
protected:
    double amount;

public:
    Payment(double amt);
    virtual bool validate() = 0;
    virtual bool process(BKashAccounts &accounts) = 0;
    virtual void display() = 0;
    virtual ~Payment();
};

#endif