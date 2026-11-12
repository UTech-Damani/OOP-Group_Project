#ifndef MERCHANDISE_H
#define MERCHANDISE_H
#include <string>
#include <iomanip>

class Merchandise : public Product{
    private:
        string sizeOfItem;
        string brand;

    public:
        // Destructor implementation from abstract parent class
        ~Merchandise() override {
            cout << "Merchandise destroyed" << endl;
        }
        // Constructors
        Merchandise() {
            sizeOfItem = "";
            brand = "";
        }

        Merchandise(string sizeOfItem, string brand, int productID,
        std::string productName, double price, int quantityInStock) : Product(productID, productName, price, quantityInStock)

            this->size = size;
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
            this->sizeOfItem = sizeOfItem;
        }

        void setBrand(string brand) {
            this->brand = brand;
        }

        // Display method for attributes within the class
        void Display() override{ // override tells the compiler that this method should be overriding a method in the parent class
            cout << "\n================================"
            << "\n      MERCHANDISE DETAILS"
            << "\n================================"
            << "\nProduct ID:       " << productID
            << "\nProduct Name:     " << productName
            << "\nPrice:            $" << fixed << setprecision(2) << price
            << "\nQuantity:         " << quantityInStock
            << "\nSize:             " << sizeOfItem
            << "\nBrand:            " << brand
            << "\n================================\n";
        }


};
#endif // MERCHANDISE_H
