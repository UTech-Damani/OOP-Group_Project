#ifndef FIXTURE_H
#define FIXTURE_H
#include <string>

class Fixture{
    private:
        int fixtureID = 0;
        std::string fixtureDate;
        std::string fixtureTime;
        std::string fixtureStatus;
        int attendance = 0;

    public:
        Fixture() = default;

        Fixture(int id, const std::string& date, const std::string& time, const std::string& status = "Scheduled", int att = 0)
        : fixtureID(id),fixtureDate(date), fixtureTime(time), fixtureStatus(status), attendance(att){}

        int getFixtureID() const{
            return fixtureID;
        }
        std::string getFixtureDate() const{
            return fixtureDate;
        }
        std::string getFixtureTime() const{
        return fixtureTime;
        }
        std::string getFixtureStatus() const{
            return fixtureStatus;
        }
        int getAttendance() const{
            return attendance;
        }

        void setFixtureID(int id){
            fixtureID = id;
        }
        void setFixtureDate(const std::string& date){
            fixtureDate = date;
        }
        void setFixtureTime(const std::string& time){
            fixtureTime = time;
        }
        void setFixtureStatus(const std::string& status){
            fixtureStatus = status;
        }
        void setAttendance(int att){
            attendance = att;
        }
        bool conflictsWith(const Fixture& other) const{
            if(fixtureStatus == "Cancelled" || other.fixtureStatus == "Cancelled"){
                return false;
            }
            return fixtureDate == other.fixtureDate && fixtureTime == other.fixtureTime;
        }
    };
#endif