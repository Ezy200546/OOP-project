#include "User.h"

User::User() {
    username = "";
    password = "";
    role = "";
}

User::User(string u, string p, string r) {
    username = u;
    password = p;
    role = r;
}

string User::getUsername() const {
    return username;
}

string User::getPassword() const {
    return password;
}

string User::getRole() const {
    return role;
}

bool User::login(string u, string p) {
    return (username == u && password == p);
}

// Buyer
Buyer::Buyer() : User("", "", "Buyer") {}

Buyer::Buyer(string u, string p)
    : User(u, p, "Buyer") {}

// Seller
Seller::Seller() : User("", "", "Seller") {}

Seller::Seller(string u, string p)
    : User(u, p, "Seller") {}