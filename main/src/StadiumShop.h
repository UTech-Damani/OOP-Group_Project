#ifndef STADIUMSHOP_H
#define STADIUMSHOP_H

#include "../data/Product.h"
#include "../include/Spectator.h"
#include "../exceptions/InsufficientStockException.h"
#include "../exceptions/InsufficientPaymentException.h"

#include <string>
#include <math.h>
#include <vector>
#include <iomanip>
#include <iostream>

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
        const double taxRate = 15;

        vector<Product*> products;

        double totalRevenue = 0.0;
        double totalGCTCollected = 0.0;
        int transactionCount = 0;

    public:
        // One line of a shop sale: which product and how many.
        struct SaleLine {
            Product* product;
            int quantity;
        };

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
        double calculatePriceWithGCT(double preTaxPrice) {
            return round(preTaxPrice * (1 + taxRate / 100.0) * 100.0) / 100.0;
        }

        // Store the tax-inclusive price using the product's existing setter.
        void setPriceFromPreTax(Product* product, double preTaxPrice) {
            product->setPrice(calculatePriceWithGCT(preTaxPrice));
        }

        // Find the tax already included in a selling price for a receipt.
        double calculateIncludedGCT(double sellingPrice) {
            return std::round(sellingPrice * (taxRate / 115.0) * 100.0) / 100.0;
        }

        void addProduct(Product* p){
            // Check if product already exists
            for (size_t i = 0; i < products.size(); ++i)
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

        vector<Product*>& getProducts() {
            return products;
        }

        Product* findProduct(int productID) {
            for (Product* product : products) {
                if (product->getProductID() == productID)
                    return product;
            }
            return nullptr;
        }

        void clearProducts() {
            for (Product* product : products)
                delete product;
            products.clear();
            productCount = 0;
            inventoryValue = 0.0;
        }

        double getTotalRevenue() const { return totalRevenue; }
        double getTotalGCTCollected() const { return totalGCTCollected; }
        int getTransactionCount() const { return transactionCount; }

        // Adds a product whose price already includes GCT (e.g. one reloaded from file).
        void addTaxInclusiveProduct(Product* p) {
            products.push_back(p);
            productCount++;
            inventoryValue += p->getPrice() * p->getQuantityInStock();
        }

        // Completes a sale. Prices already include 15% GCT, so the tax is
        // worked out from the total. Nothing changes if an exception is thrown.
        void checkout(const vector<SaleLine>& cart, double amountPaid,
                      double& subtotal, double& gct, double& total, double& change)
        {
            total = 0.0;

            for (const SaleLine& line : cart) {
                if (line.product == nullptr || line.quantity <= 0 ||
                    line.quantity > line.product->getQuantityInStock()) {
                    throw InsufficientStockException();
                }
                total += line.product->getPrice() * line.quantity;
            }

            total = round(total * 100.0) / 100.0;

            if (amountPaid < total) {
                throw InsufficientPaymentException();
            }

            gct = calculateIncludedGCT(total);
            subtotal = total - gct;
            change = round((amountPaid - total) * 100.0) / 100.0;

            for (const SaleLine& line : cart) {
                line.product->decreaseStock(line.quantity);
                totalProductsSold += line.quantity;
                inventoryValue -= line.product->getPrice() * line.quantity;
            }

            totalRevenue += total;
            totalGCTCollected += gct;
            transactionCount++;
        }

        static void printReceipt(const vector<SaleLine>& cart, double subtotal, double gct,
                                 double total, double amountPaid, double change)
        {
            cout << fixed << setprecision(2);
            cout << "\n============ RECEIPT ============\n";
            for (const SaleLine& line : cart) {
                cout << left << setw(20) << line.product->getProductName()
                     << " x" << setw(4) << line.quantity
                     << "$" << line.product->getPrice() * line.quantity << "\n";
            }
            cout << "---------------------------------\n";
            cout << "Subtotal (before GCT): $" << subtotal << "\n";
            cout << "GCT (15%):             $" << gct << "\n";
            cout << "Total:                 $" << total << "\n";
            cout << "Amount Paid:           $" << amountPaid << "\n";
            cout << "Change:                $" << change << "\n";
            cout << "=================================\n";
        }

        void transaction(Spectator* spectator, Product* product){
            if (spectator == nullptr || product == nullptr) {
                return;
            }

            // Check that the product is available first.
            if (!product->isInStock()) {
                throw InsufficientStockException();
            }

            // Deduct payment. Throws if the spectator
            // does not have sufficient funds.
            spectator->deductBalance(product->getPrice());

            // Reduce stock by one unit.
            product->decreaseStock(1);
            spectator->buyProduct(product->getPrice());

            totalProductsSold++;
            inventoryValue -= product->getPrice();

            product->Display();
        }
};

#endif // STADIUMSHOP_H
