#ifndef MATCHOFFICIAL_H
#define MATCHOFFICIAL_H

#include "Person.h"
#include <string>
#include <iostream>

class MatchOfficial : public Person {
    std::string officiatingRole;
    std::string rank;
    bool availability;
    int yearsExperience;

    public:

        MatchOfficial() : Person()
        {
            officiatingRole = ""; //No officiating role assigned
            rank = "";            //No rank assigned
            availability = true; //Official is initially available
            yearsExperience = 0;  //Starts with 0 years of experience
        }

        MatchOfficial(int id, string name, int a, string g,
                             string role, string r, bool available,
                             int experience)
                            : Person(id, name, a, g)

        {
            officiatingRole = role;      //Stores the official's role
            rank = r;                    //Stores the official's rank
            availability = available;    //Stores whether the official is available
            yearsExperience = experience; //Stores years of experience
        }

        //Getters
        std::string getOfficiatingRole() const{
            return officiatingRole;
        }
        std::string getRank() const{
            return rank;
        }
        bool getAvailability() const{
            return availability;
        }
        int getYearsExperience() const{
            return yearsExperience;
        }

        //Setters
        void setOfficiatingRole(const std::string& oRole){
            officiatingRole = oRole;
        }
        void setRank(const std::string& r){
            rank = r;
        }
        void setAvailability(bool ava){
            availability = ava;
        }
        void setYearsExperience(int years){
            yearsExperience = years;
        }

        void hasConflict(){

        }

        void assignToFixture(){
            
        }

        void Display()
        {
            cout << "ID: " << getIdNom() << endl;
            cout << "Name: " << getFullName() << endl;
            cout << "Age: " << getAge() << endl;
            cout << "Gender: " << getGender() << endl;
            cout << "Role: " << officiatingRole << endl;
            cout << "Rank: " << rank << endl;
            cout << "Availability: "
                << (availability ? "Available" : "Unavailable")
                << endl;
            cout << "Years of Experience: "
                << yearsExperience << endl;
        }
};

#endif // MATCHOFFICIAL_H
