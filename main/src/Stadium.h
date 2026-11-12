#ifndef STADIUM_H
#define STADIUM_H

#include <string>

class Stadium
{
    private:
        int stadiumID;
        string stadiumName;
        string location;
        int seatingCapacity;
        string fieldCondition;
        double ticketPrice;
        int occupancy;

    public:
        // Default Constructor
        Stadium() {
            stadiumID = 0;
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
        int getStadiumID() {
            return stadiumID;
        }

        string getStadiumName() {
            return stadiumName;
        }

        string getLocation() {
            return location;
        }

        int getSeatingCapacity() {
            return seatingCapacity;
        }

        string getFieldCondition() {
            return fieldCondition;
        }

        double getTicketPrice() {
            return ticketPrice;
        }

        int getOccupancy() {
            return occupancy;
        }

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

};

#endif // STADIUM_H
