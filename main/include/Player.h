#ifndef PLAYER_H
#define PLAYER_H
#include <string>

#include "Person.h"
#include "FootballTeam.h"

class Player : public Person {
    private:
        std::string positionOnField;
        int jerseyNom;
        int goalScored;
        std::string playerStatus;
        FootballTeam* team;

    public:
        Player() : Person()
        {
            positionOnField = ""; //No playing position assigned
            jerseyNom = 0;        //Sets jersey number to 0
            goalScored = 0;       //Player starts with 0 goals
            playerStatus = "";    //No player status assigned
        }

        Player(int id, string name, int a, string g,
               string position, int jersey, int goals,
               string status)
            : Person(id, name, a, g)
        {
            positionOnField = position; //Stores the playing position
            jerseyNom = jersey;        //Stores the player's jersey number
            goalScored = goals;        //Stores the number of goals scored
            playerStatus = status;     //Stores the player's current status
        }

        //Getters
        std::string getPositionOnField() const{
            return positionOnField;
        }
        int getJerseyNom() const{
            return jerseyNom;
        }
        int getGoalScored() const{
            return goalScored;
        }
        std::string getPlayerStatus() const{
            return playerStatus;
        }

        //Setters
        void setPositionOnField(const std::string& pos){
            positionOnField = pos;
        }
        void setJerseyNom(int jersey){
            jerseyNom = jersey;
        }
        void setGoalScored(int goals){
            goalScored = goals;
        }
        void setPlayerStatus(const std::string& status){
            playerStatus = status;
        }

        void setTeam(FootballTeam* t) {
            team = t;
        }
};


#endif // PLAYER_H
