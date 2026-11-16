#ifndef SPECTATOR_H
#define SPECTATOR_H

#include "Person.h"
#include <iostream>

using namespace std;

class Spectator : public Person{
    private:
        int ticketsPurchased;
        double totalAmountSpent;

    public:
        Spectator() : Person()
        {
            //initialized to zero as nothing has been stored yet
            ticketsPurchased = 0;
            totalAmountSpent =  0.0;
        }

        Spectator(int id, string name, int a, string g,
                     int tickets, double amount)
                    : Person(id, name, a, g) //Sends information to Person
        {
            ticketsPurchased = tickets; //Stores the number of tickets purchased
            totalAmountSpent = amount;  //Stores the total money spent
        }

        //Getters
        int getTicketsPurchased() const{
            return ticketsPurchased;
        }
        double getTotalAmountSpent() const{
            return totalAmountSpent;
        }

        //Setters
        void setTicketsPurchased(int tickets){
            ticketsPurchased = tickets;
        }
        void setTotalAmountSpent( double total){
            totalAmountSpent = total;
        }

        void buyTicket(){

        }
        void buyProduct(){

        }
        void addToTotalSpent(){
            
        }

        void Display(){
            cout << "ID: " << getIdNom() << endl;
            cout << "Name: " << getFullName() << endl;
            cout << "Age: " << getAge() << endl;
            cout << "Gender: " << getGender() << endl;
            cout << "Tickets Purchased: " << ticketsPurchased << endl;
            cout << "Total Amount Spent: $" << totalAmountSpent << endl;
        }
};


#endif // SPECTATOR_H
