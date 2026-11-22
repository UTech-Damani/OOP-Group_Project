#ifndef MERCHANDISE_H
#define MERCHANDISE_H

#include <string>
#include <iomanip>
#include <iostream>

#include "Product.h"

using namespace std;

class Merchandise : public Product{
    private:
        string sizeOfItem;
        string brand;

    public:

        // Constructors
        Merchandise() {
            sizeOfItem = "";
            brand = "";
        }

        Merchandise(string sizeOfItem, string brand, int productID,
                    string productName, double price, int quantityInStock) : Product(productID, productName, price, quantityInStock){

            this->sizeOfItem = sizeOfItem;
            this->brand = brand;
        }

        // Getters
        string getSizeOfItem() {
            return sizeOfItem;
        }

        string getBrand() {
            return brand;
        }

        // Setters
        void setSizeOfItem(string size) {
            this->sizeOfItem = size;
        }

        void setBrand(string brand) {
            this->brand = brand;
        }

        // Display method for attributes within the class
        void Display() override{ // override tells the compiler that this method should be overriding a method in the parent class
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
