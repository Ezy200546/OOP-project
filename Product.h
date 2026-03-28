#ifndef PRODUCT_H
#define PRODUCT_H

#include <iostream>
#include <string>

using namespace std;

// Base class: Product
class Product {
private:
    int id;
    string name;
    string category;
    double price;
    int stock;

public:
    // Constructors
    Product();
    Product(int id, string name, string category, double price, int stock);

    // Destructor (virtual for inheritance safety)
    virtual ~Product(){}

    // Getters
    int getId();
    string getName();
    string getCategory();
    double getPrice();
    int getStock();

    // Setters
    void setPrice(double price);
    void setStock(int stock);

    // Virtual function (for polymorphism)
    virtual void displayProduct();

    // File operations
    void saveToFile();

    // Static utility functions
    static void listAllProducts();
    static void searchProduct(int id);
    static void deleteProduct(int id);
};
