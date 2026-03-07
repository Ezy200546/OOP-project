#ifndef CASH_ON_DELIVERY_H
#define CASH_ON_DELIVERY_H

#include "Payment.h"

class CashOnDelivery : public Payment {
public:
    CashOnDelivery(double amt);

    bool validate() override;
    bool process(BKashAccounts &accounts) override;
    void display() override;
};

#endif