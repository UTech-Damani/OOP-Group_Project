#ifndef PROJECTTIME_H
#define PROJECTTIME_H

#include <iostream>

using namespace std;

class ProjectTime {
    private:
        int hours;
        int minutes;
        int seconds;

    public:
        // Default constructor
        ProjectTime() {
            hours = 0;
            minutes = 0;
            seconds = 0;
        }

        // Parameterized constructor
        ProjectTime(int h, int m, int s) {
            setHours(h);
            setMinutes(m);
            setSeconds(s);
        }

        // ================= SETTERS =================
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

        // ================= GETTERS =================
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
