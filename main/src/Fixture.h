#ifndef FIXTURE_H
#define FIXTURE_H
#include "Stadium.h"
#include "MatchResults.h"
#include "MatchOfficial.h"

#include <string>
#include <iomanip>
#include <vector>

using namespace std;

class Fixture
{
    private:
        int fixtureID;
        string fixtureDate;
        string fixtureTime;
        string fixtureStatus;
        int attendance;

        // Rule 4: Store IDs so the league can check both team positions.
        // Zero means a team has not been assigned yet.
        int homeTeamID = 0;
        int awayTeamID = 0;

        // Stop the same result from awarding points twice.
        bool leaguePointsAwarded = false;

        // Let FootballLeague assign teams after its checks pass.
        friend class FootballLeague;

        Stadium stadium;
        MatchResult result;
        vector<MatchOfficial> officials;

    public:
        // Constructors
        Fixture(){
            fixtureID = 0;
            fixtureDate = "";
            fixtureTime = "";
            fixtureStatus = "";
            attendance = 0;
        }
        Fixture(int ID, string Date, string Time, string Status, int attendance){
            fixtureID = ID;
            fixtureDate = Date;
            fixtureTime = Time;
            fixtureStatus = Status;
            this->attendance = attendance;
        }

        // Setters
        void setFixtureID(int id) {
            fixtureID = id;
        }

        void setFixtureDate(string date) {
            fixtureDate = date;
        }

        void setFixtureTime(string time) {
            fixtureTime = time;
        }

        void setFixtureStatus(string status) {
            fixtureStatus = status;
        }

        void setAttendance(int attend) {
            attendance = attend;
        }

        // Getters

        int getFixtureID() const {
            return fixtureID;
        }

        string getFixtureDate() const {
            return fixtureDate;
        }

        string getFixtureTime() const {
            return fixtureTime;
        }

        string getFixtureStatus() const {
            return fixtureStatus;
        }

        int getAttendance() const {
            return attendance;
        }

        int getHomeTeamID() const {
            return homeTeamID;
        }

        int getAwayTeamID() const {
            return awayTeamID;
        }

        void conflictsWith(){

        }
        void addOfficial(const MatchOfficial& o){
            officials.push_back(o);
        }
        void recordResults(){

        }
        void completeFixture(){

        }
        void postpone(){
            
        }
};

#endif // FIXTURE_H
