#ifndef USER_H
#define USER_H

#include <iostream>
using namespace std;

class User {
protected:
    string username;
    string password;
    string role;

public:
    User() {}
    User(string u, string p, string r) : username(u), password(p), role(r) {}

    string getUsername() { return username; }
    string getRole() { return role; }

    bool login(string u, string p) {
        return (username == u && password == p);
    }

    virtual void menu() = 0; // Polymorphism
};

class Buyer : public User {
public:
    Buyer(string u, string p) : User(u, p, "Buyer") {}

    void menu() override {
        cout << "\n--- Buyer Menu ---\n";
        cout << "1. View Products\n";
        cout << "2. View Cart\n";
        cout << "3. Checkout\n";
        cout << "4. Logout\n";
    }
};

class Seller : public User {
public:
    Seller(string u, string p) : User(u, p, "Seller") {}

    void menu() override {
        cout << "\n--- Seller Menu ---\n";
        cout << "1. Add Product\n";
        cout << "2. Edit Product\n";
        cout << "3. View Orders\n";
        cout << "4. Logout\n";
    }
};

class Admin : public User {
public:
    Admin(string u, string p) : User(u, p, "Admin") {}

    void menu() override {
        cout << "\n--- Admin Menu ---\n";
        cout << "1. Approve Seller\n";
        cout << "2. Ban User\n";
        cout << "3. View All Orders\n";
        cout << "4. Logout\n";
    }
};

#endif
