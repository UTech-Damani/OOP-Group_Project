#ifndef MATCHOFFICIAL_H
#define MATCHOFFICIAL_H

#include "Person.h"
#include <string>

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
            availability = false; //Official is initially unavailable
            yearsExperience = 0;  //Starts with 0 years of experience
        }

        MatchOfficial::MatchOfficial(int id, string name, int a, string g,
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
};

#endif // MATCHOFFICIAL_H
