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
    double getTotal();   // I need to have to total money for me to make the payement the previous one clear the cart before the payment
    void clearCart();    // 
    int getCount() const;
};

#endif
