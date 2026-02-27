#ifndef CART_H
#define CART_H

#include "Product.h"

class Cart {
private:
    Product products[10];
    int count;

public:
    Cart();
    void addProduct(Product p);
    int getCount() const;
};

#endif
