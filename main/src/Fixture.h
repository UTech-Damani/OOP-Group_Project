#ifndef FIXTURE_H
#define FIXTURE_H

#include "Stadium.h"
#include "MatchResults.h"

#include "../include/MatchOfficial.h"
#include "../universal/Date.h"
#include "../universal/ProjectTime.h"
#include "../universal/FileManager.h"

#include "../exceptions/FixtureIncompleteException.h"
#include "../exceptions/SchedulingConflictException.h"

#include <string>
#include <vector>
#include <sstream>
#include <iostream>

using namespace std;

class Fixture : public Persistable
{
private:
    int fixtureID;
    Date fixtureDate;
    ProjectTime fixtureTime;

    string fixtureStatus;
    int attendance;

    int homeTeamID;
    int awayTeamID;
    int stadiumID;

    bool resultRecorded;
    bool leaguePointsAwarded;

    Stadium* stadium;

    MatchResult result;

    vector<MatchOfficial*> officials;

    friend class FootballLeague;

public:

    Fixture()
    {
        fixtureID = 0;

        fixtureDate.setDay(0);
        fixtureDate.setMonth(0);
        fixtureDate.setYear(0);

        fixtureTime.setHours(0);
        fixtureTime.setMinutes(0);
        fixtureTime.setSeconds(0);

        fixtureStatus = "No schedule at this moment";

        attendance = 0;

        homeTeamID = 0;
        awayTeamID = 0;
        stadiumID = 0;

        resultRecorded = false;
        leaguePointsAwarded = false;

        stadium = nullptr;
    }

    Fixture(int day, int month, int year,
            int hours, int minutes, int seconds,
            string status, int attendance,
            Stadium& stadium)
    {
        fixtureID = 0;

        setFixtureDate(day, month, year);
        setFixtureTime(hours, minutes, seconds);

        fixtureStatus = status;

        this->attendance = attendance;

        homeTeamID = 0;
        awayTeamID = 0;
        stadiumID = stadium.getStadiumID();

        resultRecorded = false;
        leaguePointsAwarded = false;

        this->stadium = &stadium;
    }

    // SETTERS

    void setFixtureID(int id)
    {
        fixtureID = id;
    }

    void setFixtureDate(int day, int month, int year)
    {
        fixtureDate.setDay(day);
        fixtureDate.setMonth(month);
        fixtureDate.setYear(year);
    }

    void setFixtureTime(int hours, int minutes, int seconds)
    {
        fixtureTime.setHours(hours);
        fixtureTime.setMinutes(minutes);
        fixtureTime.setSeconds(seconds);
    }

    void setFixtureStatus(string status)
    {
        if (status == "Scheduled" ||
            status == "In progress" ||
            status == "Half Time" ||
            status == "Full Time" ||
            status == "Postponed" ||
            status == "Cancelled")
        {
            fixtureStatus = status;
        }
    }

    void setStadiumID(int id)
    {
        if (id > 0)
        {
            stadiumID = id;
        }
    }

    void setAttendance(int attend)
    {
        if (attend >= 0)
        {
            attendance = attend;
        }
    }

    // GETTERS

    int getFixtureID() const
    {
        return fixtureID;
    }

    void getFixtureDate()
    {
        fixtureDate.displayDate();
    }

    Date getFixtureDateMember() const
    {
        return fixtureDate;
    }

    void getFixtureTime() const
    {
        fixtureTime.displayTime();
    }

    ProjectTime getFixtureTimeMember() const
    {
        return fixtureTime;
    }

    string getFixtureStatus() const
    {
        return fixtureStatus;
    }

    int getAttendance() const
    {
        return attendance;
    }

    int getHomeTeamID() const
    {
        return homeTeamID;
    }

    int getAwayTeamID() const
    {
        return awayTeamID;
    }

    int getStadiumID() const
    {
        return stadiumID;
    }

    bool hasResult() const
    {
        return resultRecorded;
    }

    bool hasAwardedPoints() const
    {
        return leaguePointsAwarded;
    }

    Stadium* getStadium() const
    {
        return stadium;
    }

    MatchResult getResult() const
    {
        return result;
    }

    vector<MatchOfficial*>& getOfficials()
    {
        return officials;
    }

    // CHECK SCHEDULING CONFLICTS

    bool conflictsWith(const Fixture& other) const
    {
        if (fixtureStatus == "Cancelled" ||
            fixtureStatus == "Postponed" ||
            other.fixtureStatus == "Cancelled" ||
            other.fixtureStatus == "Postponed")
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

    // OFFICIAL MANAGEMENT

    void addOfficial(MatchOfficial* official)
    {
        if (official == nullptr)
        {
            throw SchedulingConflictException();
        }

        for (MatchOfficial* existing : officials)
        {
            if (existing == official)
            {
                throw SchedulingConflictException();
            }
        }

        officials.push_back(official);
    }

    // RESULT MANAGEMENT

    void recordResults(const MatchResult& matchResult)
    {
        if (fixtureStatus == "Cancelled" ||
            fixtureStatus == "Postponed" ||
            fixtureStatus == "Full Time")
        {
            throw FixtureIncompleteException();
        }

        if (resultRecorded)
        {
            throw FixtureIncompleteException();
        }

        if (!matchResult.validateScores())
        {
            throw FixtureIncompleteException();
        }

        result = matchResult;

        resultRecorded = true;

        fixtureStatus = "Full Time";
    }

    // COMPLETE FIXTURE

    void completeFixture()
    {
        if (fixtureStatus == "Cancelled" ||
            fixtureStatus == "Postponed")
        {
            throw FixtureIncompleteException();
        }

        if (officials.empty())
        {
            throw FixtureIncompleteException();
        }

        if (!resultRecorded)
        {
            throw FixtureIncompleteException();
        }

        fixtureStatus = "Full Time";
    }

    // POSTPONE FIXTURE

    void postpone()
    {
        if (fixtureStatus == "Full Time" ||
            fixtureStatus == "Cancelled")
        {
            throw FixtureIncompleteException();
        }

        fixtureStatus = "Postponed";
    }

    // CANCEL FIXTURE

    void cancel()
    {
        if (fixtureStatus == "Full Time")
        {
            throw FixtureIncompleteException();
        }

        fixtureStatus = "Cancelled";
    }

    // DISPLAY FIXTURE

    void Display() const
    {
        cout << "\n========== FIXTURE ==========";

        cout << "\nFixture ID: " << fixtureID;

        cout << "\nDate: ";
        fixtureDate.displayDate();

        cout << "\nTime: ";
        fixtureTime.displayTime();

        cout << "\nHome Team ID: " << homeTeamID;
        cout << "\nAway Team ID: " << awayTeamID;
        cout << "\nStadium ID: " << stadiumID;

        cout << "\nStatus: " << fixtureStatus;
        cout << "\nAttendance: " << attendance;

        cout << "\nResult Recorded: "
             << (resultRecorded ? "Yes" : "No");

        cout << "\n=============================\n";
    }

    // FILE MANAGEMENT

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
           << leaguePointsAwarded;

        if (resultRecorded)
        {
            ss << ","
               << result.getHomeScore()
               << ","
               << result.getAwayScore();
        }

        return ss.str();
    }

    static Fixture fromFileString(const string& data)
    {
        stringstream ss(data);

        Fixture fixture;

        int id, day, month, year;
        int hours, minutes, seconds;
        int attend, homeID, awayID;
        int stadID = 0;

        int recorded = 0;
        int awarded = 0;

        string status;

        char comma;

        ss >> id >> comma;
        ss >> day >> comma;
        ss >> month >> comma;
        ss >> year >> comma;

        ss >> hours >> comma;
        ss >> minutes >> comma;
        ss >> seconds >> comma;

        getline(ss, status, ',');

        ss >> attend >> comma;
        ss >> homeID >> comma;
        ss >> awayID >> comma;
        ss >> stadID;

        if (ss.peek() == ',')
        {
            ss >> comma >> recorded;
        }

        if (ss.peek() == ',')
        {
            ss >> comma >> awarded;
        }

        fixture.setFixtureID(id);
        fixture.setFixtureDate(day, month, year);
        fixture.setFixtureTime(hours, minutes, seconds);
        fixture.setFixtureStatus(status);
        fixture.setAttendance(attend);

        fixture.homeTeamID = homeID;
        fixture.awayTeamID = awayID;
        fixture.stadiumID = stadID;

        fixture.resultRecorded = recorded != 0;
        fixture.leaguePointsAwarded = awarded != 0;

        if (fixture.resultRecorded)
        {
            int homeScore = 0;
            int awayScore = 0;

            if (ss.peek() == ',')
            {
                ss >> comma >> homeScore;
            }

            if (ss.peek() == ',')
            {
                ss >> comma >> awayScore;
            }

            fixture.result.setHomeScore(homeScore);
            fixture.result.setAwayScore(awayScore);
        }

        return fixture;
    }
};

#endif