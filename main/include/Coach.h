#ifndef COACH_H
#define COACH_H

#include <string>
#include <iostream>

using namespace std;

class FootballTeam;

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

    //Setters with validation - Monecia
        // if any of these are not entered then it is invalid
        void setQualification(const std::string& qual){
            if (qual == "Level 1" ||
                qual == "Level 2" ||
                qual == "Level 3")
            {
                qualification = qual;
            }
            else
            {
                cout << "Invalid qualification." << endl;
            }
        }
        void setCoachingRole( const std::string& role){
             if (role == "Head Coach" ||
                 role == "Assistant Coach" ||
                 role == "Goalkeeping Coach")
            {
                coachingRole = role;
            }
        
            else
            {
                 cout << "Invalid coaching role." << endl;
            }
        }
        void setTeamAssignment(const std::string& assigns)
        {
            if (assigns == "Harbour FC" ||
                assigns == "Kingston United" ||
                assigns == "Clarendon FC")
                {
                    teamAssignment = assigns;
                }

            else
                {
                    cout << "Invalid team assignment." << endl;
                }
        }

        void setTeam(FootballTeam* t)
        {
            if (t != nullptr)
            {
                 team = t;
            }

        }

        // Display - Damani
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
