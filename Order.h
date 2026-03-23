#ifndef ORDER_H
#define ORDER_H

#include "Cart.h"
#include "Payment.h"
#include <string>

class Order {
private:
    int orderId;
    int itemCount;
    double totalAmount;
    std::string paymentMethod;
    std::string status;

    Payment* payment;  

public:
    Order();
    ~Order();

    void createOrder(Cart &cart);
    void setPaymentMethod(Payment* p);   
    void completePayment();

    int getOrderId();
    double getTotalAmount();
    std::string getStatus();

    void saveToFile();
    void listOrders();
};

#endif
