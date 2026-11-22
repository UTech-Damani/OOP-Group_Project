#ifndef FOODITEMS_H
#define FOODITEMS_H

#include <string>
#include <iomanip>
#include <iostream>

#include "Product.h"
#include "../universal/Date.h"

using namespace std;

class FoodItems : public Product{
    private:
        Date expiryDate;
        string category;

    public:
        // Constructors
        FoodItems() {
            category = "";
        }

        FoodItems(Date expiryDate, string category, int productID,
                string productName, double price, int quantityInStock) : Product(productID, productName, price, quantityInStock) {

            this->expiryDate = expiryDate;
            this->category = category;
        }

        // Getters
        Date getExpiryDate() {
            return expiryDate;
        }

        string getCategory() {
            return category;
        }

        // Setters
        void setExpiryDate(Date expiryDate) {
            this->expiryDate = expiryDate;
        }

        void setCategory(string category) {
            this->category = category;
        }

        bool validCategory(string category)
        {
            category = toLowerCase(category);
            return category == "drink" ||
                category == "popcorn" ||
                category == "burger" ||
                category == "pizza" ||
                category == "chicken" ||
                category == "ice Cream" ||
                category == "nachos" ||
                category == "hot Dog";
        }

        string toLowerCase(string text)
        {
            for (int i = 0; i < text.length(); i++)
            {
                text[i] = tolower(text[i]);
            }

            return text;
        }

        // Display method for attributes within the class
        void Display() override{ // override tells the compiler that this method should be overriding a method in the parent class
            cout << "\n================================"
            << "\n      FoodItems DETAILS"
            << "\n================================"
            << "\nProduct ID:       " << getProductID()
            << "\nProduct Name:     " << getProductName()
            << "\nPrice:            $" << fixed << setprecision(2) << getPrice()
            << "\nQuantity:         " << getQuantityInStock()
            << "\nExpiry Date:             ";
            expiryDate.displayDate();

            cout << "\nCategory:            " << category
            << "\n================================\n";
        }
};

#endif // FOODITEMS_H
