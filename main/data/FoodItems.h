#ifndef FOODITEMS_H
#define FOODITEMS_H

#include <string>
#include <iomanip> // Provides formatting tools such as setw() and methods for aligning data.
#include <iostream>

#include "Product.h"
#include "../universal/Date.h"

using namespace std;


// Inherits common product attributes and methods from the Product class.
class FoodItems : public Product
{
private:
    // Stores the expiry date of the food item.
    Date expiryDate;

    // Stores the category to which the food item belongs.
    string category;

public:
    // Default constructor.
    FoodItems()
    {
        category = "";
    }

    // Parameterized constructor.
    FoodItems(Date expiryDate, string category, int productID,
              string productName, double price, int quantityInStock)
        : Product(productID, productName, price, quantityInStock)
    {
        this->expiryDate = expiryDate;
        this->category = category;
    }

    // ================= GETTERS =================

    // Returns the expiry date of the food item.
    Date getExpiryDate()
    {
        return expiryDate;
    }

    // Returns the category of the food item.
    string getCategory()
    {
        return category;
    }

    // ================= SETTERS =================

    // Sets or updates the expiry date of the food item.
    void setExpiryDate(Date expiryDate)
    {
        this->expiryDate = expiryDate;
    }

    // Sets or updates the category of the food item.
    void setCategory(string category)
    {
        this->category = category;
    }

    // Validates the supplied category against the accepted food categories.
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

    // Converts every character in the supplied string to lowercase.
    string toLowerCase(string text)
    {
        for (size_t i = 0; i < text.length(); ++i)
        {
            text[i] = tolower(text[i]);
        }

        return text;
    }

    // Overrides the Display() method inherited from the Product class.
    void Display()
    {
        cout << "\n================================"
             << "\n      FoodItems DETAILS"
             << "\n================================"
             << "\nProduct ID:       " << getProductID()
             << "\nProduct Name:     " << getProductName()
             << "\nPrice:            $" << fixed << setprecision(2) << getPrice()
             << "\nQuantity:         " << getQuantityInStock()
             << "\nExpiry Date:             ";

        // Calls the Date class method to display the expiry date.
        expiryDate.displayDate();

        cout << "\nCategory:            " << category
             << "\n================================\n";
    }
};

#endif // FOODITEMS_H