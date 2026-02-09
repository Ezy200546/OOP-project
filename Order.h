#ifndef ORDER_H
#define ORDER_H

#include <iostream>
using namespace std;

class Order {
public:
    int orderId;
    string buyerName;
    string status;

    Order(int id, string b) {
        orderId = id;
        buyerName = b;
        status = "Pending";
    }

    void display() {
        cout << "Order ID: " << orderId
             << " | Buyer: " << buyerName
             << " | Status: " << status << endl;
    }
};

#endif
