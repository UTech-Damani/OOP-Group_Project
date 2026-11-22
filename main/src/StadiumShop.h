#ifndef STADIUMSHOP_H
#define STADIUMSHOP_H

#include "Product.h"
#include "Spectator.h"
#include <InsufficientPaymentException.h>

#include <string>
#include <math.h>
#include <vector>

using namespace std;

class StadiumShop
{
    private:
        int shopID;
        string shopName;
        int productCount;
        string location;
        double inventoryValue;
        int totalProductsSold;
        static const double taxRate = 15;

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

        // Getters
        int getShopID() {
            return shopID;
        }

        int getProductCount() const {
            return products.size();
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

        double getTaxRate() {
            return taxRate;
        }

        // Setters
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

        // Rule 1: Add 15% GCT to a price that does not include tax yet.
        static double calculatePriceWithGCT(double preTaxPrice) {
            return round(preTaxPrice * (1 + taxRate / 100.0) * 100.0) / 100.0;
        }

        // Store the tax-inclusive price using the product's existing setter.
        static void setPriceFromPreTax(Product* product, double preTaxPrice) {
            product->setPrice(calculatePriceWithGCT(preTaxPrice));
        }

        // Find the tax already included in a selling price for a receipt.
        static double calculateIncludedGCT(double sellingPrice) {
            return std::round(sellingPrice * (taxRate / 115.0) * 100.0) / 100.0;
        }

        void addProduct(Product* p){
            // Check if product already exists
            for (int i = 0; i < products.size(); i++)
            {
                if (products[i] == p)
                {
                    return;
                }
            }

            // Add GCT to the product price
            setPriceFromPreTax(p, p->getPrice());

            // Add product to inventory
            products.push_back(p);

            // Update shop data
            productCount++;
            inventoryValue += p->getPrice();
          
        }

        void transaction(Spectator* spectator, Product* product)
        {
            if (spectator->getBalance() < product->getPrice())
            {
                throw InsufficientPaymentException();
            }

            spectator->setBalance(spectator->getBalance() - product->getPrice());

            totalProductsSold++;
            inventoryValue -= product->getPrice();

            for (int i = 0; i < products.size(); i++)
            {
                if (products[i] == product)
                {
                    products.erase(products.begin() + i);
                    break;
                }
            }
        }
};

#endif // STADIUMSHOP_H
