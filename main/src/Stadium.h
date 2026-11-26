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
        int stadiumID;
        string stadiumName;
        string location;
        int seatingCapacity;
        string fieldCondition;
        double ticketPrice;
        int occupancy;

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

        // Getters
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

        vector<Fixture*>& getFixtures();

        // Setters
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

        bool hasCapacityFor(int requiredSeats) const {
            return (seatingCapacity - occupancy) >= requiredSeats;
        }
        int getRemainingSeats() const {
            return seatingCapacity - occupancy;
        }
        bool isAvailable() const {
            return fieldCondition == "Good" && occupancy < seatingCapacity;
        }
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

        void addShop(StadiumShop* shop){
            shops.push_back(shop);
        }

        bool canSellTickets(int quantity) const {
            if (quantity <= 0) {
                return false;
            }
            return (occupancy + quantity) <= seatingCapacity;
        }

        void sellTickets(int quantity) {
            if (!canSellTickets(quantity)) {
                throw CapacityExceededException();
            }
            occupancy += quantity;
            
        }

        bool releaseTickets(int quantity) {
            if (quantity <= 0 || quantity > occupancy) {
                return false;
            }
            occupancy -= quantity;
            return true;
        }
        void addFixture(Fixture* fixture);

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

inline vector<Fixture*>& Stadium::getFixtures()
{
    return fixtures;
}

inline void Stadium::addFixture(Fixture* fixture)
{
    if (fixture != nullptr)
    {
        fixtures.push_back(fixture);
    }
}

#endif //
