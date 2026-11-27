#ifndef DATE_H
#define DATE_H

#include <iostream>
using namespace std;

class Date {
    private:
        int day;
        int month;
        int year;

    public:
        // Default constructor
        Date(){
            day = 0;
            month = 0;
            year = 0;
        }

        // Parameterized constructor
        Date(int d, int m, int y){
            setDay(d);
            setMonth(m);
            setYear(y);
        }

        // ================= SETTERS =================
        void setDay(int d){
            day = d;
        }
        void setMonth(int m){
            month = m;
        }
        void setYear(int y){
            year = y;
        }

        // ================= GETTERS =================
        int getDay() const{
            return day;
        }
        int getMonth() const{
            return month;
        }
        int getYear() const{
            return year;
        }

        // Display date
        void displayDate() const{
            cout << day << "/" << month << "/" << year << endl;
        }
};

#endif // DATE_H
