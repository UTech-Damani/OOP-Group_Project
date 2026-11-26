#ifndef MATCHRESULTS_H
#define MATCHRESULTS_H

#include "../include/FootballTeam.h"
#include "../exceptions/InvalidScoreException.h"

#include <iostream>
#include <string>

using namespace std;

class MatchResult
{
private:
    int homeScore;
    int awayScore;
    string winner;
    string matchStatistics;

public:
    MatchResult()
    {
        homeScore = 0;
        awayScore = 0;
        winner = "";
        matchStatistics = "";
    }

    MatchResult(int homeScore, int awayScore,
                string winner, string matchStatistics)
    {
        setHomeScore(homeScore);
        setAwayScore(awayScore);

        this->winner = winner;
        this->matchStatistics = matchStatistics;
    }

    int getHomeScore() const
    {
        return homeScore;
    }

    int getAwayScore() const
    {
        return awayScore;
    }

    string getWinner() const
    {
        return winner;
    }

    string getMatchStatistics() const
    {
        return matchStatistics;
    }

    void setHomeScore(int score)
    {
        if (score < 0)
        {
            throw InvalidScoreException();
        }

        homeScore = score;
    }

    void setAwayScore(int score)
    {
        if (score < 0)
        {
            throw InvalidScoreException();
        }

        awayScore = score;
    }

    void setMatchStatistics(string statistics)
    {
        matchStatistics = statistics;
    }

    void determineWinner(FootballTeam& home,
                         FootballTeam& away)
    {
        if (homeScore > awayScore)
        {
            winner = home.getTeamName();

            home.updateLeaguePoints("win");
            away.updateLeaguePoints("loss");
        }
        else if (awayScore > homeScore)
        {
            winner = away.getTeamName();

            away.updateLeaguePoints("win");
            home.updateLeaguePoints("loss");
        }
        else
        {
            winner = "Draw";

            home.updateLeaguePoints("draw");
            away.updateLeaguePoints("draw");
        }

        home.addGoalsFor(homeScore);
        away.addGoalsFor(awayScore);

        home.addGoalsAgainst(awayScore);
        away.addGoalsAgainst(homeScore);

        home.calcGoalDifference();
        away.calcGoalDifference();
    }

    int getHomePoints() const
    {
        if (homeScore > awayScore)
            return 3;

        if (homeScore == awayScore)
            return 1;

        return 0;
    }

    int getAwayPoints() const
    {
        if (awayScore > homeScore)
            return 3;

        if (awayScore == homeScore)
            return 1;

        return 0;
    }

    bool validateScores() const
    {
        return homeScore >= 0 && awayScore >= 0;
    }

    void Display() const
    {
        cout << "\n========== MATCH RESULT ==========";
        cout << "\nHome Score: " << homeScore;
        cout << "\nAway Score: " << awayScore;
        cout << "\nWinner: " << winner;
        cout << "\nStatistics: " << matchStatistics;
        cout << "\n==================================\n";
    }
};

#endif