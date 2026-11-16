#ifndef STADIUMSHOP_H
#define STADIUMSHOP_H

#include "Merchandise.h"
#include "Tickets.h"
#include "FoodItems.h"
#include "Product.h"

#include <string>
#include <math.h>

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
        double taxRate;

    public:
    // Default Constructor
        StadiumShop() {
            shopID = 0;
            shopName = "";
            productCount = 0;
            location = "";
            inventoryValue = 0.0;
            totalProductsSold = 0;
            taxRate = 0.0;
        }

        // Parameterized Constructor
        StadiumShop(int shopID, string shopName, int productCount,
                    string location, double inventoryValue,
                    int totalProductsSold, double taxRate) {
            this->shopID = shopID;
            this->shopName = shopName;
            this->productCount = productCount;
            this->location = location;
            this->inventoryValue = inventoryValue;
            this->totalProductsSold = totalProductsSold;
            this->taxRate = taxRate;
        }

        // Getters
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

        void setTaxRate(double taxRate) {
            this->taxRate = taxRate;
        }

        // Rule 1: Add 15% GCT to a price that does not include tax yet.
        static double calculatePriceWithGCT(double preTaxPrice) {
            return std::round(preTaxPrice * 1.15 * 100.0) / 100.0;
        }

        // Store the tax-inclusive price using the product's existing setter.
        template <typename ProductType>
        static void setPriceFromPreTax(ProductType& product, double preTaxPrice) {
            product.setPrice(calculatePriceWithGCT(preTaxPrice));
        }

        // Find the tax already included in a selling price for a receipt.
        // Do not add this amount to the selling price again.
        static double calculateIncludedGCT(double sellingPrice) {
            return std::round(sellingPrice * (15.0 / 115.0) * 100.0) / 100.0;
        }
};

#endif // STADIUMSHOP_H
