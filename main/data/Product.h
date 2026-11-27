#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

#include "../universal/FileManager.h"
#include "../exceptions/InsufficientStockException.h"

// Inherits from Persistable to support saving and loading product records.
// This is an abstract class because it contains a pure virtual function.
class Product : public Persistable
{
private:
    // Stores the unique identification number of the product.
    int productID;

    // Stores the name of the product.
    std::string productName;

    // Stores the selling price of the product.
    double price;

    // Stores the quantity of the product currently available in stock.
    int quantityInStock;

public:

    // Makes Product an abstract class and allows polymorphic display.
    virtual void Display() = 0;

    // Default constructor.
    Product()
    {
        productID = 0;
        productName = "";
        price = 0.0;
        quantityInStock = 0;
    }

    // Parameterized constructor.
    Product(int pID, std::string pName, double cost, int quantity)
    {
        productID = pID;
        productName = pName;
        price = cost;
        quantityInStock = quantity;
    }

    // ================= SETTERS =================

    // Sets or updates the product ID.
    void setProductID(int id)
    {
        productID = id;
    }

    // Returns the product ID.
    int getProductID() const
    {
        return productID;
    }

    // Sets or updates the product name.
    void setProductName(std::string name)
    {
        productName = name;
    }

    // ================= GETTERS =================

    // Returns the product name.
    std::string getProductName() const
    {
        return productName;
    }

    // Sets or updates the selling price of the product.
    void setPrice(double p)
    {
        price = p;
    }

    // Returns the selling price of the product.
    double getPrice() const
    {
        return price;
    }

    // Sets or updates the quantity available in stock.
    void setQuantityInStock(int quantity)
    {
        quantityInStock = quantity;
    }

    // Returns the current quantity available in stock.
    int getQuantityInStock() const
    {
        return quantityInStock;
    }

    // Checks whether the product has at least one unit available.
    bool isInStock() const
    {
        return quantityInStock > 0;
    }

    // Increases the available stock by the specified amount.
    void increaseStock(int amount)
    {
        quantityInStock += amount;
    }

    // Decreases the available stock by the specified amount.
    void decreaseStock(int amount)
    {
        if (amount <= 0) {
            throw InsufficientStockException();
        }

        if (amount > quantityInStock) {
            throw InsufficientStockException();
        }

        quantityInStock -= amount;
    }

    // Identifies whether the product represents a ticket.
    virtual bool isTicket() const
    {
        return false;
    }
};

#endif // PRODUCT_H