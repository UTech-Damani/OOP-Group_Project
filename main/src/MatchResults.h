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
    // Stores the number of goals scored by the home team.
    int homeScore;

    // Stores the number of goals scored by the away team.
    int awayScore;

    // Stores the name of the winning team or "Draw".
    string winner;

    // Stores additional statistics or information about the match.
    string matchStatistics;

public:

    // Default constructor
    MatchResult()
    {
        homeScore = 0;
        awayScore = 0;
        winner = "";
        matchStatistics = "";
    }

    // Parameterized constructor
    MatchResult(int homeScore, int awayScore,
                string winner, string matchStatistics)
    {
        setHomeScore(homeScore);
        setAwayScore(awayScore);

        this->winner = winner;
        this->matchStatistics = matchStatistics;
    }

    // ================= GETTERS =================

    // Returns the number of goals scored by the home team.
    int getHomeScore() const
    {
        return homeScore;
    }

    // Returns the number of goals scored by the away team.
    int getAwayScore() const
    {
        return awayScore;
    }

    // Returns the name of the winning team or "Draw".
    string getWinner() const
    {
        return winner;
    }

    // Returns the additional match statistics.
    string getMatchStatistics() const
    {
        return matchStatistics;
    }

    // ================= SETTERS =================

    // Sets the home team's score.
    void setHomeScore(int score)
    {
        if (score < 0)
        {
            throw InvalidScoreException();
        }

        homeScore = score;
    }

    // Sets the away team's score.
    void setAwayScore(int score)
    {
        if (score < 0)
        {
            throw InvalidScoreException();
        }

        awayScore = score;
    }

    // Sets the additional statistics recorded for the match.
    void setMatchStatistics(string statistics)
    {
        matchStatistics = statistics;
    }

    // Determines the winner based on the scores and updates both teams league points, goals scored, goals conceded and goal difference.
    void determineWinner(FootballTeam& home,
                         FootballTeam& away)
    {
        // Checks whether the home team scored more goals.
        if (homeScore > awayScore)
        {
            winner = home.getTeamName();

            home.updateLeaguePoints("win");
            away.updateLeaguePoints("loss");
        }
        // Checks whether the away team scored more goals.
        else if (awayScore > homeScore)
        {
            winner = away.getTeamName();

            away.updateLeaguePoints("win");
            home.updateLeaguePoints("loss");
        }
        // If both teams have the same score, the match is a draw.
        else
        {
            winner = "Draw";

            home.updateLeaguePoints("draw");
            away.updateLeaguePoints("draw");
        }

        // Updates the goals scored by each team.
        home.addGoalsFor(homeScore);
        away.addGoalsFor(awayScore);

        // Updates the goals conceded by each team.
        home.addGoalsAgainst(awayScore);
        away.addGoalsAgainst(homeScore);

        // Recalculates the goal difference for both teams.
        home.calcGoalDifference();
        away.calcGoalDifference();
    }

    // Returns the number of league points earned by the home team.
    int getHomePoints() const
    {
        if (homeScore > awayScore)
            return 3;

        if (homeScore == awayScore)
            return 1;

        return 0;
    }

    // Returns the number of league points earned by the away team.
    int getAwayPoints() const
    {
        if (awayScore > homeScore)
            return 3;

        if (awayScore == homeScore)
            return 1;

        return 0;
    }

    // Checks whether both team scores are valid (non-negative).
    bool validateScores() const
    {
        return homeScore >= 0 && awayScore >= 0;
    }

    // Displays the match result and its recorded statistics.
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