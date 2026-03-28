#include "Order.h"
#include "Payment.h"
#include "BKashPayment.h"
#include "CashOnDelivery.h"
#include "BKashAccounts.h"

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <typeinfo>

using namespace std;

// Constructor
Order::Order(string user) {
    username= user;
    orderId = 0;
    itemCount = 0;
    totalAmount = 0;
    paymentMethod = "None";
    status = "Pending";
    payment = nullptr;
}

// Destructor
Order::~Order() {
    if(payment)
        delete payment;
}

// Create order from cart
void Order::createOrder(Cart &cart) {

    if(cart.getCount() == 0) {
        cout << "Cart is empty. Cannot create order.\n";
        return;
    }

    orderId = rand() % 10000 + 1; // random order ID
    itemCount = cart.getCount();
    totalAmount = cart.getTotal();
    status = "Pending";

    cout << "\nOrder Created!\n";
    cout << "Order ID: " << orderId << endl;
    cout << "Items: " << itemCount << endl;
    cout << "Total: " << totalAmount << endl;
}

// Set payment method
void Order::setPaymentMethod(Payment* p) {
    payment = p;

    BKashAccounts accounts; // Load BKash accounts if needed
    accounts.loadAccounts("bKashAccounts.txt");

    // Detect payment type
    if(dynamic_cast<BKashPayment*>(payment)) {
        paymentMethod = "BKash";

        BKashPayment* bk = dynamic_cast<BKashPayment*>(payment);
        if(bk->validate() && bk->process(accounts)) {
            status = "Paid";
        } else {
            status = "Pending";
        }

        saveToFile();
        bk->display();

    } else if(dynamic_cast<CashOnDelivery*>(payment)) {
        paymentMethod = "COD";

        CashOnDelivery* cod = dynamic_cast<CashOnDelivery*>(payment);
        if(cod->validate()) {
            status = "Pending";
        }

        saveToFile();
        cod->display();
    }
}

// Complete payment manually
void Order::completePayment() {
    if(payment) {
        status = "Paid";
        saveToFile();
    }
}

// Getters
int Order::getOrderId() { return orderId; }
double Order::getTotalAmount() { return totalAmount; }
string Order::getStatus() { return status; }

// Save order to file
void Order::saveToFile()
{
    ofstream file("orders.txt", ios::app);

    if(!file)
    {
        cout << "Error opening orders file.\n";
        return;
    }

    file << "User: " << username << endl;
    file << "OrderID: " << orderId << endl;
    file << "Items: " << itemCount << endl;
    file << "Total: " << totalAmount << endl;
    file << "Payment: " << paymentMethod << endl;
    file << "Status: " << status << endl;
    file << "--------------------------" << endl;

    file.close();
}

// List all orders
void Order::listOrders() {
    ifstream file("orders.txt");
    if(!file) {
        cout << "No orders found.\n";
        return;
    }

    int id, items;
    double total;
    string pay, stat;

    cout << "\n===== All Orders =====\n";

    while(file >> id >> items >> total >> pay >> stat) {
        cout << "Order ID: " << id << endl;
        cout << "Items: " << items << endl;
        cout << "Total: " << total << endl;
        cout << "Payment: " << pay << endl;
        cout << "Status: " << stat << endl;
        cout << "----------------------\n";
    }

    file.close();
}
