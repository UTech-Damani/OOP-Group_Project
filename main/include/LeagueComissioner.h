#ifndef LEAGUECOMMISSIONER_H
#define LEAGUECOMMISSIONER_H
#include "Person.h"
#include <string>

class LeagueCommissioner : public Person{
    bool approvalAuthority;
    int yearsOfService;
    std::string assignedRegion;

    public:
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

        //Setters
        void setApprovalAuthority(bool apr){
            approvalAuthority = apr;
        }
        void setYearsOfService(int year){
            yearsOfService = year;
        }
        void setAssignedRegion(const std::string& region){
            assignedRegion = region;
        }
};

#endif
