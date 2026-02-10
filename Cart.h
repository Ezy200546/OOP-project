#ifndef CART_H
#define CART_H

#include "Product.h"

class Cart {
public:
    Product items[20];
    int quantities[20];
    int count = 0;

    void addProduct(Product p, int qty) {
        items[count] = p;
        quantities[count] = qty;
        count++;
    }

    void viewCart() {
        cout << "\n--- Cart ---\n";
        for (int i = 0; i < count; i++) {
            cout << items[i].name << " x "
                 << quantities[i]
                 << " = $" << items[i].price * quantities[i] << endl;
        }
    }
};

#endif
