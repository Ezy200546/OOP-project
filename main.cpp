#include <iostream>
#include <fstream>
#include <string>

#include "User.h"
#include "Product.h"
#include "Cart.h"
#include "Order.h"
#include "BKashPayment.h"
#include "CashOnDelivery.h"
#include "BKashAccounts.h"

using namespace std;


void saveUser(string u, string p)
{
    ofstream file("users.txt", ios::app);
    file << u << " " << p << endl;
    file.close();
}

bool loginUser(string u, string p)
{
    ifstream file("users.txt");
    string user, pass;

    while(file >> user >> pass)
    {
        if(user == u && pass == p)
            return true;
    }
    return false;
}


int main()
{
    int choice;
    const string ADMIN_PASS = "admin123";

    Buyer pending[20];
    int pendingCount = 0;

    Cart cart;

    while(true)
    {
        cout << "\n===== E-COMMERCE SYSTEM =====\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "0. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        if(choice == 0) break;

        //REGISTER 
        if(choice == 1)
        {
            string u, p;
            cout << "Enter username: ";
            cin >> u;
            cout << "Enter password: ";
            cin >> p;

            pending[pendingCount++] = Buyer(u,p);
            saveUser(u,p);

            cout << "Registration submitted (waiting admin approval)\n";
        }

        //  LOGIN
        {
            int type;
            cout << "\n1. Buyer Login\n2. Admin Login\nChoice: ";
            cin >> type;

            // BUYER 
            if(type == 1)
            {
                string username, password;
                cout << "Username: "; cin >> username;
                cout << "Password: "; cin >> password;

                if(loginUser(username,password))
                {
                    cout << "Login successful!\n";

                    int bchoice;

                    while(true)
                    {
                        cout << "\n--- BUYER MENU ---\n";
                        cout << "1. View Products\n";
                        cout << "2. Add Product to Cart\n";
                        cout << "3. View Cart\n";
                        cout << "4. Checkout\n";
                        cout << "0. Logout\n";
                        cout << "Choice: ";
                        cin >> bchoice;

                        if(bchoice == 0) break;

                        // -------- VIEW PRODUCTS --------
                        if(bchoice == 1)
                        {
                            Product::listAllProducts();
                        }

                        // -------- ADD TO CART --------
                        else if(bchoice == 2)
                        {
                            int id, qty;
                            cout << "Enter Product ID: ";
                            cin >> id;
                            cout << "Quantity: ";
                            cin >> qty;

                            Product p;

                            if(Product::getProductById(id, p))
                            {
                                if(qty <= p.getStock())
                                {
                                    cart.addItem(p, qty);
                                }
                                else
                                {
                                    cout << "Not enough stock!\n";
                                }
                            }
                            else
                            {
                                cout << "Product not found!\n";
                            }
                        }

                        // VIEW CART 
                        else if(bchoice == 3)
                        {
                            cart.viewCart();
                        }

                        //  CHECKOUT + ORDER 
                        else if(bchoice == 4)
                        {
                            double total = cart.getTotal();

                            if(total == 0)
                            {
                                cout << "Cart is empty!\n";
                                continue;
                            }

                            cout << "Total: " << total << " Taka\n";

                           
                            Order order(username);
                            order.createOrder(cart);

                            int pay;
                            cout << "1. bKash\n2. Cash On Delivery\nChoice: ";
                            cin >> pay;

                            if(pay == 1)
                            {
                                string number;
                                cout << "Enter bKash number: ";
                                cin >> number;

                                BKashAccounts acc;
                                acc.loadAccounts("bKashAccounts.txt");

                                order.setPaymentMethod(new BKashPayment(total, number));
                            }
                            else
                            {
                                order.setPaymentMethod(new CashOnDelivery(total));
                            }

                            cout << "Order placed successfully!\n";

                            
                            for(int i = 0; i < cart.getCount(); i++)
                            {
                                Product p = cart.getProduct(i);
                                int qty = cart.getQuantity(i);

                                int newStock = p.getStock() - qty;

                                Product::updateStock(p.getId(), newStock);
                            }

                            
                            cart.clearCart();
                        }
                    }
                }
                else
                {
                    cout << "Invalid login!\n";
                }
            }

            // ADMIN 
            else if(type == 2)
            {
                string pass;
                cout << "Enter admin password: ";
                cin >> pass;

                if(pass == ADMIN_PASS)
                {
                    cout << "Admin login success!\n";

                    int achoice;

                    while(true)
                    {
                        cout << "\n--- ADMIN MENU ---\n";
                        cout << "1. View Pending Buyers\n";
                        cout << "2. Add Product\n";
                        cout << "3. Delete Product\n";
                        cout << "4. View Products\n";
                        cout << "5. View Orders\n";
                        cout << "0. Logout\n";
                        cout << "Choice: ";
                        cin >> achoice;

                        if(achoice == 0) break;

                        // PENDING USERS
                        if(achoice == 1)
                        {
                            if(pendingCount == 0)
                                cout << "No pending users\n";

                            for(int i=0;i<pendingCount;i++)
                            {
                                cout << i+1 << ". " << pending[i].getUsername() << endl;

                                int act;
                                cout << "1.Accept  2.Reject: ";
                                cin >> act;

                                for(int j=i;j<pendingCount-1;j++)
                                    pending[j]=pending[j+1];

                                pendingCount--;
                                i--;
                            }
                        }

                        // ADD PRODUCT 
                        else if(achoice == 2)
                        {
                            int id, stock;
                            double price;
                            string name, category;

                            cout << "ID: "; cin >> id;
                            cout << "Name: "; cin >> name;
                            cout << "Category: "; cin >> category;
                            cout << "Price: "; cin >> price;
                            cout << "Stock: "; cin >> stock;

                            Product p(id,name,category,price,stock);
                            p.saveToFile();

                            cout << "Product added successfully!\n";
                        }

                        //DELETE PRODUCT 
                        else if(achoice == 3)
                        {
                            int id;
                            cout << "Enter product ID: ";
                            cin >> id;

                            Product::deleteProduct(id);
                        }

                        // VIEW PRODUCTS 
                        else if(achoice == 4)
                        {
                            Product::listAllProducts();
                        }

                        //VIEW ORDERS
                        else if(achoice == 5)
                        {
                            Order o("admin"); 
                            o.listOrders();
                        }
                    }
                }
                else
                {
                    cout << "Wrong admin password!\n";
                }
            }
        }
    }

    return 0;
}
