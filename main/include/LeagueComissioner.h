#ifndef LEAGUECOMMISSIONER_H
#define LEAGUECOMMISSIONER_H
#include "Person.h"
#include "Fixture.h"
#include "MatchOfficial.h"
#include "FootballTeam.h"

#include <string>
#include <iostream>

class LeagueCommissioner : public Person{
    bool approvalAuthority;
    int yearsOfService;
    std::string assignedRegion;

    public:
        LeagueCommissioner(){
            approvalAuthority = false;
            yearsOfService = 0;
            assignedRegion = "No region Assigned";
        }
        
        LeagueCommissioner(bool approvalAuthority, int yearsOfService, string assignedRegion,
                            int IdNom, string FullName, int Age, string Gender) : Person(IdNom, FullName, Age, Gender){
                                this->approvalAuthority = approvalAuthority;
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
        std::string getRole() const
        {
            return "League Commissioner";
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
            }
            
            for (Player& player : team.getPlayers()){
                if (player.getAge())
                {
                    team.setTeamStatus("suspended");
                    return;
                }
            }

            team.setTeamStatus("approved");
            
        }
        void suspendTeam(FootballTeam& team){
            team.setTeamStatus("suspended");
        }
        void assignOfficial(Fixture& fixture, const MatchOfficial& official){
            fixture.addOfficial(official);
            
            std::cout << official.getFullName() << " assigned to fixture.\n";
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
