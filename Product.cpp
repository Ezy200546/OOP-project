#include "Product.h"
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
void Product::saveToFile()
{
    // This will CREATE file automatically if it doesn't exist
    ofstream file("products.txt", ios::app);

    if(!file.is_open())
    {
        cout << "Error opening file!" << endl;
        return;
    }

    file << id << " "
         << name << " "
         << category << " "
         << price << " "
         << stock << endl;

    file.close();

    cout << "Product saved successfully!" << endl;
}
// List all products
void Product::listAllProducts() {

    ifstream file("products.txt");

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

    ifstream file("products.txt");

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
bool Product::getProductById(int searchId, Product &result)
{
    ifstream file("products.txt");

    int id, stock;
    string name, category;
    double price;

    while(file >> id >> name >> category >> price >> stock)
    {
        if(id == searchId)
        {
            result = Product(id, name, category, price, stock);
            return true;
        }
    }

    return false;
}
// Delete product
void Product::deleteProduct(int deleteId) {

    ifstream file("products.txt");
    ofstream temp("temp.txt");

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

    remove("products.txt");
    rename("temp.txt", "products.txt");

    if(found)
        cout << "Product deleted successfully\n";
    else
        cout << "Product not found\n";
}
void Product::updateStock(int searchId, int newStock)
{
    ifstream file("products.txt");
    ofstream temp("temp.txt");

    if(!file || !temp)
    {
        cout << "Error updating stock!\n";
        return;
    }

    int id, stock;
    string name, category;
    double price;

    while(file >> id >> name >> category >> price >> stock)
    {
        if(id == searchId)
        {
            stock = newStock; // 🔥 update stock
        }

        temp << id << " "
             << name << " "
             << category << " "
             << price << " "
             << stock << endl;
    }

    file.close();
    temp.close();

    remove("products.txt");
    rename("temp.txt", "products.txt");
}
