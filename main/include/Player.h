#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <iostream>

#include "Person.h"

class FootballTeam;

class Player : public Person {
    private:
        std::string positionOnField;
        int jerseyNom;
        int goalScored;
        std::string playerStatus;
        static const int MIN_PLAYER_AGE = 16;
        
        FootballTeam* team;

    public:
        Player() : Person()
        {
            positionOnField = ""; //No playing position assigned
            jerseyNom = 0;        //Sets jersey number to 0
            goalScored = 0;       //Player starts with 0 goals
            playerStatus = "";    //No player status assigned
            team = nullptr;
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
            team = nullptr;
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
            if (pos == "Goalkeeper" ||
                pos == "Centre Back" ||
                pos == "Left Back" ||
                pos == "Right Back" ||
                pos == "Left Wing Back" ||
                pos == "Right Wing Back" ||
                pos == "Defensive Midfielder" ||
                pos == "Central Midfielder" ||
                pos == "Attacking Midfielder" ||
                pos == "Left Midfielder" ||
                pos == "Right Midfielder" ||
                pos == "Left Winger" ||
                pos == "Right Winger" ||
                pos == "Striker" ||
                pos == "Centre Forward"){

                positionOnField = pos;
            }
            else
                {
                    cout << "Invalid playing position." << endl;
                }
        }
        void setJerseyNom(int jersey){
            if (jersey >= 0)
                {
                    jerseyNom = jersey;
                }
        }
        void setGoalScored(int goals){
            if (goals >= 0)
                {
                    goalScored = goals;
                }
        }
        void setPlayerStatus(const std::string& status){
            if (status == "Active" ||
                status == "Injured" ||
                status == "Suspended" ||
                status == "Inactive" ||
                status == "Transferred" ||
                status == "Retired")
                {
                    playerStatus = status;
                }
        }

        void setTeam(FootballTeam* t) {
            if (t != nullptr){
                team = t;
            }
        }

        void recordGoals(){

        }

        bool isEligible() const {
            return getAge() >= MIN_PLAYER_AGE;
        }

        void changeStatus(){

        }

        void Display() 
        {
            cout << "ID: " << getIdNom() << endl;
            cout << "Name: " << getFullName() << endl;
            cout << "Age: " << getAge() << endl;
            cout << "Gender: " << getGender() << endl;
            cout << "Position: " << positionOnField << endl;
            cout << "Jersey Number: " << jerseyNom << endl;
            cout << "Goals Scored: " << goalScored << endl;
            cout << "Player Status: " << playerStatus << endl;
        }

};


#endif // PLAYER_H
