#ifndef SPECTATOR_H
#define SPECTATOR_H

#include "Person.h"
#include "../exceptions/InsufficientPaymentException.h"

#include <iostream>

using namespace std;

class Spectator : public Person{
    private:
        int ticketsPurchased;
        int productsPurchased;
        double totalAmountSpent;
        double balance;

    public:
        Spectator() : Person()
        {
            ticketsPurchased = 0;
            productsPurchased = 0;
            totalAmountSpent =  0.0;
            balance = 0.0;
        }

        Spectator(int id, string name, int a, string g,
                     int tickets, double amount, double balance)
                    : Person(id, name, a, g) //Sends information to Person
        {
            ticketsPurchased = tickets; //Stores the number of tickets purchased
            productsPurchased = 0;
            totalAmountSpent = amount;  //Stores the total money spent
            this->balance = balance;
        }

        //Getters
        int getTicketsPurchased() const{
            return ticketsPurchased;
        }
        double getTotalAmountSpent() const{
            return totalAmountSpent;
        }
        double getBalance() const{
            return balance;
        }

        //Setters
        void setTicketsPurchased(int tickets){
            if (tickets >= 0){
                ticketsPurchased = tickets;
            }
        }
        void setTotalAmountSpent(double total){
             if (total >= 0){
                totalAmountSpent = total;
            }
        }
        void setBalance(double bal){
            if(bal >= 0){
                balance = bal;
            }
        }

        void buyTicket(){
            ticketsPurchased++;
        }
        void buyProduct(double price){
            productsPurchased++;
            totalAmountSpent += price;
        }
        void deductBalance(double amount){
            if(balance < amount)
            {
                throw InsufficientPaymentException();
            }

            balance -= amount;
        }
        void addToTotalSpent(double amount){
            if (amount >= 0) {
                totalAmountSpent += amount;
            }
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
