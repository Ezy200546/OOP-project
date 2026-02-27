#include "Product.h"

Product::Product() {
    name = "";
    price = 0;
}

Product::Product(string n, float p) {
    name = n;
    price = p;
}

string Product::getName() const {
    return name;
}

float Product::getPrice() const {
    return price;
}