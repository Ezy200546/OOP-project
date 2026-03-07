#ifndef BKASH_PAYMENT_H
#define BKASH_PAYMENT_H

#include "Payment.h"
#include "BKashAccounts.h"
#include <string>

class BKashPayment : public Payment {
private:
    std::string number;

public:
    BKashPayment(double amt, const std::string &num);

    bool validate() override;
    bool process(BKashAccounts &accounts) override;
    void display() override;
};

#endif