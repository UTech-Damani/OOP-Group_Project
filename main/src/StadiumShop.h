#ifndef STADIUMSHOP_H
#define STADIUMSHOP_H
#include <string>

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
};

#endif // STADIUMSHOP_H
