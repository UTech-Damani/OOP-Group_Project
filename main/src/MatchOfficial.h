#ifndef MATCHOFFICIAL_H
#define MATCHOFFICIAL_H
#include "Person.h"
#include "Fixture.h"
#include <vector>
#include <string>

class MatchOfficial : public Person {
    std::string officiatingRole;
    std::string rank;
    bool availability = true;
    int yearsExperience = 0;
    std::vector<const Fixture*> assignedFixtures;

    public:
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
        const std::vector<const Fixture*>& getAssignedFixtures() const{
            return assignedFixtures;
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
        bool canAssignFixture(const Fixture& candidate) const{
            if(!availability){
                return false;
            }
            for(const Fixture* existing : assignedFixtures){
                if(existing != nullptr && existing->conflictsWith(candidate)){
                    return false;
                }
            }
            return true;
        }
        bool assignFixture(const Fixture& fixture){
            if(!canAssignFixture(fixture)){
                return false;
            }
            assignedFixtures.push_back(&fixture);
            return true;
        }
};

#endif