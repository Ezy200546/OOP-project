#ifndef CART_H
#define CART_H

#include "Product.h"

class Cart {
private:
    Product products[10];
    int quantity[10];
    int count;

public:
    Cart();

    int addItem(Product p,int quantity);
    int removeItem(int productId);
    int updateItem(int productId,int quantity);
    int viewCart();
    int checkOut();
    int getCount() const;
};

#endif
