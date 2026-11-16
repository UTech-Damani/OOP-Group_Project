#ifndef FOOTBALLTEAM_H
#define FOOTBALLTEAM_H
#include <string>
#include <vector>

#include "Player.h"
#include "Coach.h"
#include "Date.h"

using namespace std;

class FootballTeam {
    private:
        int teamID;
        string teamName;
        Date registrationDate;
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
    FootballTeam(int teamID, string teamName,
        int points, int wins, int draws,
        int losses, string teamStatus, int day, int month, int year) {
        this->teamID = teamID;
        this->teamName = teamName;
        registrationDate.setDay(day);
        registrationDate.setMonth(month);
        registrationDate.setYear(year);
        this->points = points;
        this->wins = wins;
        this->draws = draws;
        this->losses = losses;
        this->teamStatus = teamStatus;
    }
    
    // Getters
    int getTeamID() { return teamID; }
    string getTeamName() { return teamName; }
    void getRegistrationDate() { registrationDate.displayDate(); }
    int getPoints() { return points; }
    int getWins() { return wins; }
    int getDraws() { return draws; }
    int getLosses() { return losses; }
    string getTeamStatus() { return teamStatus; }
    
    // Setters
    void setTeamID(int teamID) { this->teamID = teamID; }
    void setTeamName(string teamName) { this->teamName = teamName; }
    void setRegistrationDate(int day, int month, int year) {
        registrationDate.setDay(day);
        registrationDate.setMonth(month);
        registrationDate.setYear(year);
    }
    void setPoints(int points) { this->points = points; }
    void setWins(int wins) { this->wins = wins; }
    void setDraws(int draws) { this->draws = draws; }
    void setLosses(int losses) { this->losses = losses; }
    void setTeamStatus(string teamStatus) { this->teamStatus = teamStatus; }

    // Rule 2: Update this team's record based on the match outcome.
    void updateLeaguePoints(const std::string& result) {
        if (result == "win") {
            ++wins;
            points += 3;
        } else if (result == "draw") {
            ++draws;
            points += 1;
        } else if (result == "loss") {
            ++losses; // Count the loss, but add no points.
        }
    }

    // Rule 3: Accept only registered teams.
    // "unregistered" and "suspended" both return false.
    bool canParticipate() const {
        return teamStatus == "registered";
    }
    // Adding each player object to their respective team
    void addPlayer(Player& p){
        players.push_back(p);
        p.setTeam(this);
    }
    void addCoach(Coach& c){
        coaches.push_back(c);
        c.setTeam(this);
    }
};

#endif // FOOTBALLTEAM_H
 