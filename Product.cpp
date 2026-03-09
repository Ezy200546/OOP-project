#include "../include/Product.h"
#include <fstream>
#include <cstdio>

// Default constructor
Product::Product() {
    id = 0;
    name = "";
    category = "";
    price = 0;
    stock = 0;
}

// Parameterized constructor
Product::Product(int id, string name, string category, double price, int stock) {
    this->id = id;
    this->name = name;
    this->category = category;
    this->price = price;
    this->stock = stock;
}

// Getters
int Product::getId() {
    return id;
}

string Product::getName() {
    return name;
}

string Product::getCategory() {
    return category;
}

double Product::getPrice() {
    return price;
}

int Product::getStock() {
    return stock;
}

// Setters
void Product::setPrice(double price) {
    this->price = price;
}

void Product::setStock(int stock) {
    this->stock = stock;
}

// Display product
void Product::displayProduct() {
    cout << "ID: " << id << endl;
    cout << "Name: " << name << endl;
    cout << "Category: " << category << endl;
    cout << "Price: " << price << endl;
    cout << "Stock: " << stock << endl;
    cout << "------------------------" << endl;
}

// Save product to file
void Product::saveToFile() {

    ofstream file("data/products.txt", ios::app);

    if(!file) {
        cout << "Error opening file\n";
        return;
    }

    file << id << " "
         << name << " "
         << category << " "
         << price << " "
         << stock << endl;

    file.close();
}

// List all products
void Product::listAllProducts() {

    ifstream file("data/products.txt");

    if(!file) {
        cout << "Error opening file\n";
        return;
    }

    int id, stock;
    string name, category;
    double price;

    while(file >> id >> name >> category >> price >> stock) {

        cout << "ID: " << id << endl;
        cout << "Name: " << name << endl;
        cout << "Category: " << category << endl;
        cout << "Price: " << price << endl;
        cout << "Stock: " << stock << endl;
        cout << "------------------------" << endl;
    }

    file.close();
}

// Search product by ID
void Product::searchProduct(int searchId) {

    ifstream file("data/products.txt");

    int id, stock;
    string name, category;
    double price;

    bool found = false;

    while(file >> id >> name >> category >> price >> stock) {

        if(id == searchId) {

            cout << "\nProduct Found\n";
            cout << "ID: " << id << endl;
            cout << "Name: " << name << endl;
            cout << "Category: " << category << endl;
            cout << "Price: " << price << endl;
            cout << "Stock: " << stock << endl;

            found = true;
            break;
        }
    }

    if(!found)
        cout << "Product not found\n";

    file.close();
}

// Delete product
void Product::deleteProduct(int deleteId) {

    ifstream file("data/products.txt");
    ofstream temp("data/temp.txt");

    int id, stock;
    string name, category;
    double price;

    bool found = false;

    while(file >> id >> name >> category >> price >> stock) {

        if(id == deleteId) {
            found = true;
            continue;
        }

        temp << id << " "
             << name << " "
             << category << " "
             << price << " "
             << stock << endl;
    }

    file.close();
    temp.close();

    remove("data/products.txt");
    rename("data/temp.txt", "data/products.txt");

    if(found)
        cout << "Product deleted successfully\n";
    else
        cout << "Product not found\n";
}
