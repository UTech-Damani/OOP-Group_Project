#ifndef DATE_H
#define DATE_H


class Date {
    private:
        int day;
        int month;
        int year;

    public:
        // Default Constructor
        Date() {
            day = 1;
            month = 1;
            year = 2000;
        }

        // Parameterized Constructor
        Date(int day, int month, int year) {
            this->day = day;
            this->month = month;
            this->year = year;
        }

        // Getters
        int getDay() {
            return day;
        }

        int getMonth() {
            return month;
        }

        int getYear() {
            return year;
        }

        // Setters
        void setDay(int day) {
            this->day = day;
        }

        void setMonth(int month) {
            this->month = month;
        }

        void setYear(int year) {
            this->year = year;
        }
};


#endif // DATE_H
