#ifndef PRODUCT_H
#define PRODUCT_H

#include <iostream>
using namespace std;

class Product {
public:
    int id;
    string name;
    string category;
    double price;
    int stock;

    Product() {}

    Product(int i, string n, string c, double p, int s) {
        id = i;
        name = n;
        category = c;
        price = p;
        stock = s;
    }

    void display() {
        cout << id << " | " << name << " | " << category
             << " | $" << price << " | Stock: " << stock << endl;
    }
};

#endif
