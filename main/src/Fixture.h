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
#include <vector> // Provides the vector container for storing dynamic collections.
#include <sstream>
#include <iostream>

using namespace std;

// Inherits from Persistable to support saving and loading fixture records.
class Fixture : public Persistable
{
private:

    // Tracks the current state of a live match
    int currentMinute = 0;
    int liveHomeScore = 0;
    int liveAwayScore = 0;

    // Stores events that occur during the match, such as goals and half-time.
    vector<string> matchEvents;

    // Identifies the fixture and its scheduled teams
    int fixtureID;
    int homeTeamID;
    int awayTeamID;

    // Stores fixture details
    Date fixtureDate;
    ProjectTime fixtureTime;
    string fixtureStatus;
    
    // Indicates whether the final match result has been recorded.
    bool resultRecorded;

    // Indicates whether league points have already been awarded.
    bool leaguePointsAwarded;

    // Stores the stadium and officials assigned to the fixture and the number of persons attending
    Stadium* stadium;
    vector<MatchOfficial*> officials;
    int attendance;

    // Stores the official result of the fixture.
    MatchResult result;
    
    // Allows the FootballLeague class to access private Fixture members.
    friend class FootballLeague;

public:

    // Default constructor initializes the fixture with default values.
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

        resultRecorded = false;
        leaguePointsAwarded = false;

        stadium = nullptr;
    }

    // Parameterized constructor initializes the fixture attributes
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

        resultRecorded = false;
        leaguePointsAwarded = false;

        this->stadium = &stadium;
    }

    // Returns the current minute of the live match.
    int getCurrentMinute() const
    {
        return currentMinute;
    }

    // Returns the current live score of the home team.
    int getLiveHomeScore() const
    {
        return liveHomeScore;
    }

    // Returns the current live score of the away team.
    int getLiveAwayScore() const
    {
        return liveAwayScore;
    }

    // Returns a constant reference to the collection of recorded match events.
    // "const" Prevents the caller from modifying the original event collection.
    const vector<string>& getMatchEvents() const
    {
        return matchEvents;
    }

    // ================= SETTERS =================

    // Sets or updates the fixture ID.
    void setFixtureID(int id)
    {
        fixtureID = id;
    }

    // Assigns a stadium to the fixture using its memory address.
    void setStadium(Stadium* stadium)
    {
        this->stadium = stadium;
    }

    // Sets the scheduled date of the fixture.
    void setFixtureDate(int day, int month, int year)
    {
        fixtureDate.setDay(day);
        fixtureDate.setMonth(month);
        fixtureDate.setYear(year);
    }

    // Sets the scheduled starting time of the fixture.
    void setFixtureTime(int hours, int minutes, int seconds)
    {
        fixtureTime.setHours(hours);
        fixtureTime.setMinutes(minutes);
        fixtureTime.setSeconds(seconds);
    }

    // Updates the fixture status if it matches one of the accepted values.
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

    // Updates the fixture attendance if the supplied value is non-negative.
    void setAttendance(int attend)
    {
        if (attend >= 0)
        {
            attendance = attend;
        }
    }

    // ================= GETTERS =================

    // Returns the fixture ID.
    int getFixtureID() const
    {
        return fixtureID;
    }

    // Displays the scheduled fixture date.
    void getFixtureDate()
    {
        fixtureDate.displayDate();
    }

    // Returns the Date object containing the fixture date.
    Date getFixtureDateMember() const
    {
        return fixtureDate;
    }

    // Displays the scheduled fixture time.
    void getFixtureTime() const
    {
        fixtureTime.displayTime();
    }

    // Returns the ProjectTime object containing the fixture time.
    ProjectTime getFixtureTimeMember() const
    {
        return fixtureTime;
    }

    // Returns the current fixture status.
    string getFixtureStatus() const
    {
        return fixtureStatus;
    }

    // Returns the number of spectators attending the fixture.
    int getAttendance() const
    {
        return attendance;
    }

    // Returns the home team's ID.
    int getHomeTeamID() const
    {
        return homeTeamID;
    }

    // Returns the away team's ID.
    int getAwayTeamID() const
    {
        return awayTeamID;
    }

    // Checks whether a result has been recorded for the fixture.
    bool hasResult() const
    {
        return resultRecorded;
    }

    // Checks whether league points have already been awarded.
    bool hasAwardedPoints() const
    {
        return leaguePointsAwarded;
    }

    // Returns the pointer to the stadium assigned to the fixture.
    Stadium* getStadium() const
    {
        return stadium;
    }

    // Returns the recorded MatchResult object.
    MatchResult getResult() const
    {
        return result;
    }

    // Returns a reference to the collection of assigned match officials.
    vector<MatchOfficial*>& getOfficials()
    {
        return officials;
    }

    // Checks whether two fixtures are scheduled for the same date and time.
    bool conflictsWith(const Fixture& other) const
    {
        if (fixtureStatus == "Cancelled" || fixtureStatus == "Postponed" ||
            other.fixtureStatus == "Cancelled" || other.fixtureStatus == "Postponed")
        {
            return false;
        }

        // Checks whether both fixtures have the same calendar date.
        bool sameDate = fixtureDate.getDay() == other.fixtureDate.getDay() &&
                        fixtureDate.getMonth() == other.fixtureDate.getMonth() &&
                        fixtureDate.getYear() == other.fixtureDate.getYear();

        // Checks whether both fixtures have the same starting time.
        bool sameTime = fixtureTime.getHours() == other.fixtureTime.getHours() &&
                        fixtureTime.getMinutes() == other.fixtureTime.getMinutes();

        return sameDate && sameTime;
    }

    // Assigns a match official to the fixture.
    void addOfficial(MatchOfficial* official)
    {
        if (official == nullptr)
        {
            throw SchedulingConflictException();
        }

        // Checks whether the official is already assigned.
        for (MatchOfficial* existing : officials)
        {
            if (existing == official)
            {
                throw SchedulingConflictException();
            }
        }

        officials.push_back(official);
    }

    // Records the final result of the fixture.
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

        // Validates the scores before storing the result.
        if (!matchResult.validateScores())
        {
            throw FixtureIncompleteException();
        }

        result = matchResult;

        resultRecorded = true;

        fixtureStatus = "Full Time";
    }

    // Marks the fixture as completed.
    void completeFixture()
    {
        if (fixtureStatus == "Cancelled" || fixtureStatus == "Postponed")
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

    // Changes the fixture status to Postponed.
    void postpone()
    {
        if (fixtureStatus == "Full Time" || fixtureStatus == "Cancelled")
        {
            throw FixtureIncompleteException();
        }

        fixtureStatus = "Postponed";
    }

    // Changes the fixture status to Cancelled.
    void cancel()
    {
        if (fixtureStatus == "Full Time")
        {
            throw FixtureIncompleteException();
        }

        fixtureStatus = "Cancelled";
    }

    // Displays the main details and current status of the fixture.
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

        cout << "\nStatus: " << fixtureStatus;
        cout << "\nAttendance: " << attendance;

        cout << "\nResult Recorded: " << (resultRecorded ? "Yes" : "No");

        cout << "\n=============================\n";
    }

    // Starts a scheduled fixture and initializes its live match information.
    void startMatch()
    {
        if(fixtureStatus != "Scheduled")
        {
            throw FixtureIncompleteException();
        }

        if(officials.empty())
        {
            throw FixtureIncompleteException();
        }

        if(homeTeamID == 0 || awayTeamID == 0)
        {
            throw FixtureIncompleteException();
        }

        // Resets the live match minute and both teams' scores.
        currentMinute = 0;
        liveHomeScore = 0;
        liveAwayScore = 0;

        // Removes any events from previous match activity.
        matchEvents.clear();

        // Updates the fixture status to indicate that the match has started.
        fixtureStatus = "In progress";

        // Records the start of the match in the event collection.
        matchEvents.push_back("Match started.");
    }

    // Updates the current minute of an ongoing match.
    void updateMatchMinute(int minute)
    {
        if(fixtureStatus != "In progress")
        {
            throw FixtureIncompleteException();
        }

        if(minute < currentMinute || minute > 120)
        {
            throw FixtureIncompleteException();
        }

        currentMinute = minute;
    }

    // Records a goal scored by either the home or away team.
    void recordLiveGoal(bool homeTeam, const string& teamName)
    {
        if(fixtureStatus != "In progress")
        {
            throw FixtureIncompleteException();
        }

        // Increases the home team's live score if homeTeam is true.
        if(homeTeam)
        {
            liveHomeScore++;
        }
        // Otherwise, increases the away team's live score.
        else
        {
            liveAwayScore++;
        }

        // Creates a match event containing the current minute and team name.
        string event = to_string(currentMinute) + "' - GOAL! " + teamName;

        matchEvents.push_back(event);
    }

    // Changes the fixture status to Half Time.
    void startHalfTime()
    {
        if(fixtureStatus != "In progress" || currentMinute < 45)
        {
            throw FixtureIncompleteException();
        }

        fixtureStatus = "Half Time";

        // Records the half-time event.
        matchEvents.push_back("Half-time.");
    }

    // Resumes a fixture after half-time.
    void resumeMatch()
    {
        if(fixtureStatus != "Half Time")
        {
            throw FixtureIncompleteException();
        }

        fixtureStatus = "In progress";

        // Records the beginning of the second half.
        matchEvents.push_back("Second half started.");
    }

    // Records the end of the live match.
    void finishLiveMatch()
    {
        if(fixtureStatus != "In progress" || currentMinute < 90)
        {
            throw FixtureIncompleteException();
        }

        // Adds the full-time event to the match event collection.
        matchEvents.push_back("Full-time.");

        // The final result is recorded separately using the existing MatchResult class.
    }

    // Converts the fixture's information into a csv format.
    string toFileString() const
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
           << resultRecorded << ","
           << leaguePointsAwarded;

        // Adds the final scores if a result has been recorded.
        if (resultRecorded)
        {
            ss << "," << result.getHomeScore() << "," << result.getAwayScore();
        }

        return ss.str();
    }

    // Extracts the saved fixture information and restores its attributes.
    static Fixture fromFileString(const string& data)
    {
        stringstream ss(data);

        Fixture fixture;

        // Variables temporarily store the values extracted from the file.
        int id, day, month, year;
        int hours, minutes, seconds;
        int attend, homeID, awayID;

        int recorded = 0;
        int awarded = 0;

        string status;

        char comma;

        // Extracts the fixture ID and date.
        ss >> id >> comma;
        ss >> day >> comma;
        ss >> month >> comma;
        ss >> year >> comma;

        // Extracts the scheduled fixture time.
        ss >> hours >> comma;
        ss >> minutes >> comma;
        ss >> seconds >> comma;

        // Extracts the fixture status.
        getline(ss, status, ',');

        // Extracts attendance and the participating team IDs.
        ss >> attend >> comma;
        ss >> homeID >> comma;
        ss >> awayID;

        // Extracts the result-recorded flag if it exists.
        if (ss.peek() == ',')
        {
            ss >> comma >> recorded;
        }

        // Extracts the league-points-awarded flag if it exists.
        if (ss.peek() == ',')
        {
            ss >> comma >> awarded;
        }

        // Restores the fixture's basic information.
        fixture.setFixtureID(id);
        fixture.setFixtureDate(day, month, year);
        fixture.setFixtureTime(hours, minutes, seconds);
        fixture.setFixtureStatus(status);
        fixture.setAttendance(attend);

        fixture.homeTeamID = homeID;
        fixture.awayTeamID = awayID;

        // Restores the result and league-points flags.
        fixture.resultRecorded = recorded != 0;
        fixture.leaguePointsAwarded = awarded != 0;

        // Restores the final scores if a result was previously recorded.
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