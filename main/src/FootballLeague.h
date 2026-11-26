#ifndef FOOTBALLLEAGUE_H
#define FOOTBALLLEAGUE_H

#include <string>
#include <vector>
#include <iomanip>
#include <iostream>
#include <algorithm>

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

    int leagueID;
    string leagueName;
    string season;

    Date startDate;
    Date endDate;

    int numberOfTeams;
    string currentStatus;

    const int minimumAge = 16;

    vector<Fixture> fixtures;
    vector<Stadium> stadiums;
    vector<FootballTeam> teams;

public:

    FootballLeague()
    {
        leagueID = 0;
        leagueName = "";
        season = "";
        numberOfTeams = 0;
        currentStatus = "";
    }

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

    // GETTERS

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

    // SETTERS

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
        }

        newTeam.setTeamStatus("registered");

        teams.push_back(newTeam);

        numberOfTeams = static_cast<int>(teams.size());

        cout << "\nTeam registered successfully!\n";
    }

    // CHECK PLAYER AGE

    bool meetsMinimumAge(const Player& player) const
    {
        return player.getAge() >= minimumAge;
    }

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

    void createFixture(Fixture proposed,
                       FootballTeam& home,
                       FootballTeam& away)
    {
        if (!home.canParticipate() ||
            !away.canParticipate())
        {
            throw TeamNotEligibleException();
        }

        if (home.getTeamID() == away.getTeamID())
        {
            throw TeamNotEligibleException();
        }

        if (findTeam(home.getTeamID()) == nullptr ||
            findTeam(away.getTeamID()) == nullptr)
        {
            throw TeamNotEligibleException();
        }

        for (const Fixture& existing : fixtures)
        {
            if (existing.conflictsWith(proposed))
            {
                bool sameTeam =
                    existing.getHomeTeamID() == home.getTeamID() ||
                    existing.getAwayTeamID() == home.getTeamID() ||
                    existing.getHomeTeamID() == away.getTeamID() ||
                    existing.getAwayTeamID() == away.getTeamID();

                if (sameTeam)
                {
                    throw SchedulingConflictException();
                }
            }
        }

        proposed.homeTeamID = home.getTeamID();
        proposed.awayTeamID = away.getTeamID();

        fixtures.push_back(proposed);
    }

    // RECORD RESULT AND UPDATE STANDINGS

    void recordFixtureResult(int fixtureID,
                             const MatchResult& matchResult)
    {
        Fixture* selectedFixture = nullptr;

        for (Fixture& fixture : fixtures)
        {
            if (fixture.getFixtureID() == fixtureID)
            {
                selectedFixture = &fixture;
                break;
            }
        }

        if (selectedFixture == nullptr)
        {
            throw FixtureIncompleteException();
        }

        if (selectedFixture->hasAwardedPoints())
        {
            throw FixtureIncompleteException();
        }

        FootballTeam* home =
            findTeam(selectedFixture->getHomeTeamID());

        FootballTeam* away =
            findTeam(selectedFixture->getAwayTeamID());

        if (home == nullptr || away == nullptr)
        {
            throw FixtureIncompleteException();
        }

        selectedFixture->recordResults(matchResult);

        MatchResult storedResult = selectedFixture->getResult();

        storedResult.determineWinner(*home, *away);

        selectedFixture->leaguePointsAwarded = true;
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
        vector<FootballTeam*> rankedTeams;

        for (FootballTeam& team : teams)
        {
            rankedTeams.push_back(&team);
        }

        sort(rankedTeams.begin(), rankedTeams.end(),
             [](FootballTeam* a, FootballTeam* b)
             {
                 if (a->getPoints() != b->getPoints())
                     return a->getPoints() > b->getPoints();

                 if (a->getGoalDifference() != b->getGoalDifference())
                     return a->getGoalDifference() > b->getGoalDifference();

                 return a->getGoalsFor() > b->getGoalsFor();
             });

        cout << "\n============================================================\n";
        cout << "                    FOOTBALL LEAGUE STANDINGS\n";
        cout << "============================================================\n";

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

        cout << "------------------------------------------------------------\n";

        int position = 1;

        for (FootballTeam* team : rankedTeams)
        {
            int played =
                team->getWins() +
                team->getDraws() +
                team->getLosses();

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

        cout << "============================================================\n";
    }
};

#endif