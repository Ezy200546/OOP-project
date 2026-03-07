#include <iostream>
#include "Cart.h"

using namespace std;

Cart::Cart() {
    count = 0;
}

int Cart::addItem(Product p, int qty) {

    if (count >= 10) {
        cout << "Cart is full\n";
        return 0;
    }

    products[count] = p;
    quantity[count] = qty;
    count++;

    cout << "Item added to cart\n";
    return 1;
}

int Cart::removeItem(int productId) {

    for (int i = 0; i < count; i++) {

        if (products[i].id == productId) {

            for (int j = i; j < count - 1; j++) {
                products[j] = products[j + 1];
                quantity[j] = quantity[j + 1];
            }

            count--;

            cout << "Item removed\n";
            return 1;
        }
    }

    cout << "Item not found\n";
    return 0;
}

int Cart::updateItem(int productId, int qty) {

    for (int i = 0; i < count; i++) {

        if (products[i].id == productId) {
            quantity[i] = qty;

            cout << "Item updated\n";
            return 1;
        }
    }

    cout << "Item not found\n";
    return 0;
}

int Cart::viewCart() {

    if (count == 0) {
        cout << "Cart is empty\n";
        return 0;
    }

    cout << "\nCart Items:\n";

    for (int i = 0; i < count; i++) {

        cout << "Product ID: " << products[i].id << endl;
        cout << "Name: " << products[i].name << endl;
        cout << "Price: " << products[i].price << endl;
        cout << "Quantity: " << quantity[i] << endl;
        cout << "-----------------\n";
    }

    cout << "Total: " << getTotal() << endl;

    return 1;
}

double Cart::getTotal() {

    double total = 0;

    for (int i = 0; i < count; i++) {
        total += products[i].price * quantity[i];
    }

    return total;
}

void Cart::clearCart() {
    count = 0;
}

int Cart::getCount() const {
    return count;
}
