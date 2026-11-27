#ifndef STADIUM_H
#define STADIUM_H

#include "StadiumShop.h"
#include "../exceptions/CapacityExceededException.h"

#include <string>
#include <vector>
#include <sstream>

class Fixture;

using namespace std;

class Stadium : public Persistable
{
    private:
        // Stores the stadium's identification and general information
        int stadiumID;
        string stadiumName;
        string location;

        // Stores the stadium's physical condition and seating information
        int seatingCapacity;
        string fieldCondition;
        double ticketPrice;
        int occupancy;

        // Stores pointers to the shops and fixtures associated with the stadium
        vector<StadiumShop*> shops;
        vector<Fixture*> fixtures;

    public:
        // Default Constructor
        Stadium() {
            stadiumName = "";
            location = "";
            seatingCapacity = 0;
            fieldCondition = "";
            ticketPrice = 0.0;
            occupancy = 0;
        }

        // Parameterized Constructor
        Stadium(int stadiumID, string stadiumName, string location,
                int seatingCapacity, string fieldCondition,
                double ticketPrice, int occupancy) {
            this->stadiumID = stadiumID;
            this->stadiumName = stadiumName;
            this->location = location;
            this->seatingCapacity = seatingCapacity;
            this->fieldCondition = fieldCondition;
            this->ticketPrice = ticketPrice;
            this->occupancy = occupancy;
        }

        // ================= GETTERS =================

        // Returns the stadium's stored attributes

        int getStadiumID() const{
            return stadiumID;
        }

        string getStadiumName() const {
            return stadiumName;
        }

        string getLocation() const {
            return location;
        }

        int getSeatingCapacity() const {
            return seatingCapacity;
        }

        string getFieldCondition() const {
            return fieldCondition;
        }

        double getTicketPrice() const {
            return ticketPrice;
        }

        int getOccupancy() const {
            return occupancy;
        }

        // Returns the fixtures associated with the stadium
        vector<Fixture*>& getFixtures();

        // ================= SETTERS =================

        // Updates the stadium's stored attributes

        void setStadiumID(int stadiumID) {
            this->stadiumID = stadiumID;
        }

        void setStadiumName(string stadiumName) {
            this->stadiumName = stadiumName;
        }

        void setLocation(string location) {
            this->location = location;
        }

        void setSeatingCapacity(int seatingCapacity) {
            this->seatingCapacity = seatingCapacity;
        }

        void setFieldCondition(string fieldCondition) {
            this->fieldCondition = fieldCondition;
        }

        void setTicketPrice(double ticketPrice) {
            this->ticketPrice = ticketPrice;
        }

        void setOccupancy(int occupancy) {
            this->occupancy = occupancy;
        }

        // Checks whether the stadium has enough available seats
        bool hasCapacityFor(int requiredSeats) const {
            return (seatingCapacity - occupancy) >= requiredSeats;
        }

        // Calculates and returns the number of remaining seats
        int getRemainingSeats() const {
            return seatingCapacity - occupancy;
        }

        // Checks whether the stadium is in good condition and has available seats
        bool isAvailable() const {
            return fieldCondition == "Good" && occupancy < seatingCapacity;
        }

        // Increases stadium occupancy when spectators can be accommodated
        void increaseOccupancy(int spectators) {
            if (spectators <= 0) {
                cout << "Invalid number of spectators." << endl;
                return;
            }

            if (occupancy + spectators <= seatingCapacity) {
                occupancy += spectators;
            }
            else {
                cout << "Stadium capacity exceeded." << endl;
            }
        }

        // Adds a stadium shop to the stadium's collection
        void addShop(StadiumShop* shop){
            shops.push_back(shop);
        }

        // Checks whether the requested number of tickets can be sold
        bool canSellTickets(int quantity) const {
            if (quantity <= 0) {
                return false;
            }
            return (occupancy + quantity) <= seatingCapacity;
        }

        // Sells tickets by increasing occupancy
        void sellTickets(int quantity) {
            if (!canSellTickets(quantity)) {
                throw CapacityExceededException();
            }
            occupancy += quantity;

        }

        // Releases previously occupied seats
        bool releaseTickets(int quantity) {
            if (quantity <= 0 || quantity > occupancy) {
                return false;
            }
            occupancy -= quantity;
            return true;
        }

        // Adds a fixture to the stadium's scheduled fixtures
        void addFixture(Fixture* fixture);

        // Converts stadium information into a csv format
        string toFileString() const override
        {
            stringstream ss;

            ss << stadiumID << ","
            << stadiumName << ","
            << location << ","
            << seatingCapacity << ","
            << fieldCondition << ","
            << ticketPrice << ","
            << occupancy;

            return ss.str();
        }

        // Reconstructs a Stadium object from a comma-separated file record
        static Stadium fromFileString(const string& data)
        {
            stringstream ss(data);

            int id, capacity, occupancy;
            double price;
            string name, location, condition;

            char comma;

            ss >> id >> comma;
            getline(ss, name, ',');

            getline(ss, location, ',');

            getline(ss, condition, ',');

            ss >> capacity >> comma
            >> price >> comma
            >> occupancy;

            return Stadium(
                id, name, location,
                capacity, condition,
                price, occupancy
            );
        }

};

// Returns a reference to the stadium's fixture collection
inline vector<Fixture*>& Stadium::getFixtures()
{
    return fixtures;
}

// Adds a non-null fixture pointer to the stadium's fixture collection
inline void Stadium::addFixture(Fixture* fixture)
{
    if (fixture != nullptr)
    {
        fixtures.push_back(fixture);
    }
}

#endif // STADIUM_H