#ifndef FOOTBALLTEAM_H
#define FOOTBALLTEAM_H
#include <string>
#include <vector>
#include <sstream>

#include "Player.h"
#include "Coach.h"
#include "../universal/Date.h"
#include "../exceptions/CapacityExceededException.h"
#include "../exceptions/UnderageExceptions.h"
#include "../exceptions/DuplicateRegistrationException.h"
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
        static const int maxPlayers = 24;

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
    int getTeamID() const { 
        return teamID; 
    }
    string getTeamName() const {
        return teamName; 
    }
    string getParish() const {
        return parish;
    }
    void getRegistrationDate() { 
        registrationDate.displayDate(); 
    }
    int getPoints() const {
        return points; 
    }
    int getWins() const { 
        return wins; 
    }
    int getDraws() const { 
        return draws; 
    }
    int getLosses() const { 
        return losses; 
    }
    string getTeamStatus() const { 
        return teamStatus; 
    }

    int getGoalDifference() const {
        return goalDifference;
    }
    int getGoalsFor() const {
        return goalsFor;
    }
    int getGoalsAgainst() const {
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
        return teamStatus == "registered" || teamStatus == "approved";
    }
    // Adding each player object to their respective team
    void addPlayer(Player& p){
        if(players.size() >= static_cast<size_t>(maxPlayers))
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
        players.back().setTeam(this);
    }
    void addCoach(Coach& c){
        for(Coach coach : coaches){
            if(c.getIdNom() == coach.getIdNom())
            {
                throw DuplicateRegistrationException();
            }
        }

        coaches.push_back(c);
        coaches.back().setTeam(this);
    }

    void rebindMembers()
    {
        for (Player& player : players) player.setTeam(this);
        for (Coach& coach : coaches) coach.setTeam(this);
    }

    bool updateTeamDetails(const string& name, const string& teamParish)
    {
        if (name.empty() || teamParish.empty()) return false;
        teamName = name;
        parish = teamParish;
        return true;
    }

    Player* findPlayer(int playerID)
    {
        for (Player& player : players)
            if (player.getIdNom() == playerID) return &player;
        return nullptr;
    }

    Coach* findCoach(int coachID)
    {
        for (Coach& coach : coaches)
            if (coach.getIdNom() == coachID) return &coach;
        return nullptr;
    }

    bool removePlayer(int playerID)
    {
        for (vector<Player>::iterator it = players.begin(); it != players.end(); ++it)
            if (it->getIdNom() == playerID) { players.erase(it); return true; }
        return false;
    }

    bool removeCoach(int coachID)
    {
        for (vector<Coach>::iterator it = coaches.begin(); it != coaches.end(); ++it)
            if (it->getIdNom() == coachID) { coaches.erase(it); return true; }
        return false;
    }

    bool updatePlayer(int playerID, const string& position, int jersey, const string& status)
    {
        Player* player = findPlayer(playerID);
        if (!player || jersey < 0) return false;
        player->setPositionOnField(position);
        player->setJerseyNom(jersey);
        player->setPlayerStatus(status);
        return true;
    }

    bool updateCoach(int coachID, const string& qualification,
                     const string& role, int experience)
    {
        Coach* coach = findCoach(coachID);
        if (!coach || experience < 0) return false;
        coach->setQualification(qualification);
        coach->setCoachingRole(role);
        coach->setYearsExperience(experience);
        return true;
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

    string toFileString() const{
        stringstream ss;

        ss << teamID << ","
        << teamName << ","
        << parish << ","
        << points << ","
        << wins << ","
        << draws << ","
        << losses << ","
        << teamStatus << ","
        << registrationDate.getDay() << ","
        << registrationDate.getMonth() << ","
        << registrationDate.getYear() << ","
        << goalsFor << "," << goalsAgainst << "," << goalDifference;

        return ss.str();
    }
    static FootballTeam fromFileString(const string& data)
    {
        stringstream ss(data);

        int id, points, wins, draws, losses;
        int day, month, year;
        string name, parish, status;
        char comma;

        ss >> id >> comma;
        getline(ss, name, ',');
        getline(ss, parish, ',');
        ss >> points >> comma
           >> wins >> comma
           >> draws >> comma
           >> losses >> comma;
        getline(ss, status, ',');
        ss >> day >> comma >> month >> comma >> year;
        FootballTeam team(id, name, parish, points, wins, draws,
                          losses, status, day, month, year);
        int gf=0, ga=0, gd=0;
        if (ss.peek()==',') ss >> comma >> gf;
        if (ss.peek()==',') ss >> comma >> ga;
        if (ss.peek()==',') ss >> comma >> gd;
        team.addGoalsFor(gf);
        team.addGoalsAgainst(ga);
        team.calcGoalDifference();
        return team;
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