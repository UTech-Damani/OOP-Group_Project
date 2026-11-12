#ifndef COACH_H
#define COACH_H

#include "FootballTeam.h"


class Coach{
    private:
        std::string qualificaton;
        std::string coachingRole;
        std::string teamAssignment;
        FootballTeam* team;

    public:
        Coach(){
            qualification = ""; //No qualification entered
            coachingRole = "";  //No coaching role assigned
            teamAssignment = ""; //No team assigned
        }

        Coach(int id, string name, int a, string g, string qual, string role, string team){
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

};


#endif
