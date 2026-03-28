#ifndef PRODUCT_H
#define PRODUCT_H

#include <iostream>
#include <string>

using namespace std;

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

    // Getters
    int getId();
    string getName();
    string getCategory();
    double getPrice();
    int getStock();

    // Setters
    void setPrice(double price);
    void setStock(int stock);

    // Display product
    void displayProduct();

    // File operations
    void saveToFile();

    // Static operations
    static void listAllProducts();
    static void searchProduct(int id);
    static void deleteProduct(int id);
    static bool getProductById(int id,Product &result);
    static void updateStock(int id, int newStock);
};

#endif
