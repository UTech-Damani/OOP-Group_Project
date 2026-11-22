#ifndef FIXTURE_H
#define FIXTURE_H
#include "Stadium.h"
#include "MatchResults.h"
#include "../include/MatchOfficial.h"
#include "../universal/Date.h"
#include "../universal/ProjectTime.h"
#include "../exceptions/FixtureIncompleteException.h"

#include <string>
#include <iomanip>
#include <vector>

using namespace std;

class Fixture
{
    private:
        int fixtureID;
        Date fixtureDate;
        ProjectTime fixtureTime;
        string fixtureStatus;
        int attendance; // Number of persons attending

        // Rule 4: Store IDs so the league can check both team positions.
        // Zero means a team has not been assigned yet.
        int homeTeamID = 0;
        int awayTeamID = 0;

        // Stop the same result from awarding points twice.
        bool leaguePointsAwarded = false;

        // Let FootballLeague assign teams after its checks pass.
        friend class FootballLeague;

        Stadium* stadium;
        MatchResult result;
        vector<MatchOfficial*> officials;

    public:
        // Constructors
        Fixture(){
            
            fixtureID = 0;
            fixtureDate.setDay(0);
            fixtureDate.setMonth(0);
            fixtureDate.setYear(0);

            fixtureTime.setHours(0);
            fixtureTime.setMinutes(0);
            fixtureTime.setSeconds(0);

            fixtureStatus = "No schedule at this moment";
            attendance = 0;

            stadium = nullptr;
        }
        Fixture(int day, int month, int year, int hours, int minutes, int seconds, string Status, int attendance,
                Stadium &stadium){
            this->stadium = &stadium;

            setFixtureDate(day, month, year);
            setFixtureTime(hours, minutes, seconds);
            fixtureStatus = Status;
            this->attendance = attendance;
        }

        // Setters
        void setFixtureID(int id) {
            fixtureID = id;
        }

        void setFixtureDate(int day, int month, int year) {
            fixtureDate.setDay(day);
            fixtureDate.setMonth(month);
            fixtureDate.setYear(year);
        }

        void setFixtureTime(int hours, int minutes, int seconds) {
            fixtureTime.setHours(hours);
            fixtureTime.setMinutes(minutes);
            fixtureTime.setSeconds(seconds);
        }

        void setFixtureStatus(string status) {
            if(status != "Scheduled" &&
                status != "In progress" &&
                status != "Half Time" &&
                status != "Full Time" &&
                status != "Postponed" &&
                status != "Cancelled")
            {
                cout << "Invalid Status" << endl;
            }
            fixtureStatus = status;
        }

        void setAttendance(int attend) {
            if(attend <= 0){

            }
            attendance = attend;
        }

        // Getters

        int getFixtureID() const {
            return fixtureID;
        }

        void getFixtureDate() {
            fixtureDate.displayDate();
        }

        Date getFixtureDateMember() const{
            return fixtureDate;
        }

        void getFixtureTime() const {
            fixtureTime.displayTime();
        }

        ProjectTime getFixtureTimeMember() const {
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

        bool conflictsWith(const Fixture& other) const{
            if (fixtureStatus == "Cancelled" || other.fixtureStatus == "Cancelled")
            {
                return false;
            }

            bool sameDate =
                fixtureDate.getDay() == other.fixtureDate.getDay() &&
                fixtureDate.getMonth() == other.fixtureDate.getMonth() &&
                fixtureDate.getYear() == other.fixtureDate.getYear();

            bool sameTime =
                fixtureTime.getHours() == other.fixtureTime.getHours() &&
                fixtureTime.getMinutes() == other.fixtureTime.getMinutes();

            return sameDate && sameTime;

        }

        void addOfficial(MatchOfficial* o){
            officials.push_back(o);
        }
        void recordResults(const MatchResult& matchResult){
            if (fixtureStatus == "Cancelled"){
                cout << "Cannot record results for a cancelled fixture.\n";
                return;
            }

            result = matchResult;
            fixtureStatus = "Full Time";
        }
        void completeFixture(){
            if(officials.empty())
            {
                throw FixtureIncompleteException();
            }
            if (fixtureStatus == "Cancelled"){
                cout << "Cancelled fixtures cannot be completed.\n";
                return;
            }

            if (fixtureStatus == "Postponed"){
                cout << "Postponed fixtures must be rescheduled first.\n";
                return;
            }

            fixtureStatus = "Full Time";
        }
        void postpone(){
            if (fixtureStatus == "Full Time"){
                cout << "Completed fixtures cannot be postponed.\n";
                return;
            }

            if (fixtureStatus == "Cancelled"){
                cout << "Cancelled fixtures cannot be postponed.\n";
                return;
            }

            fixtureStatus = "Postponed";
        }
};

#endif // FIXTURE_H
