#ifndef MERCHANDISE_H
#define MERCHANDISE_H

#include <string>
#include <iomanip> // Provides formatting tools such as setw() and methods for aligning data.
#include <iostream>

#include "Product.h"

using namespace std;

// Represents merchandise products sold at the stadium shop.
class Merchandise : public Product
{
private:
    // Stores the size of the merchandise item.
    string sizeOfItem;

    // Stores the brand associated with the merchandise item.
    string brand;

public:

    // Default constructor.
    Merchandise()
    {
        sizeOfItem = "";
        brand = "";
    }

    // Parameterized constructor.
    Merchandise(string sizeOfItem, string brand, int productID,
                string productName, double price, int quantityInStock)
        : Product(productID, productName, price, quantityInStock)
    {
        this->sizeOfItem = sizeOfItem;
        this->brand = brand;
    }

    // ================= GETTERS =================

    // Returns the size of the merchandise item.
    string getSizeOfItem()
    {
        return sizeOfItem;
    }

    // Returns the brand of the merchandise item.
    string getBrand()
    {
        return brand;
    }

    // ================= SETTERS =================

    // Sets or updates the size of the merchandise item.
    void setSizeOfItem(string size)
    {
        this->sizeOfItem = size;
    }

    // Sets or updates the brand of the merchandise item.
    void setBrand(string brand)
    {
        this->brand = brand;
    }

    // Overrides the Display() method inherited from the Product class.
    void Display()
    {
        cout << "\n================================"
             << "\n      MERCHANDISE DETAILS"
             << "\n================================"
             << "\nProduct ID:       " << getProductID()
             << "\nProduct Name:     " << getProductName()
             << "\nPrice:            $" << fixed << setprecision(2) << getPrice()
             << "\nQuantity:         " << getQuantityInStock()
             << "\nSize:             " << sizeOfItem
             << "\nBrand:            " << brand
             << "\n================================\n";
    }
};

#endif // MERCHANDISE_H