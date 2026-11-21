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

        // Setters with validation

        // Set officiating role
        void setOfficiatingRole(const std::string& oRole)
        {
            if (oRole != "")
                {
                    officiatingRole = oRole;
                }
        }

        // Set rank
        void setRank(const std::string& r)
        {
            if (r != "")
                {
                    rank = r;
                }
        }

        // Set availability
        void setAvailability(bool ava)
            {
                availability = ava;
            }

        // Set years of experience
        void setYearsExperience(int years)
            {
                if (years >= 0)
                {
                    yearsExperience = years;
                }
            }

          // Set availability
        void setAvailability(bool ava)
        {
            availability = ava;
        }

        // Set years of experience
        void setYearsExperience(int years)
        {
            if (years >= 0) //cannot be anything under 0
                {
                    yearsExperience = years;
                }
        }
};

#endif // MATCHOFFICIAL_H
