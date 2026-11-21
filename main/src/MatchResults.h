#ifndef MATCHRESULTS_H
#define MATCHRESULTS_H
#include <string>

class MatchResults {
    int homeScore = 0;
    int awayScore = 0;
    std::string winner;
    std::string matchStatistics;

    void updateWinner() {
        if (homeScore > awayScore) {
            winner = "Home";
        } else if (awayScore > homeScore) {
            winner = "Away";
        } else {
            winner = "Draw";
        }
    }

public:
    MatchResults() = default;

    MatchResults(int home, int away, const std::string& stats = "")
        : homeScore(0), awayScore(0), matchStatistics(stats) {
        setHomeScore(home);
        setAwayScore(away);
        updateWinner();
    }

    // Getters
    int getHomeScore() const{
        return homeScore;
    }
    int getAwayScore() const{
        return awayScore;
    }
    std::string getWinner() const{
        return winner;
    }
    std::string getMatchStatistics() const{
        return matchStatistics;
    }

    bool setHomeScore(int score) {
        if (score < 0) {
            return false; 
        }
        homeScore = score;
        updateWinner();
        return true;
    }

    bool setAwayScore(int score) {
        if (score < 0) {
            return false; 
        }
        awayScore = score;
        updateWinner();
        return true;
    }

    void setWinner(const std::string& w) {
        winner = w;
    }

    void setMatchStatistics(const std::string& stats) {
        matchStatistics = stats;
    }
};

#endif