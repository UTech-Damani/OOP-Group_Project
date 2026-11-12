#ifndef FOOTBALLTEAM_H
#define FOOTBALLTEAM_H
#include <string>
#include <vector>

#include "Player.h"
#include "Coach.h"

class FootballTeam {
    private:
        int teamID;
        string teamName;
        string registrationDate;
        int points;
        int wins;
        int draws;
        int losses;
        string teamStatus;

        std::vector <Player> players;
        std::vector <Coach> coaches;
     
    public:
    // Default Constructor
    FootballTeam() {}
     
    // Parameterized Constructor
    FootballTeam(int teamID, string teamName, string registrationDate,
        int points, int wins, int draws,
        int losses, string teamStatus) {
        this->teamID = teamID;
        this->teamName = teamName;
        this->registrationDate = registrationDate;
        this->points = points;
        this->wins = wins;
        this->draws = draws;
        this->losses = losses;
        this->teamStatus = teamStatus;
    }
     
    // Getters
    int getTeamID() { return teamID; }
    string getTeamName() { return teamName; }
    string getRegistrationDate() { return registrationDate; }
    int getPoints() { return points; }
    int getWins() { return wins; }
    int getDraws() { return draws; }
    int getLosses() { return losses; }
    string getTeamStatus() { return teamStatus; }
     
    // Setters
    void setTeamID(int teamID) { this->teamID = teamID; }
    void setTeamName(string teamName) { this->teamName = teamName; }
    void setRegistrationDate(string registrationDate) { this->registrationDate = registrationDate; }
    void setPoints(int points) { this->points = points; }
    void setWins(int wins) { this->wins = wins; }
    void setDraws(int draws) { this->draws = draws; }
    void setLosses(int losses) { this->losses = losses; }
    void setTeamStatus(string teamStatus) { this->teamStatus = teamStatus; }

    // Adding each player object to their respective team
    void addPlayer(Player p){
        players.push_back(p);
        p.setTeam(this);
    }
    void addCoach(Coach c){
        coaches.push_back(c);
        c.setTeam(this);
    }
};

#endif // FOOTBALLTEAM_H
