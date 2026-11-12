#ifndef PRODUCT_H
#define PRODUCT_H
#include <string>

class Product
{
    private:
        int productID;
        std::string productName;
        double price;
        int quantityInStock;

    public:
        //Default Constructor
        Product() {
            productID = 0;
            productName = "";
            price = 0.0;
            quantityInStock = 0;
        }

        //Primary Constructor
        Product(int pID, std::string pName, double cost, int quantity) {
            productID = pID;
            productName = pName;
            price = cost;
            quantityInStock = quantity;
        }

        // Sets the product ID
        void setProductID(int id) {
            productID = id;
        }

        // Returns the product ID
        int getProductID() const {
            return productID;
        }

        // Sets the product name
        void setProductName(std::string name) {
            productName = name;
        }

        // Returns the product name
        std::string getProductName() const {
            return productName;
        }

        // Sets the product price
        void setPrice(double p) {
            price = p;
        }

        // Returns the product price
        double getPrice() const {
            return price;
        }

        // Sets the quantity of the product in stock
        void setQuantityInStock(int quantity) {
            quantityInStock = quantity;
        }

        // Returns the quantity of the product in stock
        int getQuantityInStock() const {
            return quantityInStock;
        }



};

#endif // PRODUCT_H
