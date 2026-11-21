#ifndef FOOTBALLLEAGUE_H
#define FOOTBALLLEAGUE_H

#include "Player.h"
#include <string>

class FootballLeague {
private:
    int leagueID = 0;
    std::string leagueName;
    std::string season;
    std::string startDate;
    std::string endDate;
    int numberOfTeams = 0;
    std::string currentStatus;
    int minimumAge = 16;

public:
    FootballLeague() = default;

    FootballLeague(int id, const std::string& name, const std::string& leagueSeason,
                   const std::string& start, const std::string& end,
                   int teams, const std::string& status = "Active", int minAge = 16)
        : leagueID(id),
          leagueName(name),
          season(leagueSeason),
          startDate(start),
          endDate(end),
          numberOfTeams(teams >= 0 ? teams : 0),
          currentStatus(status),
          minimumAge(minAge >= 0 ? minAge : 0) {}

    // Getters
    int getLeagueID() const{
        return leagueID;
    }
    std::string getLeagueName() const{
        return leagueName;
    }
    std::string getSeason() const{
        return season;
    }
    std::string getStartDate() const{
        return startDate;
    }
    std::string getEndDate() const{
        return endDate;
    }
    int getNumberOfTeams() const{
        return numberOfTeams;
    }
    std::string getCurrentStatus() const{
        return currentStatus;
    }
    int getMinimumAge() const{
        return minimumAge;
    }

    // Setters
    void setLeagueID(int id){
        leagueID = id;
    }
    void setLeagueName(const std::string& name){
        leagueName = name;
    }
    void setSeason(const std::string& leagueSeason){
        season = leagueSeason;
    }
    void setStartDate(const std::string& start){
        startDate = start;
    }
    void setEndDate(const std::string& end){endDate = end;
    }
    void setCurrentStatus(const std::string& status){
        currentStatus = status;
    }

    void setNumberOfTeams(int teams) {
        if (teams >= 0) {
            numberOfTeams = teams;
        }
    }

    void setMinimumAge(int minAge) {
        if (minAge >= 0) {
            minimumAge = minAge;
        }
    }

    bool meetsMinimumAge(const Player& player) const {
        return player.getAge() >= minimumAge;
    }

    bool registerPlayer(const Player& player) const {
        if (!meetsMinimumAge(player)) {
            return false; 
        }
        return true;
    }
};

#endif