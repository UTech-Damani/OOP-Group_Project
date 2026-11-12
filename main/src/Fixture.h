#ifndef FIXTURE_H
#define FIXTURE_H

#include <string>
#include <iomanip>

using namespace std;

class Fixture
{
    private:
        int fixtureID;
        string fixtureDate;
        string fixtureTime;
        string fixtureStatus;
        int attendance;

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
};

#endif // FIXTURE_H
