#ifndef FOODITEMS_H
#define FOODITEMS_H

#include <string>
#include <iomanip>

class FoodItems : public Product{
    private:
        string expiryDate;
        string category;

    public:
        // Destructor implementation from abstract parent class
        ~FoodItems() override {
            cout << "FoodItems destroyed" << endl;
        }

        // Constructors
        FoodItems() {
            expiryDate = "";
            category = "";
        }

        FoodItems(string expiryDate, string category, int productID,
        std::string productName, double price, int quantityInStock) : Product(productID, productName, price, quantityInStock) {

            this->expiryDate = expiryDate;
            this->category = category;
        }

        // Getters
        tm getExpiryDate() {
            return expiryDate;
        }

        string getCategory() {
            return category;
        }

        // Setters
        void setExpiryDate(string expiryDate) {
            this->expiryDate = expiryDate;
        }

        void setCategory(string category) {
            this->category = category;
        }

        // Display method for attributes within the class
        void Display() override{ // override tells the compiler that this method should be overriding a method in the parent class
            cout << "\n================================"
            << "\n      FoodItems DETAILS"
            << "\n================================"
            << "\nProduct ID:       " << productID
            << "\nProduct Name:     " << productName
            << "\nPrice:            $" << fixed << setprecision(2) << price
            << "\nQuantity:         " << quantityInStock
            << "\nExpiry Date:             " << expiryDate
            << "\nCategory:            " << category
            << "\n================================\n";
        }
};

#endif // FOODITEMS_H
