#ifndef FOOTBALLLEAGUE_H
#define FOOTBALLLEAGUE_H


class FootballLeague
{
    private:
        int leagueID;
        string leagueName;
        string season;
        Date startDate;
        Date endDate;
        int numberOfTeams;
        string currentStatus;

    public:
        // Default Constructor
        FootballLeague() {
            leagueID = 0;
            leagueName = "";
            season = "";
            numberOfTeams = 0;
            currentStatus = "";
        }

        // Parameterized Constructor
        FootballLeague(int leagueID, string leagueName, string season,
                       Date startDate, Date endDate,
                       int numberOfTeams, string currentStatus) {
            this->leagueID = leagueID;
            this->leagueName = leagueName;
            this->season = season;
            this->startDate = startDate;
            this->endDate = endDate;
            this->numberOfTeams = numberOfTeams;
            this->currentStatus = currentStatus;
        }

        // Getters
        int getLeagueID() {
            return leagueID;
        }

        string getLeagueName() {
            return leagueName;
        }

        string getSeason() {
            return season;
        }

        Date getStartDate() {
            return startDate;
        }

        Date getEndDate() {
            return endDate;
        }

        int getNumberOfTeams() {
            return numberOfTeams;
        }

        string getCurrentStatus() {
            return currentStatus;
        }

        // Setters
        void setLeagueID(int leagueID) {
            this->leagueID = leagueID;
        }

        void setLeagueName(string leagueName) {
            this->leagueName = leagueName;
        }

        void setSeason(string season) {
            this->season = season;
        }

        void setStartDate(Date startDate) {
            this->startDate = startDate;
        }

        void setEndDate(Date endDate) {
            this->endDate = endDate;
        }

        void setNumberOfTeams(int numberOfTeams) {
            this->numberOfTeams = numberOfTeams;
        }

        void setCurrentStatus(string currentStatus) {
            this->currentStatus = currentStatus;
        }

};

#endif // FOOTBALLLEAGUE_H
