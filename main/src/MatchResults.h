
#ifndef MATCHRESULTS_H
#define MATCHRESULTS_H

#include "FootballTeam.h"

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

class MatchResult {
private:
    int homeScore;
    int awayScore;
    string winner;
    string matchStatistics;

public:
    // Default constructor
    MatchResult() {
        homeScore = 0;
        awayScore = 0;
        winner = "";
        matchStatistics = "";
    }

    // Parameterized constructor
    MatchResult(int homeScore, int awayScore,
                string winner, string matchStatistics) {
        this->homeScore = homeScore;
        this->awayScore = awayScore;
        this->winner = winner;
        this->matchStatistics = matchStatistics;
    }

    // Getters
    int getHomeScore() const {
        return homeScore;
    }

    int getAwayScore() const {
        return awayScore;
    }

    string getWinner() const {
        return winner;
    }

    string getMatchStatistics() const {
        return matchStatistics;
    }

    // Setters
    bool setHomeScore(int homeScore) {
        if (homeScore < 0) {
            return false; 
        }

        this->homeScore = homeScore;
        
        return true;
    }

    bool setAwayScore(int awayScore) {
        if (awayScore < 0) {
            return false; 
        }
        this->awayScore = awayScore;

        return true;
    }

    void setMatchStatistics(string matchStatistics) {
        this->matchStatistics = matchStatistics;
    }

    // Determine the winner
    void determineWinner(FootballTeam& home, FootballTeam& away) {
        if (homeScore > awayScore) {
            winner = home.getTeamName();
            home.updateLeaguePoints("win");
            away.updateLeaguePoints("loss");
        }
        else if (awayScore > homeScore) {
            winner = away.getTeamName();
            away.updateLeaguePoints("win");
            home.updateLeaguePoints("loss");
        }
        else {
            winner = "Draw";
            home.updateLeaguePoints("draw");
            away.updateLeaguePoints("draw");
        }
    }

    // Randomize match scores
    void randomizeResults() {
        int homeGoals = rand() % 13;
        int awayGoals = rand() % 13;

        setHomeScore(homeGoals);
        setAwayScore(awayGoals);
    }

    // Calculate home team points
    int getHomePoints() const {
        if (homeScore > awayScore) {
            return 3;
        }
        else if (homeScore == awayScore) {
            return 1;
        }
        else {
            return 0;
        }
    }

    // Calculate away team points
    int getAwayPoints() const {
        if (awayScore > homeScore) {
            return 3;
        }
        else if (awayScore == homeScore) {
            return 1;
        }
        else {
            return 0;
        }
    }

    // Validate match scores
    bool validateScores() const {
        return homeScore >= 0 && awayScore >= 0;
    }

    // Display match result
    void Display() const {
        cout << "\n========== Match Result ==========" << endl;
        cout << "Home Score: " << homeScore << endl;
        cout << "Away Score: " << awayScore << endl;
        cout << "Winner: " << winner << endl;
        cout << "Statistics: " << matchStatistics << endl;
        cout << "==================================" << endl;
    }
};

#endif
