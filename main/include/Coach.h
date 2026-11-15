#ifndef COACH_H
#define COACH_H

#include "FootballTeam.h"

#include <string>
#include <iostream>

using namespace std;

class Coach : public Person{
    private:
        std::string qualification;
        std::string coachingRole;
        std::string teamAssignment;
        FootballTeam* team;

    public:
        Coach(){
            qualification = ""; //No qualification entered
            coachingRole = "";  //No coaching role assigned
            teamAssignment = ""; //No team assigned
        }

        Coach(int id, string name, int a, string g, string qual, string role, string team) : Person(id, name, a, g){
            qualification = qual;
            coachingRole = role;
            teamAssignment = team;
        }

        //Getters
        std::string getQualification() const{
            return qualification;
        }
        std::string getCoachingRole() const{
            return coachingRole;
        }
        std::string getTeamAssignment() const{
            return teamAssignment;
        }

        //Setters
        void setQualification(const std::string& qual){
            qualification = qual;
        }
        void setCoachingRole( const std::string& role){
            coachingRole = role;
        }
        void setTeamAssignment(const std::string& assigns){
            teamAssignment = assigns;
        }

        void setTeam(FootballTeam* t){
            team = t;
        }

        void Display() 
        {
            cout << "ID: " << getIdNom() << endl;
            cout << "Name: " << getFullName() << endl;
            cout << "Age: " << getAge() << endl;
            cout << "Gender: " << getGender() << endl;
            cout << "Qualification: " << qualification << endl;
            cout << "Coaching Role: " << coachingRole << endl;
            cout << "Team Assignment: " << teamAssignment << endl;
        }

};


#endif
