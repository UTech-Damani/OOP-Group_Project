#ifndef STADIUMSHOP_H
#define STADIUMSHOP_H

#include "../data/Product.h"
#include "../include/Spectator.h"
#include "../exceptions/InsufficientStockException.h"
#include "Stadium.h"

#include <string>
#include <math.h>
#include <vector> // Provides the vector container for storing dynamic collections.

using namespace std;

class Stadium;

class StadiumShop
{
    private:
        // Stores the shop's identification and general information
        int shopID;
        string shopName;
        int productCount;
        string location;

        // Tracks the financial value and sales performance of the shop
        double inventoryValue;
        int totalProductsSold;

        // Defines the GCT percentage applied to product prices
        const double taxRate = 15;

        // Stores pointers to the products available in the shop
        vector<Product*> products;

    public:
        // Default Constructor
        StadiumShop() {
            shopID = 0;
            shopName = "";
            productCount = 0;
            location = "";
            inventoryValue = 0.0;
            totalProductsSold = 0;

        }

        // Parameterized Constructor
        StadiumShop(int shopID, string shopName, int productCount,
                    string location, double inventoryValue,
                    int totalProductsSold) {
            this->shopID = shopID;
            this->shopName = shopName;
            this->productCount = productCount;
            this->location = location;
            this->inventoryValue = inventoryValue;
            this->totalProductsSold = totalProductsSold;

        }

        // ================= GETTERS =================

        // Returns the shop's stored attributes

        int getShopID() {
            return shopID;
        }

        string getShopName() {
            return shopName;
        }

        int getProductCount() {
            return productCount;
        }

        string getLocation() {
            return location;
        }

        double getInventoryValue() {
            return inventoryValue;
        }

        int getTotalProductsSold() {
            return totalProductsSold;
        }

        // Returns the shop's GCT rate
        double getTaxRate() {
            return taxRate;
        }

        // ================= SETTERS =================

        // Updates the shop's stored attributes

        void setShopID(int shopID) {
            this->shopID = shopID;
        }

        void setShopName(string shopName) {
            this->shopName = shopName;
        }

        void setProductCount(int productCount) {
            this->productCount = productCount;
        }

        void setLocation(string location) {
            this->location = location;
        }

        void setInventoryValue(double inventoryValue) {
            this->inventoryValue = inventoryValue;
        }

        void setTotalProductsSold(int totalProductsSold) {
            this->totalProductsSold = totalProductsSold;
        }

        // Calculates the product's selling price after adding 15% GCT
        double calculatePriceWithGCT(double preTaxPrice) {
            return round(preTaxPrice * (1 + taxRate / 100.0) * 100.0) / 100.0;
        }

        // Updates a product's price to include GCT
        void setPriceFromPreTax(Product* product, double preTaxPrice) {
            product->setPrice(calculatePriceWithGCT(preTaxPrice));
        }

        // Calculates the GCT amount already included in a selling price
        // This value can be used when preparing a customer receipt
        double calculateIncludedGCT(double sellingPrice) {
            return std::round(sellingPrice * (taxRate / 115.0) * 100.0) / 100.0;
        }

        // Adds a product to the shop's inventory
        void addProduct(Product* p){
            // Prevents the same product pointer from being added more than once
            for (size_t i = 0; i < products.size(); ++i)
            {
                if (products[i] == p)
                {
                    return;
                }
            }

            // Adds GCT to the product's original price
            setPriceFromPreTax(p, p->getPrice());

            // Stores the product in the shop's inventory
            products.push_back(p);

            // Updates the shop's product count and inventory value
            productCount++;
            inventoryValue += p->getPrice();

        }

        // Processes a transaction between a spectator and the shop
        void transaction(Spectator* spectator, Product* product){

            // Ensures both the spectator and product pointers are valid
            if (spectator == nullptr || product == nullptr) {
                return;
            }

            // Checks that the product is available before processing the sale
            if (!product->isInStock()) {
                throw InsufficientStockException();
            }

            // Deducts the product's price from the spectator's balance
            // Throws an exception if the spectator has insufficient funds
            spectator->deductBalance(product->getPrice());

            // Reduces the product's available stock by one unit
            product->decreaseStock(1);

            // Records the spectator's purchase
            spectator->buyProduct(product->getPrice());

            // Updates the shop's sales and inventory records
            totalProductsSold++;
            inventoryValue -= product->getPrice();

            // Displays the product involved in the transaction
            product->Display();
        }
};

#endif // STADIUMSHOP_H