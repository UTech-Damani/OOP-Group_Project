#ifndef DATE_H
#define DATE_H

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

        // Setters
        void setDay(int d){
            day = d;
        }
        void setMonth(int m){
            month = m;
        }
        void setYear(int y){
            year = y;
        }

        // Getters
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
        void displayDate(){
            cout << day << "/" << month << "/" << year << endl;
        }
};

#endif // DATE_H
