#ifndef STADIUM_H
#define STADIUM_H
#include <string>

class Stadium {
    int stadiumID = 0;
    std::string stadiumName;
    std::string location;
    int seatingCapacity = 0;
    std::string fieldCondition;
    double ticketPrice = 0.0;
    int occupancy = 0; // Tracks current tickets sold / seats occupied

public:
    Stadium() = default;

    Stadium(int id, const std::string& name, const std::string& loc,
            int capacity, const std::string& condition = "Good",
            double price = 0.0, int currentOccupancy = 0)
        : stadiumID(id),
          stadiumName(name),
          location(loc),
          seatingCapacity(capacity >= 0 ? capacity : 0),
          fieldCondition(condition),
          ticketPrice(price >= 0.0 ? price : 0.0),
          occupancy(0) {
        if (currentOccupancy > 0) {
            sellTickets(currentOccupancy);
        }
    }

    // Getters
    int getStadiumID() const{ 
        return stadiumID;
    }
    std::string getStadiumName() const{
        return stadiumName;
    }
    std::string getLocation() const{
        return location;
    }
    int getSeatingCapacity() const{
        return seatingCapacity;
    }
    std::string getFieldCondition() const{
        return fieldCondition;
    }
    double getTicketPrice() const{
        return ticketPrice;
    }
    int getOccupancy() const{
        return occupancy;
    }
    int getAvailableSeats() const{
        return seatingCapacity - occupancy;
    }

    // Setters
    void setStadiumID(int id){
        stadiumID = id;
    }
    void setStadiumName(const std::string& name){
        stadiumName = name;
    }
    void setLocation(const std::string& loc){
        location = loc;
    }
    void setFieldCondition(const std::string& condition){
        fieldCondition = condition;
    }

    void setSeatingCapacity(int capacity){
        if (capacity < 0) {
            return;
        }
        seatingCapacity = capacity;
        if (occupancy > seatingCapacity) {
            occupancy = seatingCapacity;
        }
    }

    void setTicketPrice(double price) {
        if (price >= 0.0) {
            ticketPrice = price;
        }
    }

    bool canSellTickets(int quantity) const {
        if (quantity <= 0) {
            return false;
        }
        return (occupancy + quantity) <= seatingCapacity;
    }

    bool sellTickets(int quantity) {
        if (!canSellTickets(quantity)) {
            return false; // Exceeds seating capacity or invalid quantity
        }
        occupancy += quantity;
        return true;
    }

    bool releaseTickets(int quantity) {
        if (quantity <= 0 || quantity > occupancy) {
            return false;
        }
        occupancy -= quantity;
        return true;
    }
};

#endif