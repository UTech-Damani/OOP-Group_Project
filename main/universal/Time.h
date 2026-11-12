#ifndef TIME_H
#define TIME_H


using namespace std;

class Time {
    private:
        int hours;
        int minutes;
        int seconds;

    public:
        // Default constructor
        Time() {
            hours = 0;
            minutes = 0;
            seconds = 0;
        }

        // Parameterized constructor
        Time(int h, int m, int s) {
            setHours(h);
            setMinutes(m);
            setSeconds(s);
        }

        // Setters
        void setHours(int h) {
            if (h >= 0 && h <= 23) {
                hours = h;
            }
        }

        void setMinutes(int m) {
            if (m >= 0 && m <= 59) {
                minutes = m;
            }
        }

        void setSeconds(int s) {
            if (s >= 0 && s <= 59) {
                seconds = s;
            }
        }

        // Getters
        int getHours() const {
            return hours;
        }

        int getMinutes() const {
            return minutes;
        }

        int getSeconds() const {
            return seconds;
        }

        // Display time
        void displayTime() const {
            cout << hours << ":" << minutes << ":" << seconds << endl;
        }
};

#endif // TIME_H
