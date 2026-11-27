#ifndef TICKETS_H
#define TICKETS_H

#include <string>
#include <iomanip> // Provides formatting tools such as setw() and methods for aligning data.
#include <iostream>

#include "Product.h"
#include "../universal/Date.h"

using namespace std;

// Inherits common product attributes and methods from the Product class.
class Tickets : public Product
{
private:
    // Stores the category of the ticket.
    string ticketCategory;

    // Stores the date of the football match associated with the ticket.
    Date matchDate;

    // Stores the seat number assigned to the ticket.
    string seatNumber;

public:

    // Default constructor
    Tickets() : Product()
    {
        ticketCategory = "";
        seatNumber = "";
    }

    // Parameterized constructor 
    Tickets(string ticketCategory, Date matchDate, string seatNumber, int productID,
            std::string productName, double price, int quantityInStock)
        : Product(productID, productName, price, quantityInStock)
    {
        this->ticketCategory = ticketCategory;
        this->matchDate = matchDate;
        this->seatNumber = seatNumber;
    }

    // ================= GETTERS =================

    // Returns the category of the ticket.
    string getTicketCategory()
    {
        return ticketCategory;
    }

    // Returns the date of the match associated with the ticket.
    Date getMatchDate()
    {
        return matchDate;
    }

    // Returns the seat number assigned to the ticket.
    string getSeatNumber()
    {
        return seatNumber;
    }

    // ================= SETTERS =================

    // Sets or updates the ticket category.
    void setTicketCategory(string ticketCategory)
    {
        this->ticketCategory = ticketCategory;
    }

    // Sets or updates the match date associated with the ticket.
    void setMatchDate(Date matchDate)
    {
        this->matchDate = matchDate;
    }

    // Sets or updates the seat number assigned to the ticket.
    void setSeatNumber(string seatNumber)
    {
        this->seatNumber = seatNumber;
    }

    // Overrides the isTicket() method from the Product class.
    bool isTicket() const
    {
        return true;
    }

    // Overrides the Display() method inherited from the Product class.
    void Display() 
    {
        cout << "\n================================"
             << "\n      Tickets DETAILS"
             << "\n================================"
             << "\nProduct ID:       " << getProductID()
             << "\nProduct Name:     " << getProductName()
             << "\nPrice:            $" << fixed << setprecision(2) << getPrice()
             << "\nQuantity:         " << getQuantityInStock() 
             << "\nTicket Category:             " << ticketCategory
             << "\nMatch Date:            ";

        // Calls the Date class method to display the match date.
        matchDate.displayDate();

        cout << "\nSeat Number:           " << seatNumber
             << "\n================================\n";
    }
};

#endif // TICKETS_H