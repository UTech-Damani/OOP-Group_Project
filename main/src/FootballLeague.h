#ifndef FOOTBALLLEAGUE_H
#define FOOTBALLLEAGUE_H

#include <string>
#include <vector> // Provides the vector container for storing dynamic collections.
#include <iomanip> // Provides formatting tools such as setw() and methods for aligning data.
#include <iostream>
#include <algorithm> // Provides standard algorithms such as sort() for arranging teams in the league standings.

#include "../universal/Date.h"

#include "Fixture.h"
#include "MatchResults.h"
#include "Stadium.h"

#include "../include/FootballTeam.h"

#include "../exceptions/TeamNotEligibleException.h"
#include "../exceptions/DuplicateRegistrationException.h"
#include "../exceptions/SchedulingConflictException.h"
#include "../exceptions/FixtureIncompleteException.h"

using namespace std;

class FootballLeague
{
private:

    // Stores the league's identification and general information
    int leagueID;
    string leagueName;
    string season;

    // Defines the starting and ending dates of the league season
    Date startDate;
    Date endDate;

    // Tracks the number of registered teams and the league's current status
    int numberOfTeams;
    string currentStatus;

    // Establishes the minimum age required for players to participate
    const int minimumAge = 16;

    // Stores the fixtures, stadiums and football teams managed by the league
    vector<Fixture> fixtures;
    vector<Stadium> stadiums;
    vector<FootballTeam> teams;

public:

    // Default Constructor
    FootballLeague()
    {
        leagueID = 0;
        leagueName = "";
        season = "";
        numberOfTeams = 0;
        currentStatus = "";
    }

    // Parameterized Constructor
    FootballLeague(int leagueID, string leagueName,
                   string season, Date startDate,
                   Date endDate, int numberOfTeams,
                   string currentStatus)
    {
        this->leagueID = leagueID;
        this->leagueName = leagueName;
        this->season = season;
        this->startDate = startDate;
        this->endDate = endDate;
        this->numberOfTeams = numberOfTeams;
        this->currentStatus = currentStatus;
    }

    // ================= GETTERS =================

    // Retrieve the league's stored information

    int getLeagueID() const
    {
        return leagueID;
    }

    string getLeagueName() const
    {
        return leagueName;
    }

    string getSeason() const
    {
        return season;
    }

    Date getStartDate() const
    {
        return startDate;
    }

    Date getEndDate() const
    {
        return endDate;
    }

    int getNumberOfTeams() const
    {
        return numberOfTeams;
    }

    string getCurrentStatus() const
    {
        return currentStatus;
    }

    int getMinimumAge() const
    {
        return minimumAge;
    }

    // Returns references to the league's collections
    vector<Fixture>& getFixtures()
    {
        return fixtures;
    }

    const vector<Fixture>& getFixtures() const
    {
        return fixtures;
    }

    vector<Stadium>& getStadiums()
    {
        return stadiums;
    }

    const vector<Stadium>& getStadiums() const
    {
        return stadiums;
    }

    vector<FootballTeam>& getTeams()
    {
        return teams;
    }

    const vector<FootballTeam>& getTeams() const
    {
        return teams;
    }

    // ================= SETTERS =================
    
    // Update the league's stored information

    void setLeagueID(int id)
    {
        leagueID = id;
    }

    void setLeagueName(string name)
    {
        leagueName = name;
    }

    void setSeason(string season)
    {
        this->season = season;
    }

    void setStartDate(Date date)
    {
        startDate = date;
    }

    void setEndDate(Date date)
    {
        endDate = date;
    }

    void setNumberOfTeams(int number)
    {
        if (number >= 0)
            numberOfTeams = number;
    }

    void setCurrentStatus(string status)
    {
        currentStatus = status;
    }

    // ADD STADIUM
    void addStadiums(const Stadium& stadium)
    {
        for (const Stadium& existing : stadiums)
        {
            if (existing.getStadiumID() == stadium.getStadiumID())
            {
                throw DuplicateRegistrationException();
            }
        }

        stadiums.push_back(stadium);
    }

    // ADD TEAM
    void addFootBallTeams(const FootballTeam& team)
    {
        // 
        teams.push_back(team);
    }

    // ADD FIXTURE
    void addFixtures(const Fixture& fixture)
    {
        fixtures.push_back(fixture);
    }

    // REGISTER TEAM
    void registerTeam(FootballTeam& newTeam)
    {
        for (FootballTeam& existing : teams)
        {
            if (existing.getTeamID() == newTeam.getTeamID())
            {
                throw DuplicateRegistrationException();
            }
            if (existing.getTeamName() == newTeam.getTeamName())
            {
                throw DuplicateRegistrationException();
            }
        }

        // Updates the team's registration status
        newTeam.setTeamStatus("registered");

        // Adds the registered team to the league
        teams.push_back(newTeam);

        // Synchronizes the team count with the collection size
        numberOfTeams = static_cast<int>(teams.size());

        cout << "\nTeam registered successfully!\n";
    }

    // CHECK PLAYER AGE
    bool meetsMinimumAge(const Player& player) const
    {
        return player.getAge() >= minimumAge;
    }

    // Checks whether a player meets the age requirement for registration
    bool registerPlayer(const Player& player) const
    {
        return meetsMinimumAge(player);
    }

    // FIND TEAM
    FootballTeam* findTeam(int teamID)
    {
        for (FootballTeam& team : teams)
        {
            if (team.getTeamID() == teamID)
            {
                return &team;
            }
        }

        return nullptr;
    }

    // CREATE FIXTURE
    void createFixture(Fixture proposed, FootballTeam& home, FootballTeam& away)
    {
        // Ensure both teams are eligible to participate
        if (!home.canParticipate() ||
            !away.canParticipate())
        {
            throw TeamNotEligibleException();
        }

        // Prevent a team from playing against itself
        if (home.getTeamID() == away.getTeamID())
        {
            throw TeamNotEligibleException();
        }

        // Ensure both teams are registered in this league
        if (findTeam(home.getTeamID()) == nullptr || findTeam(away.getTeamID()) == nullptr)
        {
            throw TeamNotEligibleException();
        }

        // Check existing fixtures for scheduling conflicts
        for (const Fixture& existing : fixtures)
        {
            if (existing.conflictsWith(proposed))
            {
                bool sameTeam = existing.getHomeTeamID() == home.getTeamID() || existing.getAwayTeamID() == home.getTeamID() ||
                    existing.getHomeTeamID() == away.getTeamID() || existing.getAwayTeamID() == away.getTeamID();

                if (sameTeam)
                {
                    throw SchedulingConflictException();
                }
            }
        }

        // Assign the participating teams to the proposed fixture
        proposed.homeTeamID = home.getTeamID();
        proposed.awayTeamID = away.getTeamID();

        // Store the fixture in the league
        fixtures.push_back(proposed);
    }

    // RECORD RESULT AND UPDATE STANDINGS
    void recordFixtureResult(int fixtureID, const MatchResult& matchResult)
    {
        Fixture* selectedFixture = nullptr;

        // Find the fixture using its unique ID
        for (Fixture& fixture : fixtures)
        {
            if (fixture.getFixtureID() == fixtureID)
            {
                selectedFixture = &fixture;
                break;
            }
        }

        // Ensure the requested fixture exists
        if (selectedFixture == nullptr)
        {
            throw FixtureIncompleteException();
        }

        // Prevent league points from being awarded more than once
        if (selectedFixture->hasAwardedPoints())
        {
            throw FixtureIncompleteException();
        }

        // Validate the submitted match scores
        if (!matchResult.validateScores())
        {
            throw FixtureIncompleteException();
        }

        // Retrieve the actual teams participating in the fixture
        FootballTeam* home = findTeam(selectedFixture->getHomeTeamID());

        FootballTeam* away = findTeam(selectedFixture->getAwayTeamID());

        // Ensure both participating teams exist
        if (home == nullptr || away == nullptr)
        {
            throw FixtureIncompleteException();
        }

        // Determine the winner and update the teams' statistics
        MatchResult appliedResult = matchResult;

        appliedResult.determineWinner(*home, *away);

        // Store the finalized result in the fixture
        selectedFixture->recordResults(appliedResult);

        // Mark the fixture to prevent duplicate awarding of league points
        selectedFixture->leaguePointsAwarded = true;

        cout << "\nMatch result recorded successfully!\n";

        // Display the updated league standings
        cout << "\n========== UPDATED LEAGUE STANDINGS ==========\n";

        getStandings();
    }

    // DISPLAY FIXTURES
    void displayFixtures() const
    {
        if (fixtures.empty())
        {
            cout << "\nNo fixtures available.\n";
            return;
        }

        for (const Fixture& fixture : fixtures)
        {
            fixture.Display();
        }
    }

    // DISPLAY TEAMS
    void displayTeams()
    {
        if (teams.empty())
        {
            cout << "\nNo teams registered.\n";
            return;
        }

        for (FootballTeam& team : teams)
        {
            cout << "\nTeam ID: " << team.getTeamID();
            cout << "\nTeam Name: " << team.getTeamName();
            cout << "\nStatus: " << team.getTeamStatus();
            cout << "\nPoints: " << team.getPoints();
            cout << "\n";
        }
    }

    // LEAGUE STANDINGS
    void getStandings()
    {
        // Store pointers to the teams for ranking without changing their original order
        vector<FootballTeam*> rankedTeams;

        for (FootballTeam& team : teams)
        {
            rankedTeams.push_back(&team);
        }

        // Sort teams using the league's ranking rules
        sort(rankedTeams.begin(), rankedTeams.end(),
             [](FootballTeam* a, FootballTeam* b)
             {
                 if (a->getPoints() != b->getPoints())
                     return a->getPoints() > b->getPoints();

                 if (a->getGoalDifference() != b->getGoalDifference())
                     return a->getGoalDifference() > b->getGoalDifference();

                 return a->getGoalsFor() > b->getGoalsFor();
             });

        // Display the standings table headings
        cout << "\n===========================================================================================\n";
        cout << "                    FOOTBALL LEAGUE STANDINGS\n";
        cout << "==============================================================================================\n";

        cout << left
             << setw(5) << "POS"
             << setw(25) << "TEAM"
             << setw(5) << "P"
             << setw(5) << "W"
             << setw(5) << "D"
             << setw(5) << "L"
             << setw(7) << "GF"
             << setw(7) << "GA"
             << setw(7) << "GD"
             << setw(5) << "PTS"
             << endl;

        cout << "---------------------------------------------------------------------------------------------------\n";

        // Display each team according to its calculated position
        int position = 1;

        for (FootballTeam* team : rankedTeams)
        {
            // Calculate the total number of matches played
            int played = team->getWins() + team->getDraws() + team->getLosses();

            cout << left
                 << setw(5) << position++
                 << setw(25) << team->getTeamName()
                 << setw(5) << played
                 << setw(5) << team->getWins()
                 << setw(5) << team->getDraws()
                 << setw(5) << team->getLosses()
                 << setw(7) << team->getGoalsFor()
                 << setw(7) << team->getGoalsAgainst()
                 << setw(7) << team->getGoalDifference()
                 << setw(5) << team->getPoints()
                 << endl;
        }

        cout << "===================================================================================================\n";
    }
};

#endif // FOOTBALLLEAGUE_H