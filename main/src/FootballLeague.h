#ifndef FOOTBALLLEAGUE_H
#define FOOTBALLLEAGUE_H

#include <string>

#include "Date.h"
#include "Fixture.h"
#include "FootballTeam.h"

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

    public:
        // Default Constructor
        FootballLeague() {
            leagueID = 0;
            leagueName = "";
            season = "";
            numberOfTeams = 0;
            currentStatus = "";
        }

        // Parameterized Constructor
        FootballLeague(int leagueID, string leagueName, string season,
                       Date startDate, Date endDate,
                       int numberOfTeams, string currentStatus) {
            this->leagueID = leagueID;
            this->leagueName = leagueName;
            this->season = season;
            this->startDate = startDate;
            this->endDate = endDate;
            this->numberOfTeams = numberOfTeams;
            this->currentStatus = currentStatus;
        }

        // Getters
        int getLeagueID() {
            return leagueID;
        }

        string getLeagueName() {
            return leagueName;
        }

        string getSeason() {
            return season;
        }

        Date getStartDate() {
            return startDate;
        }

        Date getEndDate() {
            return endDate;
        }

        int getNumberOfTeams() {
            return numberOfTeams;
        }

        string getCurrentStatus() {
            return currentStatus;
        }

        // Setters
        void setLeagueID(int leagueID) {
            this->leagueID = leagueID;
        }

        void setLeagueName(string leagueName) {
            this->leagueName = leagueName;
        }

        void setSeason(string season) {
            this->season = season;
        }

        void setStartDate(Date startDate) {
            this->startDate = startDate;
        }

        void setEndDate(Date endDate) {
            this->endDate = endDate;
        }

        void setNumberOfTeams(int numberOfTeams) {
            this->numberOfTeams = numberOfTeams;
        }

        void setCurrentStatus(string currentStatus) {
            this->currentStatus = currentStatus;
        }

        bool scheduleFixture(Fixture proposed, FootballTeam& home, FootballTeam& away) {
            // Rule 3: Both teams must be registered to play.
            if (!home.canParticipate() || !away.canParticipate()) {
                return false;
            }

            const int homeID = home.getTeamID();
            const int awayID = away.getTeamID();

            for (const Fixture& existing : fixtures) {
                // Rule 4: Check whether either team already plays at this kickoff.
                const bool sameKickoff =
                    existing.getFixtureDate() == proposed.getFixtureDate() &&
                    existing.getFixtureTime() == proposed.getFixtureTime();

                const bool sharesTeam =
                    existing.getHomeTeamID() == homeID ||
                    existing.getAwayTeamID() == homeID ||
                    existing.getHomeTeamID() == awayID ||
                    existing.getAwayTeamID() == awayID;

                if (sameKickoff && sharesTeam) {
                    return false;
                }
            }

            // Save the fixture only after both rules pass.
            proposed.homeTeamID = homeID;
            proposed.awayTeamID = awayID;
            fixtures.push_back(proposed);
            return true;
        }

};

#endif // FOOTBALLLEAGUE_H
