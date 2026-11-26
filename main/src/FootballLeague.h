#ifndef FOOTBALLLEAGUE_H
#define FOOTBALLLEAGUE_H

#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include "../exceptions/DuplicateRegistrationException.h"
#include "../exceptions/SchedulingConflictException.h"
#include "../exceptions/FixtureIncompleteException.h"

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
            teams.reserve(100);
            stadiums.reserve(100);
            fixtures.reserve(1000);
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
            teams.reserve(100);
            stadiums.reserve(100);
            fixtures.reserve(1000);
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

        vector<Stadium>& getStadiums() { return stadiums; }
        const vector<Stadium>& getStadiums() const { return stadiums; }

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
            for (const Stadium& existing : stadiums)
                if (existing.getStadiumID()==stadium.getStadiumID())
                    throw DuplicateRegistrationException();
            stadiums.push_back(stadium);
        }

        void addFootBallTeams(const FootballTeam& team){
            if (team.getTeamID() <= 0 || findTeam(team.getTeamID()))
                throw DuplicateRegistrationException();
            teams.push_back(team);
            teams.back().rebindMembers();
            numberOfTeams=static_cast<int>(teams.size());
        }

        void addFixtures(const Fixture& fixture){
            for (const Fixture& existing : fixtures)
                if (existing.getFixtureID()==fixture.getFixtureID())
                    throw DuplicateRegistrationException();
            fixtures.push_back(fixture);
        }

        void getStandings(){
            vector<FootballTeam*> ranked;
            for (FootballTeam& team : teams) ranked.push_back(&team);
            sort(ranked.begin(), ranked.end(), [](const FootballTeam* a, const FootballTeam* b) {
                if (a->getPoints()!=b->getPoints()) return a->getPoints()>b->getPoints();
                if (a->getGoalDifference()!=b->getGoalDifference()) return a->getGoalDifference()>b->getGoalDifference();
                return a->getGoalsFor()>b->getGoalsFor();
            });
            cout << "\nPOS  TEAM                     P  W  D  L  GF  GA  GD  PTS\n";
            int pos=1;
            for (const FootballTeam* t : ranked) {
                cout << left << setw(5) << pos++ << setw(25) << t->getTeamName()
                     << setw(3) << (t->getWins()+t->getDraws()+t->getLosses())
                     << setw(3) << t->getWins() << setw(3) << t->getDraws()
                     << setw(3) << t->getLosses() << setw(4) << t->getGoalsFor()
                     << setw(4) << t->getGoalsAgainst() << setw(4) << t->getGoalDifference()
                     << t->getPoints() << '\n';
            }
        }

        FootballTeam* findTeam(int id) {
            for (FootballTeam& team : teams) if (team.getTeamID()==id) return &team;
            return nullptr;
        }

        const FootballTeam* findTeam(int id) const {
            for (const FootballTeam& team : teams) if (team.getTeamID()==id) return &team;
            return nullptr;
        }

        bool updateTeam(int id, const string& name, const string& parish) {
            FootballTeam* team=findTeam(id);
            return team && team->updateTeamDetails(name, parish);
        }

        bool removeTeam(int id) {
            for (vector<FootballTeam>::iterator it=teams.begin(); it!=teams.end(); ++it)
                if (it->getTeamID()==id) {
                    for (const Fixture& f : fixtures)
                        if (f.getHomeTeamID()==id || f.getAwayTeamID()==id) return false;
                    teams.erase(it);
                    for (FootballTeam& remaining : teams) remaining.rebindMembers();
                    numberOfTeams=static_cast<int>(teams.size()); return true;
                }
            return false;
        }

        void recordFixtureResult(int fixtureID, const MatchResult& result) {
            for (Fixture& fixture : fixtures) {
                if (fixture.getFixtureID()!=fixtureID) continue;
                if (fixture.pointsAwarded()) throw FixtureIncompleteException();
                FootballTeam* home=findTeam(fixture.getHomeTeamID());
                FootballTeam* away=findTeam(fixture.getAwayTeamID());
                if (!home || !away) throw FixtureIncompleteException();
                if (fixture.hasResult() || fixture.pointsAwarded() ||
                    fixture.getFixtureStatus()=="Cancelled" ||
                    fixture.getFixtureStatus()=="Postponed" || !result.validateScores())
                    throw FixtureIncompleteException();
                MatchResult applied=result;
                applied.determineWinner(*home,*away);
                fixture.recordResults(applied);
                fixture.leaguePointsAwarded=true;
                return;
            }
            throw FixtureIncompleteException();
        }

        void createFixture(Fixture proposed, FootballTeam& home, FootballTeam& away) {
            // Rule 3: Both teams must be registered to play.
            if (!home.canParticipate() || !away.canParticipate()) {
                throw TeamNotEligibleException();
            }

            const int homeID = home.getTeamID();
            const int awayID = away.getTeamID();

            if (proposed.getStadiumID() <= 0)
                throw FixtureIncompleteException();
            bool stadiumFound = false;
            for (const Stadium& stadium : stadiums)
                if (stadium.getStadiumID() == proposed.getStadiumID()) stadiumFound = true;
            if (!stadiumFound) throw FixtureIncompleteException();

            if (homeID == awayID) {
                throw TeamNotEligibleException();
            }
            if (proposed.getFixtureID() <= 0)
                throw FixtureIncompleteException();
            for (const Fixture& existing : fixtures)
                if (existing.getFixtureID() == proposed.getFixtureID())
                    throw DuplicateRegistrationException();

            for (const Fixture& existing : fixtures) {
                if (existing.getFixtureStatus() == "Cancelled" ||
                    existing.getFixtureStatus() == "Postponed") continue;
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
                    throw SchedulingConflictException();
                }
                if (sameKickoff && proposed.getStadiumID() > 0 &&
                    existing.getStadiumID() == proposed.getStadiumID()) {
                    throw SchedulingConflictException();
                }
            }

            if (findTeam(homeID)==nullptr || findTeam(awayID)==nullptr)
                throw TeamNotEligibleException();

            // Save the fixture only after both rules pass.
            proposed.homeTeamID = homeID;
            proposed.awayTeamID = awayID;
            fixtures.push_back(proposed);
            for (Stadium& stadium : stadiums) {
                if (stadium.getStadiumID() == proposed.getStadiumID()) {
                    fixtures.back().setStadium(&stadium);
                    stadium.addFixture(&fixtures.back());
                    break;
                }
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

        void registerTeam(FootballTeam& NewTeam)
        {
            if (NewTeam.getTeamID() <= 0 || NewTeam.getTeamName().empty())
                throw TeamNotEligibleException();
            for (FootballTeam& existing : teams)
            {
                if (existing.getTeamID() == NewTeam.getTeamID())
                {
                    throw DuplicateRegistrationException();
                }
            }

            NewTeam.setTeamStatus("registered");
            teams.push_back(NewTeam);
            teams.back().rebindMembers();
            numberOfTeams = static_cast<int>(teams.size());

            cout << "\nTeam Registered Successfully!\n";
        }

};

#endif
