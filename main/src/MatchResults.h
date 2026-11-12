#ifndef MATCHRESULTS_H
#define MATCHRESULTS_H


#include <iostream>
#include <string>

using namespace std;

class MatchResult {
    private:
        int homeScore;
        int awayScore;
        string winner;
        string matchStatistics;

    public:
        // Default Constructor
        MatchResult() {
            homeScore = 0;
            awayScore = 0;
            winner = "";
            matchStatistics = "";
        }

        // Parameterized Constructor
        MatchResult(int homeScore, int awayScore,
                    string winner, string matchStatistics) {
            this->homeScore = homeScore;
            this->awayScore = awayScore;
            this->winner = winner;
            this->matchStatistics = matchStatistics;
        }

        // Getters
        int getHomeScore() {
            return homeScore;
        }

        int getAwayScore() {
            return awayScore;
        }

        string getWinner() {
            return winner;
        }

        string getMatchStatistics() {
            return matchStatistics;
        }

        // Setters
        void setHomeScore(int homeScore) {
            this->homeScore = homeScore;
        }

        void setAwayScore(int awayScore) {
            this->awayScore = awayScore;
        }

        void setWinner(string winner) {
            this->winner = winner;
        }

        void setMatchStatistics(string matchStatistics) {
            this->matchStatistics = matchStatistics;
        }

        // Display Method
        void Display() {
            cout << "\n=== Match Result ===" << endl;
            cout << "Home Score: " << homeScore << endl;
            cout << "Away Score: " << awayScore << endl;
            cout << "Winner: " << winner << endl;
            cout << "Statistics: " << matchStatistics << endl;
        }
};
#endif // MATCHRESULTS_H
