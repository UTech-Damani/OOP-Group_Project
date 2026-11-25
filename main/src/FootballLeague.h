#ifndef FOOTBALLLEAGUE_H
#define FOOTBALLLEAGUE_H

#include <string>
#include <vector>
#include <iomanip>

#include "../universal/Date.h"
#include "Fixture.h"
#include "../include/FootballTeam.h"
#include "Stadium.h"
#include "../exceptions/TeamNotEligibleException.h"

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

        vector <Fixture> fixtures;
        vector <Stadium> stadiums;
        vector <FootballTeam> teams;

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

        int getNumberOfTeams() const {
            return numberOfTeams;
        }

        string getCurrentStatus() const {
            return currentStatus;
        }

        int getMinimumAge() const {
            return minimumAge;
        }

        vector<Fixture>& getFixtures() {
            return fixtures;
        }

        const vector<Fixture>& getFixtures() const {
            return fixtures;
        }

        vector<Stadium> getStadiums() const {
            return stadiums;
        }

        const vector<FootballTeam>& getTeams() const {
            return teams;
        }
        vector<FootballTeam>& getTeams() {
            return teams;
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

        //Worker Functions

        void addStadiums(const Stadium& stadium){
            stadiums.push_back(stadium);
        }

        void addFootBallTeams(const FootballTeam& team){
            teams.push_back(team);
        }

        void addFixtures(const Fixture& fixture){
            fixtures.push_back(fixture);
        }

        void getStandings(){
            cout << "\n";
            cout << "============================================================\n";
            cout << "                 FOOTBALL LEAGUE                            \n";
            cout << "                    STANDINGS                               \n";
            cout << "============================================================\n";

            cout << "------------------------------------------------------------\n";
            cout << left
                << setw(5)  << "POS"
                << setw(25) << "TEAM"
                << setw(5)  << "P"
                << setw(5)  << "W"
                << setw(5)  << "D"
                << setw(5)  << "L"
                << setw(7)  << "GF"
                << setw(7)  << "GA"
                << setw(7)  << "GD"
                << setw(5)  << "PTS" << endl;

            cout << "------------------------------------------------------------\n";

            // Display standings here
            for (FootballTeam& team : teams){
                cout << left
                     << setw(5)  << 1
                     << setw(25) << team.getTeamName()
                     << setw(5)  << 1
                     << setw(5)  << team.getWins()
                     << setw(5)  << team.getDraws()
                     << setw(5)  << team.getLosses()
                     << setw(7)  << team.getGoalsFor()
                     << setw(7)  << team.getGoalsAgainst()
                     << setw(7)  << team.getGoalDifference()
                     << setw(5)  << team.getPoints()
                     << endl;

            }
            cout << "============================================================\n";
            cout << " P = Played | W = Won | D = Drawn | L = Lost\n";
            cout << " GF = Goals For | GA = Goals Against | GD = Goal Difference\n";
            cout << "============================================================\n";
        }

        void createFixture(Fixture proposed, FootballTeam& home, FootballTeam& away) {
            // Rule 3: Both teams must be registered to play.
            if (!home.canParticipate() || !away.canParticipate()) {
                throw TeamNotEligibleException();
            }

            const int homeID = home.getTeamID();
            const int awayID = away.getTeamID();

            if (homeID == awayID) {
                throw TeamNotEligibleException();
            }

            for (const Fixture& existing : fixtures) {
                // Rule 4: Check whether either team already plays at this kickoff.
                const bool sameKickoff =
                    existing.getFixtureDateMember().getDay() == proposed.getFixtureDateMember().getDay() &&
                    existing.getFixtureDateMember().getMonth() == proposed.getFixtureDateMember().getMonth() &&
                    existing.getFixtureDateMember().getYear() == proposed.getFixtureDateMember().getYear() &&

                    existing.getFixtureTimeMember().getHours() == proposed.getFixtureTimeMember().getHours() &&
                    existing.getFixtureTimeMember().getMinutes() == proposed.getFixtureTimeMember().getMinutes() &&
                    existing.getFixtureTimeMember().getSeconds() == proposed.getFixtureTimeMember().getSeconds();

                const bool sharesTeam =
                    existing.getHomeTeamID() == homeID ||
                    existing.getAwayTeamID() == homeID ||
                    existing.getHomeTeamID() == awayID ||
                    existing.getAwayTeamID() == awayID;

                if (sameKickoff && sharesTeam) {
                    throw TeamNotEligibleException();
                }
            }

            // Save the fixture only after both rules pass.
            proposed.homeTeamID = homeID;
            proposed.awayTeamID = awayID;
            fixtures.push_back(proposed);
            
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

        void registerTeam(FootballTeam& NewTeam)
        {
            for (FootballTeam& existing : teams)
            {
                if (existing.getTeamID() == NewTeam.getTeamID())
                {
                    throw DuplicateRegistrationException();
                }
            }

            NewTeam.setTeamStatus("registered");
            teams.push_back(NewTeam);

            cout << "\nTeam Registered Successfully!\n";
        }

};

#endif
