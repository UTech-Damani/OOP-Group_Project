#ifndef TICKETS_H
#define TICKETS_H
#include <string>
#include <iomanip>
#include <iostream>

#include "Product.h"
#include "Date.h"

using namespace std;

class Tickets : public Product{
    private:
        string ticketCategory;
        Date matchDate;
        string seatNumber;

    public:
        // Constructors
        Tickets() : Product() {
            ticketCategory = "";
            
            seatNumber = "";
        }

        Tickets(string ticketCategory, Date matchDate, string seatNumber, int productID,
            std::string productName, double price, int quantityInStock) : Product(productID, productName, price, quantityInStock){

            this->ticketCategory = ticketCategory;
            this->matchDate = matchDate;
            this->seatNumber = seatNumber;
        }

        // Getters
        string getTicketCategory() {
            return ticketCategory;
        }

        Date getMatchDate() {
            return matchDate;
        }

        string getSeatNumber() {
            return seatNumber;
        }

        // Setters
        void setTicketCategory(string ticketCategory) {
            this->ticketCategory = ticketCategory;
        }

        void setMatchDate(Date matchDate) {
            this->matchDate = matchDate;
        }

        void setSeatNumber(string seatNumber) {
            this->seatNumber = seatNumber;
        }

        // Display method for attributes within the class
        void Display() override{ // override tells the compiler that this method should be overriding a method in the parent class
            cout << "\n================================"
            << "\n      Tickets DETAILS"
            << "\n================================"
            << "\nProduct ID:       " << getProductID()
            << "\nProduct Name:     " << getProductName()
            << "\nPrice:            $" << fixed << setprecision(2) << getPrice()
            << "\nQuantity:         " << getQuantityInStock()
            << "\nTicket Category:             " << ticketCategory
            << "\nMatch Date:            "; 
            matchDate.displayDate();
            cout << "\nSeat Number:           " << seatNumber
            << "\n================================\n";
        }
};

#endif // TICKETS_H
