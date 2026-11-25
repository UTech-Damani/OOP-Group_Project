#ifndef LEAGUECOMMISSIONER_H
#define LEAGUECOMMISSIONER_H
#include "Person.h"
#include "../src/Fixture.h"
#include "MatchOfficial.h"
#include "FootballTeam.h"
#include "../exceptions/TeamNotEligibleException.h"
#include "../exceptions/SchedulingConflictException.h"

#include <string>
#include <iostream>

class LeagueCommissioner : public Person{
    private:
        bool approvalAuthority;
        int yearsOfService;
        std::string assignedRegion;
        vector<Fixture> fixtures;

    public:
        LeagueCommissioner(){
            approvalAuthority = false;
            yearsOfService = 0;
            assignedRegion = "No region Assigned";
        }
        
        LeagueCommissioner(int yearsOfService, string assignedRegion,
                            int IdNom, string FullName, int Age, string Gender) : Person(IdNom, FullName, Age, Gender){
                                this->approvalAuthority = true;
                                this->yearsOfService = yearsOfService;
                                this->assignedRegion = assignedRegion;
                            }

        //Getters
        bool getApprovalAuthority() const{
            return approvalAuthority;
        }
        int getYearsOfService() const{
            return yearsOfService;
        }
        std::string getAssignedRegion() const{
            return assignedRegion;
        }
        std::string getRole() const{
            return "League Commissioner";
        }
        vector<Fixture>& getFixtures() {
            return fixtures;
        }

        //Setters - Monecia
        void setApprovalAuthority(bool apr){
            approvalAuthority = apr;
        }
        void setYearsOfService(int year){
            if (year >= 0)
            {
                yearsOfService = year;
            }
        }
        void setAssignedRegion(const std::string& region){
            if (region != "")
            {
                assignedRegion = region;
            }
        }

        void approveTeam(FootballTeam& team){
            if (team.getPlayers().size() == 0 || team.getCoaches().size() == 0){
                team.setTeamStatus("suspended");
                throw TeamNotEligibleException();
            }
            
            for (Player& player : team.getPlayers()){
                if (player.isEligible() == false)
                {
                    team.setTeamStatus("suspended");
                    throw TeamNotEligibleException();
                }
            }

            team.setTeamStatus("approved");
            
        }
        void suspendTeam(FootballTeam& team){
            team.setTeamStatus("suspended");
        }
        void reinstateTeam(FootballTeam& team)
        {
            team.setTeamStatus("registered");
        }
        void assignOfficial(Fixture& fixture, MatchOfficial& official){
            if(!official.canAssignFixture()){
                throw SchedulingConflictException();
            }

            fixture.addOfficial(&official);

            official.assignFixture(fixture);

        }

        void scheduleFixture(Fixture& fixture)
        {
            // Fixture must have both teams assigned
            if (fixture.getHomeTeamID() == 0 ||
                fixture.getAwayTeamID() == 0)
            {
                throw FixtureIncompleteException();
            }

            // Team cannot play itself
            if (fixture.getHomeTeamID() ==
                fixture.getAwayTeamID())
            {
                throw TeamNotEligibleException();
            }

            // Check for fixture conflicts
            for (Fixture& existing : fixtures)
            {
                if (fixture.conflictsWith(existing))
                {
                    throw SchedulingConflictException();
                }
            }

            fixtures.push_back(fixture);

            cout << "Fixture scheduled successfully." << endl;
        }


        void Display() 
        {
            cout << "ID: " << getIdNom() << endl;
            cout << "Name: " << getFullName() << endl;
            cout << "Age: " << getAge() << endl;
            cout << "Gender: " << getGender() << endl;
            cout << "Approval Authority: "
                << (approvalAuthority ? "Yes" : "No")
                << endl;
            cout << "Years Of Service: "
                << yearsOfService << endl;
            cout << "Assigned Region: "
                << assignedRegion << endl;
        }
};

#endif
