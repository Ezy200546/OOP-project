#include "Cart.h"

Cart::Cart() {
    count = 0;
}

void Cart::addProduct(Product p) {
    if (count < 10)
        products[count++] = p;
}

int Cart::getCount() const {
    return count;
}