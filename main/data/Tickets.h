#ifndef TICKETS_H
#define TICKETS_H
#include <string>
#include <iomanip>

class Tickets : public Product{
    private:
        string ticketCategory;
        string matchDate;
        string seatNumber;

    public:
        // Destructor implementation from abstract parent class
        ~Tickets() override {
                cout << "Ticket destroyed" << endl;
        }
        // Constructors
        Tickets() : Product() {
            ticketCategory = "";
            matchDate = "";
            seatNumber = "";
        }

        Tickets(string ticketCategory, string matchDate, string seatNumber, int productID,
            std::string productName, double price, int quantityInStock) : Product(productID, productName, price, quantityInStock){

            this->ticketCategory = ticketCategory;
            this->matchDate = matchDate;
            this->seatNumber = seatNumber;
        }

        // Getters
        string getTicketCategory() {
            return ticketCategory;
        }

        tm getMatchDate() {
            return matchDate;
        }

        string getSeatNumber() {
            return seatNumber;
        }

        // Setters
        void setTicketCategory(string ticketCategory) {
            this->ticketCategory = ticketCategory;
        }

        void setMatchDate(string matchDate) {
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
            << "\nProduct ID:       " << productID
            << "\nProduct Name:     " << productName
            << "\nPrice:            $" << fixed << setprecision(2) << price
            << "\nQuantity:         " << quantityInStock
            << "\nTicket Category:             " << ticketCategory
            << "\nMatch Date:            " << matchDate
            << "\nSeat Number:           " << seatNumber
            << "\n================================\n";
        }
};

#endif // TICKETS_H
