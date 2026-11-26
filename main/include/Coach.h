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
        FootballTeam* team;
        int yearsExperience;

    public:
        Coach(){
            qualification = ""; //No qualification entered
            coachingRole = "";  //No coaching role assigned
            yearsExperience = 0;
            team = nullptr;
        }

        Coach(int id, string name, int age, string g, string qual, string role, int yearsExperience) : Person(id, name, age, g){
            qualification = qual;
            coachingRole = role;
            this->yearsExperience = yearsExperience;
        }

        //Getters
        std::string getQualification() const{
            return qualification;
        }
        std::string getCoachingRole() const{
            return coachingRole;
        }
        int getYearsExperience() const{
            return yearsExperience;
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

        void setTeam(FootballTeam* t)
        {
            if (t != nullptr)
            {
                 team = t;
            }

        }
        void setYearsExperience(int experience){
            if (experience >= 0){
                yearsExperience = experience;
            }
            else{
                cout << "Invalid Years of Experience." << endl;
            }
        }

        // Display - Damani
        void Display() override;
        

};


#endif
