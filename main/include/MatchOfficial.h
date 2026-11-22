#ifndef MATCHOFFICIAL_H
#define MATCHOFFICIAL_H

#include "Person.h"
#include "../src/Fixture.h"
#include <vector>

#include <string>

class Fixture;

class MatchOfficial : public Person {
    std::string officiatingRole;
    std::string rank;
    bool availability;
    int yearsExperience;
    std::vector<const Fixture*> assignedFixtures;

    public:

        MatchOfficial() : Person()
        {
            officiatingRole = ""; //No officiating role assigned
            rank = "";            //No rank assigned
            availability = false; //Official is initially unavailable
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

        //Getters - Aaron
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

        const std::vector<const Fixture*>& getAssignedFixtures() const{
            return assignedFixtures;
        }

        // Setters with validation - Monecia

        // Set officiating role
        void setOfficiatingRole(const std::string& oRole){
            if (oRole != ""){
                officiatingRole = oRole;
            }
        }

        // Set rank
        void setRank(const std::string& r){
            if (r != ""){
                rank = r;
            }
        }

        // Set availability
        void setAvailability(bool ava){
            availability = ava;
        }

        // Set years of experience
        void setYearsExperience(int years){
            if (years >= 0)
            {
                yearsExperience = years;
            }
        }

        bool canAssignFixture() const{
            return availability;
        }

        bool assignFixture(const Fixture& fixture){
            assignedFixtures.push_back(&fixture);
            return true;
        }
        void Display(){
            cout << "\nOfficial ID: " << getIdNom();
            cout << "\nName: " << getFullName();
            cout << "\nRole: " << officiatingRole;
            cout << "\nRank: " << rank;
            cout << "\nExperience: " << yearsExperience;
        }
};

#endif 
