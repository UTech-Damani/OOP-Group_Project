#ifndef FOOTBALLTEAM_H
#define FOOTBALLTEAM_H
#include <string>
#include <vector>

#include "Player.h"
#include "Coach.h"
#include "../universal/Date.h"
#include "../exceptions/DuplicateRegistrationException.h"
#include "../exceptions/CapacityExceededException.h"
#include "../universal/FileManager.h"

using namespace std;

class FootballTeam : public Persistable {
    private:
        int teamID;
        string teamName;
        string parish;
        Date registrationDate;
        int points; 
        int wins;
        int draws;
        int losses;

        int goalsFor = 0;
        int goalsAgainst = 0;
        int goalDifference = 0;
        const int maxPlayers = 24;

        string teamStatus;

        std::vector <Player> players;
        std::vector <Coach> coaches;
    
    public:
    // Default Constructor
    FootballTeam() {
        goalsFor = 0;
        goalsAgainst = 0;
        goalDifference = 0;
        teamID = 0;
        points = 0;
        wins = 0;
        draws = 0;
        losses = 0;
    }
    
    // Parameterized Constructor
    FootballTeam(int teamID, string teamName, string parish,
        int points, int wins, int draws,
        int losses, string teamStatus, int day, int month, int year) {
        this->teamID = teamID;
        this->teamName = teamName;
        this->parish = parish;
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
    int getTeamID() { 
        return teamID; 
    }
    string getTeamName() {
        return teamName; 
    }
    string getParish(){
        return parish;
    }
    void getRegistrationDate() { 
        registrationDate.displayDate(); 
    }
    int getPoints() {
        return points; 
    }
    int getWins() { 
        return wins; 
    }
    int getDraws() { 
        return draws; 
    }
    int getLosses() { 
        return losses; 
    }
    string getTeamStatus() { 
        return teamStatus; 
    }

    int getGoalDifference(){
        return goalDifference;
    }
    int getGoalsFor(){
        return goalsFor;
    }
    int getGoalsAgainst(){
        return goalsAgainst;
    }

    std::vector<Player>& getPlayers(){
        return players;
    }
    
    std::vector<Coach>& getCoaches(){
        return coaches;
    }
    
    // Setters - Monecia Implementation Starts
    void setTeamID(int teamID) { 
        if (teamID > 0)
            {
                this->teamID = teamID;
            } 
    }
    void setTeamName(string teamName) { 
        if (teamName != "")
            {
                this->teamName = teamName;
            }
    }

    void setParish(string parish){
        this->parish = parish;
    }
    void setRegistrationDate(int day, int month, int year) {
        registrationDate.setDay(day);
        registrationDate.setMonth(month);
        registrationDate.setYear(year);
    }
    void setPoints(int points) { 
        if (points >= 0)
            {
                this->points = points;
            }
    }
    void setWins(int wins) { 
        if (wins >= 0)
            {
                this->wins = wins;
            }
    }
    void setDraws(int draws) { 
        if (draws >= 0)
            {
                this->draws = draws;
            } 
    }
    void setLosses(int losses) { 
        if (losses >= 0)
            {
                this->losses = losses;
            } 
    }
    void setTeamStatus(string teamStatus) { 
        if (teamStatus == "registered" ||
            teamStatus == "unregistered" ||
            teamStatus == "suspended"    ||
            teamStatus == "approved")
            {
                this->teamStatus = teamStatus;
            } 
    }
    // Setters - Monecia Implementation Ends

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
        if(players.size() >= maxPlayers)
        {
            throw CapacityExceededException("max");
        }
        if(p.isEligible() == false){
            throw UnderageException();
        }

        for(Player player : players){
            if(p.getIdNom() == player.getIdNom())
            {
                throw DuplicateRegistrationException();
            }
        }
        
        players.push_back(p);
        p.setTeam(this);
    }
    void addCoach(Coach& c){
        for(Coach coach : coaches){
            if(c.getIdNom() == coach.getIdNom())
            {
                throw DuplicateRegistrationException();
            }
        }

        coaches.push_back(c);
        c.setTeam(this);
    }

    void addGoalsFor(int goal){
        goalsFor += goal;
    }

    void addGoalsAgainst(int goal){
        goalsAgainst += goal;
    }

    void calcGoalDifference(){
        goalDifference = goalsFor - goalsAgainst;
    }

    void viewTeamMembers()
    {
        cout << "\n===== PLAYERS =====\n";

        for (Player& player : players)
        {
        player.Display();
        cout << "-------------------\n";
        }

        cout << "\n===== COACHES =====\n";

        for (Coach& coach : coaches)
        {
        coach.Display();
        cout << "-------------------\n";
        }
    }

    

    
};
 
inline void Coach::Display()
{
    cout << "ID: " << getIdNom() << endl;
    cout << "Name: " << getFullName() << endl;
    cout << "Age: " << getAge() << endl;
    cout << "Gender: " << getGender() << endl;
    cout << "Qualification: " << qualification << endl;
    cout << "Coaching Role: " << coachingRole << endl;

    if (team != nullptr) {
        cout << "Team Assignment: " << team->getTeamName() << endl;
    }
    else {
        cout << "Team Assignment: Not Assigned" << endl;
    }
}

#endif // FOOTBALLTEAM_H