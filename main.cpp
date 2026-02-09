#include <iostream>
#include "User.h"
#include "Product.h"
#include "Cart.h"
#include "Order.h"

using namespace std;

int main() {
    Buyer buyer("adef", "1234");
    Seller seller("ezy", "1234");
    Admin admin("admin", "admin");

    User* currentUser = &buyer;  // demo login

    cout << "Welcome to MAHO E-COMMERCE\n";
    cout << "Logged in as: " << currentUser->getRole() << endl;

    currentUser->menu();

    // Demo products
    Product p1(1, "Laptop", "Electronics", 800, 10);
    Product p2(2, "Shoes", "Fashion", 50, 20);

    Cart cart;
    cart.addProduct(p1, 1);
    cart.addProduct(p2, 2);

    cart.viewCart();

    Order o1(1001, buyer.getUsername());
    o1.display();

    cout << "\nPayment Method: Cash on Deliver\n";
    cout << "Order Confirmed!\n";

    return 0;
}
