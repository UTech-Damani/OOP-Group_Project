#ifndef FIXTURE_H
#define FIXTURE_H
#include "Stadium.h"
#include "MatchResults.h"
#include "../include/MatchOfficial.h"
#include "../universal/Date.h"
#include "../universal/ProjectTime.h"
#include "../exceptions/FixtureIncompleteException.h"
#include "../exceptions/SchedulingConflictException.h"
#include "../universal/FileManager.h"

#include <string>
#include <iomanip>
#include <vector>
#include <sstream>

using namespace std;

class Fixture : public Persistable
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
        bool resultRecorded = false;
        int stadiumID = 0;

        // Let FootballLeague assign teams after its checks pass.
        friend class FootballLeague;

        Stadium* stadium;
        MatchResult result;
        vector<MatchOfficial*> officials;
        vector<int> officialIDs;

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
            stadiumID = 0;
            resultRecorded = false;
            leaguePointsAwarded = false;
        }
        Fixture(int day, int month, int year, int hours, int minutes, int seconds, string Status, int attendance,
                Stadium &stadium){
            this->stadium = &stadium;
            this->stadiumID = stadium.getStadiumID();
            resultRecorded = false;
            leaguePointsAwarded = false;
            homeTeamID = 0;
            awayTeamID = 0;

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
            if(status != "Scheduled" && status != "In progress" &&
               status != "Half Time" && status != "Full Time" &&
               status != "Postponed" && status != "Cancelled") {
                cout << "Invalid Status" << endl;
                return;
            }
            fixtureStatus = status;
        }

        void setAttendance(int attend) {
            if(attend >= 0) attendance = attend;
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
            if (fixtureStatus == "Cancelled" || fixtureStatus == "Postponed" ||
                other.fixtureStatus == "Cancelled" || other.fixtureStatus == "Postponed")
            {
                return false;
            }

            bool sameDate =
                fixtureDate.getDay() == other.fixtureDate.getDay() &&
                fixtureDate.getMonth() == other.fixtureDate.getMonth() &&
                fixtureDate.getYear() == other.fixtureDate.getYear();

            bool sameTime =
                fixtureTime.getHours() == other.fixtureTime.getHours() &&
                fixtureTime.getMinutes() == other.fixtureTime.getMinutes() &&
                fixtureTime.getSeconds() == other.fixtureTime.getSeconds();

            return sameDate && sameTime;

        }

        void addOfficial(MatchOfficial* o){
            if (o == nullptr) throw SchedulingConflictException();
            for (MatchOfficial* assigned : officials)
                if (assigned == o) throw SchedulingConflictException();
            officials.push_back(o);
            bool idStored=false;
            for(int id : officialIDs) if(id==o->getIdNom()) idStored=true;
            if(!idStored) officialIDs.push_back(o->getIdNom());
        }
        void recordResults(const MatchResult& matchResult){
            if (fixtureStatus == "Cancelled" || fixtureStatus == "Postponed" ||
                fixtureStatus == "Full Time" || resultRecorded || !matchResult.validateScores())
                throw FixtureIncompleteException();
            result = matchResult;
            resultRecorded = true;
        }
        bool hasResult() const { return resultRecorded; }
        bool pointsAwarded() const { return leaguePointsAwarded; }
        MatchResult getResult() const { return result; }
        int getStadiumID() const { return stadiumID; }
        void setStadium(Stadium* selected) {
            stadium = selected;
            if (selected) stadiumID = selected->getStadiumID();
        }
        Stadium* getStadium() const { return stadium; }
        const vector<int>& getAssignedOfficialIDs() const { return officialIDs; }
        void assignStadiumID(int id) { if (id > 0) stadiumID = id; }
        void completeFixture(){
            if (officials.empty() || !resultRecorded ||
                fixtureStatus == "Cancelled" || fixtureStatus == "Postponed")
                throw FixtureIncompleteException();
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

        void Display() const {
            cout << "\nFixture ID: " << fixtureID
                 << " | Date: "; fixtureDate.displayDate();
            cout << " | Time: "; fixtureTime.displayTime();
            cout << "Status: " << fixtureStatus
                 << " | Home Team: " << homeTeamID
                 << " | Away Team: " << awayTeamID
                 << " | Stadium ID: " << stadiumID << '\n';
            if (resultRecorded) result.Display();
        }

        string toFileString() const override
        {
            stringstream ss;
            ss << fixtureID << ","
               << fixtureDate.getDay() << ","
               << fixtureDate.getMonth() << ","
               << fixtureDate.getYear() << ","
               << fixtureTime.getHours() << ","
               << fixtureTime.getMinutes() << ","
               << fixtureTime.getSeconds() << ","
               << fixtureStatus << ","
               << attendance << ","
               << homeTeamID << ","
               << awayTeamID << ","
               << stadiumID << ","
               << resultRecorded << ","
               << leaguePointsAwarded << ","
               << result.getHomeScore() << ","
               << result.getAwayScore() << ","
               << result.getWinner() << ","
               << result.getMatchStatistics() << ",";
            for (size_t i=0;i<officialIDs.size();++i) {
                if(i) ss << ";";
                ss << officialIDs[i];
            }
            return ss.str();
        }

        static Fixture fromFileString(const string& data)
        {
            stringstream ss(data);
            Fixture fixture;
            string status;
            char comma;
            int id=0, day=0, month=0, year=0, hours=0, minutes=0, seconds=0;
            int attend=0, homeID=0, awayID=0, stadium=0, recorded=0, awarded=0;
            int homeScore=0, awayScore=0;
            string winner, statistics, officialsText;
            ss >> id >> comma >> day >> comma >> month >> comma >> year
               >> comma >> hours >> comma >> minutes >> comma >> seconds >> comma;
            getline(ss, status, ',');
            ss >> attend >> comma >> homeID >> comma >> awayID;
            if (ss.peek()==',') ss >> comma >> stadium;
            if (ss.peek()==',') ss >> comma >> recorded;
            if (ss.peek()==',') ss >> comma >> awarded;
            if (ss.peek()==',') ss >> comma >> homeScore;
            if (ss.peek()==',') ss >> comma >> awayScore;
            if (ss.peek()==',') {
                ss.get(comma);
                getline(ss,winner,',');
                getline(ss,statistics,',');
                getline(ss,officialsText);
            }
            fixture.setFixtureID(id);
            fixture.setFixtureDate(day, month, year);
            fixture.setFixtureTime(hours, minutes, seconds);
            fixture.setFixtureStatus(status);
            fixture.setAttendance(attend);
            fixture.homeTeamID=homeID; fixture.awayTeamID=awayID;
            fixture.stadiumID=stadium;
            fixture.resultRecorded=(recorded!=0);
            fixture.leaguePointsAwarded=(awarded!=0);
            if (fixture.resultRecorded) {
                fixture.result.setHomeScore(homeScore);
                fixture.result.setAwayScore(awayScore);
                fixture.result.setWinner(winner);
                fixture.result.setMatchStatistics(statistics);
            }
            if (!officialsText.empty()) {
                stringstream ids(officialsText); string idText;
                while(getline(ids,idText,';')) if(!idText.empty()) fixture.officialIDs.push_back(stoi(idText));
            }
            return fixture;
        }
};

inline bool MatchOfficial::assignFixture(Fixture& fixture)
{
    if (!availability) return false;
    for (Fixture* existing : assignedFixtures) {
        if (!existing) continue;
        if (existing == &fixture) return false;
        if (existing->getFixtureDateMember().getDay() == fixture.getFixtureDateMember().getDay() &&
            existing->getFixtureDateMember().getMonth() == fixture.getFixtureDateMember().getMonth() &&
            existing->getFixtureDateMember().getYear() == fixture.getFixtureDateMember().getYear() &&
            existing->getFixtureTimeMember().getHours() == fixture.getFixtureTimeMember().getHours() &&
            existing->getFixtureTimeMember().getMinutes() == fixture.getFixtureTimeMember().getMinutes() &&
            existing->getFixtureTimeMember().getSeconds() == fixture.getFixtureTimeMember().getSeconds())
            return false;
    }
    assignedFixtures.push_back(&fixture);
    return true;
}

#endif // FIXTURE_H
