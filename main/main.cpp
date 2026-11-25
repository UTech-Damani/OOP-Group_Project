#include <iostream>
#include <windows.h>

#include <string>
#include <vector>
#include <ctype.h>
#include <cstdlib>
#include <ctime>

#include "universal/KPFL.h"
#include "universal/FileManager.h"

using namespace std;

int displayMainMenu();
int generateRandomID();
void teamManagement(FootballLeague& league);
void playerManagement(FootballLeague& league);
void coachManagement(FootballLeague& league);
void testExceptions();
void officialMenu();
void fixtureManagementMenu();
void commissionerMenu();
void resultsMenu();
void stadiumMenu();
void stadiumShopMenu();
void spectatorMenu();
void footballLeagueMenu();
void fileManagement(FootballLeague& league);

int main()
{
    srand(time(NULL));

    FootballLeague league;
    int choice;

    cout << "Za Wurldo!" << endl;

    do{
        int choice = displayMainMenu();

        switch (choice)
        {
            case 1:
                teamManagement(league);
                break;

            case 2:
                playerManagement(league);
                break;

            case 3:
                coachManagement(league);
                break;

            case 4:
                officialMenu();
                break;

            case 5:
                fixtureManagementMenu();
                break;

            case 6:
                commissionerMenu();
                break;

            case 7:
                resultsMenu();
                break;

            case 8:
                stadiumMenu();
                break;

            case 9:
                stadiumShopMenu();
                break;

            case 10:
                spectatorMenu();
                break;

            case 11:
                footballLeagueMenu();
                break;

            case 12:
                testExceptions();
                break;
            
            case 13:
                fileManagement(league);
                break;

            case 0:
                cout << "You are now exiting the KPFL Demo program..." << endl;
                break;
            
            default:
                break;
        }
    }while(choice != 0);

    return 0;
}


void teamManagement(FootballLeague& league){
    int choice;

    do{
        cout << "\n==================================================";
        cout << "\n TEAM MANAGEMENT";
        cout << "\n==================================================";
        cout << "\n 1. Create Team";
        cout << "\n 2. Add Player";
        cout << "\n 3. Add Coach";
        cout << "\n 4. Display Team";
        cout << "\n 5. Display All Teams";
        cout << "\n 0. Back";
        cout << "\n==================================================";
        cout << "\nChoice ==> ";
        
        cin >> choice;
        
        switch(choice){
            case 1: {
                int id = generateRandomID();
                string name;
                string parish;
                
                cin.ignore();
                
                cout << "Team Name: ";
                getline(cin,name);
                
                cout << "Parish: ";
                getline(cin,parish);
                
                FootballTeam team;
                
                team.setTeamID(id);
                team.setTeamName(name);
                team.setParish(parish);
                
                try{

                    league.registerTeam(team);

                }catch(const KPFLExceptions e){

                    cout << e.getMessage() << endl;
                }
            
                break;
            }
        
        
            case 2: {
                if(league.getTeams().empty()){
                    cout << "\nNo Teams Registered.\n";
                    break;
                }
                
                cout << "\nRegistered Teams\n";
                
                for(int i = 0; i < league.getTeams().size(); i++){
                    cout << i + 1 << ". "
                    << league.getTeams()[i].getTeamName()
                    << endl;
                }
                
                int teamChoice;
                
                cout << "\nSelect Team: ";
                cin >> teamChoice;
            
                teamChoice--;

                int id;
                string name;
                int age;
                string gender;
                string position;
                int jersey;
        
                cout << "\nPlayer ID: ";
                cin >> id;
            
                cin.ignore();
        
                cout << "Player Name: ";
                getline(cin,name);

                cout << "Age: ";
                cin >> age;
            
                cin.ignore();
                
                cout << "Position: ";
                getline(cin,position);
                
                cout << "Jersey Number: ";
                cin >> jersey;
                
                try
                {
                    Player player;
                
                    player.setIdNom(id);
                    player.setFullName(name);
                    player.setAge(age);
                    
                    player.setPositionOnField(position);
                    player.setJerseyNom(jersey);
                
                    league.getTeams()[teamChoice].addPlayer(player);
                    
                    cout << "\nPlayer Added Successfully!\n";
                }
                catch(const KPFLExceptions& e){
                    cout << e.getMessage() << endl;
                }
                break;
            }
        
            case 3:{
                if(league.getTeams().empty()){
                    cout << "\nNo Teams Registered.\n";
                    break;
                }
                
                cout << "\nRegistered Teams\n";

                for(int i = 0; i < league.getTeams().size(); i++){
                    cout << i + 1 << ". "
                    << league.getTeams()[i].getTeamName()
                    << endl;
                }
                
                int teamChoice;
            
                cout << "\nSelect Team: ";
                cin >> teamChoice;
            
                teamChoice--;
    
                int id;
                string name;
                int age;
                string gender;
                string qualification;
                string role;
    
                cout << "\nCoach ID: ";
                cin >> id;
        
                cin.ignore();
            
                cout << "Coach Name: ";
                getline(cin,name);
            
                cout << "Age: ";
                cin >> age;
            
                cin.ignore();
                
                cout << "Qualification: ";
                getline(cin,qualification);
            
                cout << "Coaching Role: ";
                getline(cin,role);
                
                Coach coach;
                
                coach.setIdNom(id);
                coach.setFullName(name);
                coach.setAge(age);
                
                coach.setQualification(qualification);
                coach.setCoachingRole(role);
                
                league.getTeams()[teamChoice].addCoach(coach);
            
                cout << "\nCoach Added Successfully!\n";
                break;
            }

            case 4: {
                if(league.getTeams().empty()){
                    cout << "\nNo Teams Registered.\n";
                    break;
                }
                
                cout << "\nRegistered Teams\n";
                
                for(int i = 0; i < league.getTeams().size(); i++){
                    cout << i + 1 << ". "
                    << league.getTeams()[i].getTeamName()
                    << endl;
                }
                
                int teamChoice;
                
                cout << "\nSelect Team: ";
                cin >> teamChoice;
                
                teamChoice--;
                
                cout << endl;
                
                league.getTeams()[teamChoice].viewTeamMembers();
                
                break;
            }
            
            case 5:{
                if(league.getTeams().empty()){
                    cout << "\nNo Teams Registered.\n";
                    break;
                }
                
                for(FootballTeam& team : league.getTeams()){
                    cout << "\n------------------------------------\n";
                    team.viewTeamMembers();
                }
                
                break;
            }
            
            case 0:
                cout << "\nReturning...\n";
                break;
            
            default:
                cout << "\nInvalid Option!\n";
        }
            
    } while(choice != 0);
    
}


void playerManagement(FootballLeague& league) {

    int choice = -1;


    while (choice != 0) {

        cout << "\n========== PLAYER MANAGEMENT ==========\n";
        cout << "1. Register Player\n";
        cout << "2. Update Player\n";
        cout << "3. Display Player Details\n";
        cout << "4. Check Player Eligibility\n";
        cout << "0. Back\n";
        cout << "=======================================\n";
        cout << "Choice ==> ";
        
        cin >> choice;

        switch (choice) {

            // REGISTER PLAYER
            case 1: {

                if (league.getTeams().empty()) {
                    cout << "\nNo Teams Registered.\n";
                    break;
                }

                cout << "\n========== REGISTER PLAYER ==========\n";

                for (int i = 0; i < league.getTeams().size(); i++) {
                    cout << i + 1 << ". "
                         << league.getTeams()[i].getTeamName()
                         << endl;
                }

                int teamChoice;

                cout << "\nSelect Team: ";
                cin >> teamChoice;

                teamChoice--;

                if (teamChoice < 0 ||
                    teamChoice >= league.getTeams().size()) {

                    cout << "\nInvalid Team Selection!\n";
                    break;
                }

                int id, age, jersey;
                string name, gender, position;

                cout << "\nPlayer ID: ";
                cin >> id;

                cin.ignore();

                cout << "Player Name: ";
                getline(cin, name);

                cout << "Age: ";
                cin >> age;

                cin.ignore();

                cout << "Gender: ";
                getline(cin, gender);

                cout << "Position: ";
                getline(cin, position);

                cout << "Jersey Number: ";
                cin >> jersey;

                try {

                    Player player;

                    player.setIdNom(id);
                    player.setFullName(name);
                    player.setAge(age);
            
                    player.setPositionOnField(position);
                    player.setJerseyNom(jersey);

                    league.getTeams()[teamChoice].addPlayer(player);

                    cout << "\nPlayer Registered Successfully!\n";

                }
                catch (const KPFLExceptions& e) {
                    cout << e.getMessage() << endl;
                }

                break;
            }

            // UPDATE PLAYER
            case 2: {

                if (league.getTeams().empty()) {
                    cout << "\nNo Teams Registered.\n";
                    break;
                }

                int teamChoice;

                cout << "\n========== SELECT TEAM ==========\n";

                for (int i = 0; i < league.getTeams().size(); i++) {
                    cout << i + 1 << ". "
                         << league.getTeams()[i].getTeamName()
                         << endl;
                }

                cout << "\nSelect Team: ";
                cin >> teamChoice;

                teamChoice--;

                if (teamChoice < 0 ||
                    teamChoice >= league.getTeams().size()) {

                    cout << "\nInvalid Team Selection!\n";
                    break;
                }

                vector<Player>& players =
                    league.getTeams()[teamChoice].getPlayers();

                if (players.empty()) {
                    cout << "\nThis Team Has No Registered Players.\n";
                    break;
                }

                int playerID;
                bool found = false;

                cout << "\nEnter Player ID: ";
                cin >> playerID;

                for (Player& player : players) {

                    if (player.getIdNom() == playerID) {

                        found = true;

                        int updateChoice;

                        cout << "\n========== UPDATE PLAYER ==========\n";
                        cout << "1. Update Name\n";
                        cout << "2. Update Age\n";
                        cout << "3. Update Position\n";
                        cout << "4. Update Jersey Number\n";
                        cout << "5. Update Status\n";
                        cout << "0. Cancel\n";
                        cout << "Choice ==> ";

                        cin >> updateChoice;

                        switch (updateChoice) {

                            case 1: {
                                string name;

                                cin.ignore();

                                cout << "New Name: ";
                                getline(cin, name);

                                player.setFullName(name);

                                cout << "\nName Updated Successfully!\n";
                                break;
                            }

                            case 2: {
                                int age;

                                cout << "New Age: ";
                                cin >> age;

                                player.setAge(age);

                                cout << "\nAge Updated Successfully!\n";
                                break;
                            }

                            case 3: {
                                string position;

                                cin.ignore();

                                cout << "New Position: ";
                                getline(cin, position);

                                player.setPositionOnField(position);

                                cout << "\nPosition Updated Successfully!\n";
                                break;
                            }

                            case 4: {
                                    int jerseyNumber;

                                    cout << "New Jersey Number: ";
                                    cin >> jerseyNumber;

                                    player.setJerseyNom(jerseyNumber);

                                    cout << "\nJersey Number Updated Successfully!\n";
                                    break;
                                }

                                case 5: {
                                    int statusChoice;
                                    string status;

                                    cout << "\n========== PLAYER STATUS ==========\n";
                                    cout << "1. Active\n";
                                    cout << "2. Injured\n";
                                    cout << "3. Suspended\n";
                                    cout << "4. Inactive\n";
                                    cout << "5. Transferred\n";
                                    cout << "6. Retired\n";
                                    cout << "0. Cancel\n";
                                    cout << "Choice ==> ";

                                    cin >> statusChoice;

                                    switch (statusChoice) {
                                        case 1: status = "Active"; break;
                                        case 2: status = "Injured"; break;
                                        case 3: status = "Suspended"; break;
                                        case 4: status = "Inactive"; break;
                                        case 5: status = "Transferred"; break;
                                        case 6: status = "Retired"; break;

                                        case 0:
                                            cout << "\nStatus Update Cancelled.\n";
                                            break;

                                        default:
                                            cout << "\nInvalid Status Option!\n";
                                            break;
                                    }

                                    if (statusChoice >= 1 && statusChoice <= 6) {
                                        player.setPlayerStatus(status);
                                        cout << "\nPlayer Status Updated Successfully!\n";
                                    }

                                    break;

                                }

                            case 0:
                                cout << "\nUpdate Cancelled.\n";
                                break;

                            default:
                                cout << "\nInvalid Option!\n";
                        }

                        break;
                    }
                }

                if (!found) {
                    cout << "\nPlayer Not Found!\n";
                }

                break;
            }

            // DISPLAY PLAYER
            case 3: {

                if (league.getTeams().empty()) {
                    cout << "\nNo Teams Registered.\n";
                    break;
                }

                int teamChoice;

                for (int i = 0; i < league.getTeams().size(); i++) {
                    cout << i + 1 << ". "
                         << league.getTeams()[i].getTeamName()
                         << endl;
                }

                cout << "\nSelect Team: ";
                cin >> teamChoice;

                teamChoice--;

                if (teamChoice < 0 ||
                    teamChoice >= league.getTeams().size()) {

                    cout << "\nInvalid Team Selection!\n";
                    break;
                }

                int playerID;
                bool found = false;

                cout << "\nEnter Player ID: ";
                cin >> playerID;

                for (Player& player :
                     league.getTeams()[teamChoice].getPlayers()) {

                    if (player.getIdNom() == playerID) {
                        player.Display();
                        found = true;
                        break;
                    }
                }

                if (!found) {
                    cout << "\nPlayer Not Found!\n";
                }

                break;
            }

            // CHECK ELIGIBILITY
            case 4: {

                int teamChoice;
                int playerID;
                bool found = false;

                if (league.getTeams().empty()) {
                    cout << "\nNo Teams Registered.\n";
                    break;
                }

                for (int i = 0; i < league.getTeams().size(); i++) {
                    cout << i + 1 << ". "
                         << league.getTeams()[i].getTeamName()
                         << endl;
                }

                cout << "\nSelect Team: ";
                cin >> teamChoice;

                teamChoice--;

                if (teamChoice < 0 ||
                    teamChoice >= league.getTeams().size()) {

                    cout << "\nInvalid Team Selection!\n";
                    break;
                }

                cout << "Player ID: ";
                cin >> playerID;

                for (Player& player :
                     league.getTeams()[teamChoice].getPlayers()) {

                    if (player.getIdNom() == playerID) {

                        if (player.isEligible()) {
                            cout << "\nPlayer Is Eligible.\n";
                        }
                        else {
                            cout << "\nPlayer Is Not Eligible.\n";
                        }

                        found = true;
                        break;
                    }
                }

                if (!found) {
                    cout << "\nPlayer Not Found!\n";
                }

                break;
            }

            case 0:
                cout << "\nReturning to Main Menu...\n";
                break;

            default:
                cout << "\nInvalid Option!\n";
        }
    }
}


void coachManagement(FootballLeague& league) {

    int choice = -1;

    while (choice != 0) {

        cout << "\n========== COACH MANAGEMENT ==========\n";
        cout << "1. Register Coach\n";
        cout << "2. Display Coach\n";
        cout << "3. Update Experience\n";
        cout << "0. Back\n";
        cout << "======================================\n";
        cout << "Choice ==> ";

        cin >> choice;

        switch (choice) {

            // REGISTER COACH
            case 1: {

                if (league.getTeams().empty()) {
                    cout << "\nNo Teams Registered.\n";
                    break;
                }

                cout << "\n========== REGISTER COACH ==========\n";

                for (int i = 0; i < league.getTeams().size(); i++) {
                    cout << i + 1 << ". "
                         << league.getTeams()[i].getTeamName()
                         << endl;
                }

                int teamChoice;

                cout << "\nSelect Team: ";
                cin >> teamChoice;

                teamChoice--;

                if (teamChoice < 0 ||
                    teamChoice >= league.getTeams().size()) {

                    cout << "\nInvalid Team Selection!\n";
                    break;
                }

                int id, age, experience;
                string name, gender, qualification, role;

                cout << "\nCoach ID: ";
                cin >> id;

                cin.ignore();

                cout << "Coach Name: ";
                getline(cin, name);

                cout << "Age: ";
                cin >> age;

                cin.ignore();

                cout << "Gender: ";
                getline(cin, gender);

                cout << "Years Experience: ";
                cin >> experience;

                // QUALIFICATION
                int qualChoice;

                cout << "\n========== COACH QUALIFICATION ==========\n";
                cout << "1. Level 1\n";
                cout << "2. Level 2\n";
                cout << "3. Level 3\n";
                cout << "Choice ==> ";

                cin >> qualChoice;

                switch (qualChoice) {
                    case 1: qualification = "Level 1"; break;
                    case 2: qualification = "Level 2"; break;
                    case 3: qualification = "Level 3"; break;

                    default:
                        cout << "\nInvalid Qualification Option!\n";
                        break;
                }

                if (qualChoice < 1 || qualChoice > 3) {
                    break;
                }

                // COACHING ROLE
                int roleChoice;

                cout << "\n========== COACHING ROLE ==========\n";
                cout << "1. Head Coach\n";
                cout << "2. Assistant Coach\n";
                cout << "3. Goalkeeping Coach\n";
                cout << "Choice ==> ";

                cin >> roleChoice;

                switch (roleChoice) {
                    case 1: role = "Head Coach"; break;
                    case 2: role = "Assistant Coach"; break;
                    case 3: role = "Goalkeeping Coach"; break;

                    default:
                        cout << "\nInvalid Coaching Role Option!\n";
                        break;
                }

                if (roleChoice < 1 || roleChoice > 3) {
                    break;
                }

                try {

                    Coach coach(id, name, age, gender, qualification, role, experience);

                    coach.setTeam(&league.getTeams()[teamChoice]);
                    

                    league.getTeams()[teamChoice].addCoach(coach);

                    cout << "\nCoach Registered Successfully!\n";

                }
                catch (const KPFLExceptions& e) {
                    cout << e.getMessage() << endl;
                }

                break;
            }

            // DISPLAY COACH
            case 2: {

                if (league.getTeams().empty()) {
                    cout << "\nNo Teams Registered.\n";
                    break;
                }

                cout << "\n========== SELECT TEAM ==========\n";

                for (int i = 0; i < league.getTeams().size(); i++) {
                    cout << i + 1 << ". "
                         << league.getTeams()[i].getTeamName()
                         << endl;
                }

                int teamChoice;

                cout << "\nSelect Team: ";
                cin >> teamChoice;

                teamChoice--;

                if (teamChoice < 0 ||
                    teamChoice >= league.getTeams().size()) {

                    cout << "\nInvalid Team Selection!\n";
                    break;
                }

                vector<Coach>& coaches =
                    league.getTeams()[teamChoice].getCoaches();

                if (coaches.empty()) {
                    cout << "\nThis Team Has No Registered Coaches.\n";
                    break;
                }

                int coachID;
                bool found = false;

                cout << "\nEnter Coach ID: ";
                cin >> coachID;

                for (Coach& coach : coaches) {

                    if (coach.getIdNom() == coachID) {

                        coach.Display();
                        found = true;
                        break;
                    }
                }

                if (!found) {
                    cout << "\nCoach Not Found!\n";
                }

                break;
            }

            // UPDATE EXPERIENCE
            case 3: {

                if (league.getTeams().empty()) {
                    cout << "\nNo Teams Registered.\n";
                    break;
                }

                cout << "\n========== SELECT TEAM ==========\n";

                for (int i = 0; i < league.getTeams().size(); i++) {
                    cout << i + 1 << ". "
                         << league.getTeams()[i].getTeamName()
                         << endl;
                }

                int teamChoice;

                cout << "\nSelect Team: ";
                cin >> teamChoice;

                teamChoice--;

                if (teamChoice < 0 ||
                    teamChoice >= league.getTeams().size()) {

                    cout << "\nInvalid Team Selection!\n";
                    break;
                }

                vector<Coach>& coaches =
                    league.getTeams()[teamChoice].getCoaches();

                if (coaches.empty()) {
                    cout << "\nThis Team Has No Registered Coaches.\n";
                    break;
                }

                int coachID;
                bool found = false;

                cout << "\nEnter Coach ID: ";
                cin >> coachID;

                for (Coach& coach : coaches) {

                    if (coach.getIdNom() == coachID) {

                        found = true;

                        int experience;

                        cout << "\nCurrent Experience: "
                             << coach.getYearsExperience()
                             << " Years\n";

                        cout << "Enter New Years of Experience: ";
                        cin >> experience;

                        if (experience < 0) {
                            cout << "\nInvalid Years of Experience!\n";
                            break;
                        }

                        coach.setYearsExperience(experience);

                        cout << "\nCoach Experience Updated Successfully!\n";

                        break;
                    }
                }

                if (!found) {
                    cout << "\nCoach Not Found!\n";
                }

                break;
            }

            case 0:
                cout << "\nReturning to Main Menu...\n";
                break;

            default:
                cout << "\nInvalid Option!\n";
        }
    }
}


void officialMenu(FootballLeague& league)
{
    int choice;

    do
    {
        cout << "\n========== MATCH OFFICIALS ==========";
        cout << "\n1. Register Official";
        cout << "\n2. Assign Official";
        cout << "\n3. Display Official";
        cout << "\n4. View Assigned Fixtures";
        cout << "\n0. Back";
        cout << "\nChoice ==> ";

        cin >> choice;

        switch(choice)
        {
            case 1:
            {
                int id, age, experience, available;
                string name, gender, role, rank;

                cout << "\nOfficial ID: ";
                cin >> id;

                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                cout << "Official Name: ";
                getline(cin, name);

                cout << "Age: ";
                cin >> age;

                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                cout << "Gender: ";
                getline(cin, gender);

                cout << "Officiating Role: ";
                getline(cin, role);

                cout << "Rank: ";
                getline(cin, rank);

                cout << "Availability (1 = Available, 0 = Unavailable): ";
                cin >> available;

                cout << "Years of Experience: ";
                cin >> experience;

                if(id <= 0 || age < 0 || experience < 0 ||
                   (available != 0 && available != 1))
                {
                    cout << "\nInvalid information entered.\n";
                    break;
                }

                MatchOfficial official(id, name, age, gender,
                                       role, rank, available == 1,
                                       experience);

                officials.push_back(official);

                cout << "\nOfficial registered successfully!\n";
                break;
            }

            case 2:
            {
                if(officials.empty() || fixtures.empty())
                {
                    cout << "\nOfficials or fixtures are unavailable.\n";
                    break;
                }

                int officialChoice, fixtureChoice;

                cout << "\nREGISTERED OFFICIALS\n";

                for(int i = 0; i < officials.size(); i++)
                {
                    cout << "\n" << i + 1 << ". "
                         << officials[i].getFullName();
                }

                cout << "\nSelect Official: ";
                cin >> officialChoice;

                if(officialChoice < 1 || officialChoice > officials.size())
                {
                    cout << "\nInvalid official selection.\n";
                    break;
                }

                cout << "\nAVAILABLE FIXTURES\n";

                for(int i = 0; i < fixtures.size(); i++)
                {
                    cout << "\n" << i + 1
                         << ". Fixture ID: "
                         << fixtures[i].getFixtureID();
                }

                cout << "\nSelect Fixture: ";
                cin >> fixtureChoice;

                if(fixtureChoice < 1 || fixtureChoice > fixtures.size())
                {
                    cout << "\nInvalid fixture selection.\n";
                    break;
                }

                if(!officials[officialChoice - 1].canAssignFixture())
                {
                    cout << "\nOfficial is unavailable.\n";
                    break;
                }

                commissioner.assignOfficial(
                    fixtures[fixtureChoice - 1],
                    officials[officialChoice - 1]
                );

                cout << "\nOfficial assigned successfully!\n";
                break;
            }

            case 3:
            {
                if(officials.empty())
                {
                    cout << "\nNo registered officials.\n";
                    break;
                }

                for(int i = 0; i < officials.size(); i++)
                {
                    cout << "\nOfficial " << i + 1;
                    officials[i].Display();
                    cout << "\n";
                }

                break;
            }

            case 4:
            {
                int officialChoice;

                if(officials.empty())
                {
                    cout << "\nNo registered officials.\n";
                    break;
                }

                for(int i = 0; i < officials.size(); i++)
                {
                    cout << "\n" << i + 1 << ". "
                         << officials[i].getFullName();
                }

                cout << "\nSelect Official: ";
                cin >> officialChoice;

                if(officialChoice < 1 || officialChoice > officials.size())
                {
                    cout << "\nInvalid selection.\n";
                    break;
                }

                const vector<const Fixture*>& assigned =
                    officials[officialChoice - 1].getAssignedFixtures();

                if(assigned.empty())
                {
                    cout << "\nNo assigned fixtures.\n";
                    break;
                }

                for(const Fixture* fixture : assigned)
                {
                    cout << "\nFixture ID: " << fixture->getFixtureID();
                    cout << "\nStatus: " << fixture->getFixtureStatus();
                    cout << "\nDate: ";
                    fixture->getFixtureDate();
                    cout << "\n";
                }

                break;
            }

            case 0:
                cout << "\nReturning to Main Menu...\n";
                break;

            default:
                cout << "\nInvalid choice.\n";
        }

    } while(choice != 0);
}



void fixtureManagementMenu(FootballLeague& league)
{
    int choice;

    do
    {
        cout << "\n========= FIXTURE MANAGEMENT =========";
        cout << "\n1. Schedule Fixture";
        cout << "\n2. Assign Official";
        cout << "\n3. Record Result";
        cout << "\n4. Complete Fixture";
        cout << "\n0. Back";
        cout << "\nChoice ==> ";

        cin >> choice;

        switch(choice)
        {
            case 1:
            {
                vector<FootballTeam> teams = league.getTeams();

                if(teams.size() < 2)
                {
                    cout << "\nAt least two teams are required.\n";
                    break;
                }

                cout << "\nREGISTERED TEAMS\n";

                for(int i = 0; i < teams.size(); i++)
                {
                    cout << "\n" << i + 1 << ". "
                         << teams[i].getTeamName();
                }

                int home, away;

                cout << "\nSelect Home Team: ";
                cin >> home;

                cout << "Select Away Team: ";
                cin >> away;

                if(home < 1 || home > teams.size() ||
                   away < 1 || away > teams.size() || home == away)
                {
                    cout << "\nInvalid team selection.\n";
                    break;
                }

                int id, day, month, year;
                int hours, minutes, seconds;

                cout << "\nFixture ID: ";
                cin >> id;

                cout << "Day: ";
                cin >> day;

                cout << "Month: ";
                cin >> month;

                cout << "Year: ";
                cin >> year;

                cout << "Hours: ";
                cin >> hours;

                cout << "Minutes: ";
                cin >> minutes;

                cout << "Seconds: ";
                cin >> seconds;

                Fixture proposed;

                proposed.setFixtureID(id);
                proposed.setFixtureDate(day, month, year);
                proposed.setFixtureTime(hours, minutes, seconds);
                proposed.setFixtureStatus("Scheduled");

                if(league.scheduleFixture(proposed,
                    teams[home - 1], teams[away - 1]))
                {
                    vector<Fixture> saved = league.getFixtures();
                    fixtures.push_back(saved.back());

                    cout << "\nFixture scheduled successfully!\n";
                }
                else
                {
                    cout << "\nFixture could not be scheduled.\n";
                }

                break;
            }

            case 2:
            {
                if(officials.empty() || fixtures.empty())
                {
                    cout << "\nOfficials or fixtures are unavailable.\n";
                    break;
                }

                int officialChoice, fixtureChoice;

                for(int i = 0; i < officials.size(); i++)
                {
                    cout << "\n" << i + 1 << ". "
                         << officials[i].getFullName();
                }

                cout << "\nSelect Official: ";
                cin >> officialChoice;

                if(officialChoice < 1 || officialChoice > officials.size())
                {
                    cout << "\nInvalid official selection.\n";
                    break;
                }

                for(int i = 0; i < fixtures.size(); i++)
                {
                    cout << "\n" << i + 1
                         << ". Fixture ID: "
                         << fixtures[i].getFixtureID();
                }

                cout << "\nSelect Fixture: ";
                cin >> fixtureChoice;

                if(fixtureChoice < 1 || fixtureChoice > fixtures.size())
                {
                    cout << "\nInvalid fixture selection.\n";
                    break;
                }

                if(!officials[officialChoice - 1].canAssignFixture())
                {
                    cout << "\nOfficial is unavailable.\n";
                    break;
                }

                commissioner.assignOfficial(
                    fixtures[fixtureChoice - 1],
                    officials[officialChoice - 1]
                );

                cout << "\nOfficial assigned successfully!\n";
                break;
            }

            case 3:
            {
                cout << "\nTo record the result, the MatchResult "
                     << "class methods are needed.\n";
                break;
            }

            case 4:
            {
                if(fixtures.empty())
                {
                    cout << "\nNo fixtures available.\n";
                    break;
                }

                int fixtureChoice;

                for(int i = 0; i < fixtures.size(); i++)
                {
                    cout << "\n" << i + 1
                         << ". Fixture ID: "
                         << fixtures[i].getFixtureID();
                }

                cout << "\nSelect Fixture: ";
                cin >> fixtureChoice;

                if(fixtureChoice < 1 || fixtureChoice > fixtures.size())
                {
                    cout << "\nInvalid fixture selection.\n";
                    break;
                }

                try
                {
                    fixtures[fixtureChoice - 1].completeFixture();
                    cout << "\nFixture completed successfully!\n";
                }
                catch(...)
                {
                    cout << "\nFixture could not be completed. "
                         << "Check that an official has been assigned.\n";
                }

                break;
            }

            case 0:
                cout << "\nReturning to Main Menu...\n";
                break;

            default:
                cout << "\nInvalid choice.\n";
        }

    } while(choice != 0);
}



void commissionerMenu(FootballLeague& league)
{
    int choice;

    do
    {
        cout << "\n========== LEAGUE COMMISSIONER ==========";
        cout << "\n1. Approve Team";
        cout << "\n2. Suspend Team";
        cout << "\n3. Reinstate Team";
        cout << "\n4. Schedule Fixture";
        cout << "\n5. Assign Official";
        cout << "\n6. Inspect Match Preparation";
        cout << "\n0. Back";
        cout << "\nChoice ==> ";

        cin >> choice;

        switch(choice)
        {
            case 1:
            case 2:
            case 3:
            {
                vector<FootballTeam> teams = league.getTeams();

                if(teams.empty())
                {
                    cout << "\nNo registered teams available.\n";
                    break;
                }

                cout << "\nREGISTERED TEAMS\n";

                for(int i = 0; i < teams.size(); i++)
                {
                    cout << "\n" << i + 1 << ". "
                         << teams[i].getTeamName();
                }

                int teamChoice;

                cout << "\nSelect Team: ";
                cin >> teamChoice;

                if(teamChoice < 1 || teamChoice > teams.size())
                {
                    cout << "\nInvalid team selection.\n";
                    break;
                }

                try
                {
                    if(choice == 1)
                    {
                        commissioner.approveTeam(teams[teamChoice - 1]);
                        cout << "\nTeam approval completed.\n";
                    }
                    else if(choice == 2)
                    {
                        commissioner.suspendTeam(teams[teamChoice - 1]);
                        cout << "\nTeam suspended successfully.\n";
                    }
                    else if(choice == 3)
                    {
                        commissioner.reinstateTeam(teams[teamChoice - 1]);
                        cout << "\nTeam reinstated successfully.\n";
                    }
                }
                catch(...)
                {
                    cout << "\nTeam could not be approved.\n";
                }

                cout << "\nNote: The league returns a copy of its teams, "
                     << "so these changes are not saved to the original team.\n";

                break;
            }

            case 4:
            {
                if(fixtures.empty())
                {
                    cout << "\nNo fixtures available.\n";
                    break;
                }

                int fixtureChoice;

                for(int i = 0; i < fixtures.size(); i++)
                {
                    cout << "\n" << i + 1
                         << ". Fixture ID: "
                         << fixtures[i].getFixtureID();
                }

                cout << "\nSelect Fixture: ";
                cin >> fixtureChoice;

                if(fixtureChoice < 1 || fixtureChoice > fixtures.size())
                {
                    cout << "\nInvalid fixture selection.\n";
                    break;
                }

                try
                {
                    commissioner.scheduleFixture(
                        fixtures[fixtureChoice - 1]
                    );

                    cout << "\nCommissioner scheduled the fixture.\n";
                }
                catch(...)
                {
                    cout << "\nFixture could not be scheduled.\n";
                }

                break;
            }

            case 5:
            {
                if(officials.empty() || fixtures.empty())
                {
                    cout << "\nOfficials or fixtures are unavailable.\n";
                    break;
                }

                int officialChoice, fixtureChoice;

                for(int i = 0; i < officials.size(); i++)
                {
                    cout << "\n" << i + 1 << ". "
                         << officials[i].getFullName();
                }

                cout << "\nSelect Official: ";
                cin >> officialChoice;

                if(officialChoice < 1 || officialChoice > officials.size())
                {
                    cout << "\nInvalid official selection.\n";
                    break;
                }

                for(int i = 0; i < fixtures.size(); i++)
                {
                    cout << "\n" << i + 1
                         << ". Fixture ID: "
                         << fixtures[i].getFixtureID();
                }

                cout << "\nSelect Fixture: ";
                cin >> fixtureChoice;

                if(fixtureChoice < 1 || fixtureChoice > fixtures.size())
                {
                    cout << "\nInvalid fixture selection.\n";
                    break;
                }

                if(!officials[officialChoice - 1].canAssignFixture())
                {
                    cout << "\nOfficial is unavailable.\n";
                    break;
                }

                commissioner.assignOfficial(
                    fixtures[fixtureChoice - 1],
                    officials[officialChoice - 1]
                );

                cout << "\nOfficial assigned successfully!\n";
                break;
            }

            case 6:
            {
                if(fixtures.empty())
                {
                    cout << "\nNo fixtures available for inspection.\n";
                    break;
                }

                for(int i = 0; i < fixtures.size(); i++)
                {
                    cout << "\nFixture ID: "
                         << fixtures[i].getFixtureID();

                    cout << "\nDate: ";
                    fixtures[i].getFixtureDate();

                    cout << "\nTime: ";
                    fixtures[i].getFixtureTime();

                    cout << "\nStatus: "
                         << fixtures[i].getFixtureStatus();

                    cout << "\n";
                }

                break;
            }

            case 0:
                cout << "\nReturning to Main Menu...\n";
                break;

            default:
                cout << "\nInvalid choice.\n";
        }

    } while(choice != 0);
}

void stadiumMenu(){
    cout << "\n========== STADIUM MANAGEMENT ==========";
    cout << "\n1. Add Stadium";
    cout << "\n2. Display Stadium";
    cout << "\n3. Check Capacity";
    cout << "\n4. View Scheduled Fixtures";
    cout << "\n0. Back";
    cout << "\nChoice ==> ";
}

void spectatorMenu(){
    cout << "\n========== SPECTATOR MANAGEMENT ==========";
    cout << "\n1. Register Spectator";
    cout << "\n2. Purchase Ticket";
    cout << "\n3. Display Spectator";
    cout << "\n4. Add Funds";
    cout << "\n0. Back";
    cout << "\nChoice ==> ";
}

void stadiumShopMenu(){
    cout << "\n============ STADIUM SHOP ============\n";
    cout << "1. Add Product\n";
    cout << "2. Display Inventory\n";
    cout << "3. Purchase Product\n";
    cout << "0. Back\n";
    cout << "\nChoice ==> ";
}

void resultsMenu(){
    cout << "\n========== MATCH RESULTS ==========";
    cout << "\n1. Enter Match Result";
    cout << "\n2. Display Result";
    cout << "\n3. View League Standings";
    cout << "\n0. Back";
    cout << "\nChoice ==> ";
}

void footballLeagueMenu(){
    cout << "\n========== FOOTBALL LEAGUE ==========";
    cout << "\n1. Register Team";
    cout << "\n2. Create Fixture";
    cout << "\n3. Record League Result";
    cout << "\n4. View Standings";
    cout << "\n5. Display Teams";
    cout << "\n6. Display Fixtures";
    cout << "\n0. Back";
    cout << "\nChoice ==> ";
}

void testExceptions() {

    int choice;

    do {
        cout << "\n========== TEST EXCEPTIONS ==========";
        cout << "\n1. UnderageException";
        cout << "\n2. DuplicateRegistrationException";
        cout << "\n3. TeamNotEligibleException";
        cout << "\n4. SchedulingConflictException";
        cout << "\n5. FixtureIncompleteException";
        cout << "\n6. InvalidScoreException";
        cout << "\n7. InsufficientPaymentException";
        cout << "\n8. InsufficientStockException";
        cout << "\n9. CapacityExceededException";
        cout << "\n10. DataFileException";
        cout << "\n0. Back";
        cout << "\nChoice ==> ";
        cin >> choice;

        try {

            switch (choice) {

                case 1:
                    throw UnderageException();

                case 2:
                    throw DuplicateRegistrationException();

                case 3:
                    throw TeamNotEligibleException();

                case 4:
                    throw SchedulingConflictException();

                case 5:
                    throw FixtureIncompleteException();

                case 6:
                    throw InvalidScoreException();

                case 7:
                    throw InsufficientPaymentException();

                case 8:
                    throw InsufficientStockException();

                case 9:
                    throw CapacityExceededException();

                case 10:
                    throw DataFileException();

                case 0:
                    cout << "\nReturning to previous menu...\n";
                    break;

                default:
                    cout << "\nInvalid choice. Try again.\n";
            }

        }
        catch (const KPFLExceptions& e) {
            cout << "\nException successfully caught!";
            cout << "\nError Message: " << e.getMessage() << "\n";
            Sleep(3000);
        }

    } while (choice != 0);
}

void fileManagement(FootballLeague& league){
    int choice;
    FileManager fileManager("data");

    do {
        cout << "\n===== FILE MANAGER =====\n";
        cout << "\n 1. Save Teams";
        cout << "\n 2. Load Teams";
        cout << "\n 3. Save Fixtures";
        cout << "\n 4. Load Fixtures";
        cout << "\n 5. Save People";
        cout << "\n 6. Load People";
        cout << "\n 0. Back";
        cout << "\nChoice ==> ";
        cin >> choice;

        try {
            switch(choice){
                case 1: {
                    vector<FootballTeam>& teams = league.getTeams();
                    vector<Persistable*> teamRecords;
                    teamRecords.reserve(teams.size());

                    for (FootballTeam& team : teams)
                        teamRecords.push_back(&team);

                    fileManager.saveTeams(teamRecords.data(), teamRecords.size());
                    cout << "\nTeams saved successfully.\n";
                    break;
                }

                case 2: {
                    unique_ptr<FootballTeam> teams[100];
                    int count = fileManager.loadTeams(teams, 100);

                    league.getTeams().clear();
                    for (int i = 0; i < count; ++i)
                        league.registerTeam(*teams[i]);

                    cout << "\n" << count << "Team(s) loaded successfully.\n";
                    break;
                }

                case 3: {
                    vector<Fixture> fixtures = league.getFixtures();
                    vector<Persistable*> fixtureRecords;
                    fixtureRecords.reserve(fixtures.size());

                    for (Fixture& fixture : fixtures)
                        fixtureRecords.push_back(&fixture);

                    fileManager.saveFixtures(fixtureRecords.data(), fixtureRecords.size());
                    cout << "\nFixtures saved successfully.\n";
                    break;
                }

                case 4: {
                    unique_ptr<Fixture> fixtures[100];
                    int count = fileManager.loadFixtures(fixtures, 100);
                    league.getFixtures().clear();

                    for (int i = 0; i < count; ++i)
                        league.getFixtures().push_back(*fixtures[i]);

                    cout << "\n" << count << "Fixture(s) loaded successfully.\n";
                    break;
                }

                case 5: {
                    int count = 0;

                    for (FootballTeam& team : league.getTeams()) {
                        for (Player& player : team.getPlayers()) {
                            string record = "Player|" +
                                to_string(player.getIdNom()) + "|" +
                                player.getFullName() + "|" +
                                to_string(player.getAge()) + "|" +
                                player.getGender() + "|" +
                                player.getPositionOnField() + "|" +
                                to_string(player.getJerseyNom());

                            fileManager.appendLine(FileManager::PEOPLE_FILE, record);
                            ++count;
                        }

                        for (Coach& coach : team.getCoaches()) {
                            string record = "Coach|" +
                                to_string(coach.getIdNom()) + "|" +
                                coach.getFullName() + "|" +
                                to_string(coach.getAge()) + "|" +
                                coach.getGender() + "|" +
                                coach.getQualification() + "|" +
                                to_string(coach.getYearsExperience());

                            fileManager.appendLine(FileManager::PEOPLE_FILE, record);
                            ++count;
                        }
                    }

                    cout << "\n" << count << " person record(s) saved successfully.\n";
                    break;
                }

                case 6: {
                    ifstream input(string("data/") + FileManager::PEOPLE_FILE);
                    if (!input)
                        throw DataFileException();
                    string line;
                    int count = 0;
                    cout << "\nPeople Records:\n";
                    while (getline(input, line)) {
                        if (!line.empty()){
                            cout << line << '\n';
                            ++count;
                        }
                    }
                    cout << count << " person record(s) loaded.\n";
                    break;
                }

                case 0:
                    cout << "\nReturning to previous menu...\n";
                    break;

                default:
                    cout << "\nInvalid choice. Try again.\n";
            }
        }
        catch (const KPFLExceptions& exception){
            cout << "\nFile operation failed: "
                 << exception.getMessage() << '\n';
        }
    } while (choice != 0);
}

int displayMainMenu(){
    int choice;

    cout << "\n==================================================";
    cout << "\n      KINGSTON PREMIER FOOTBALL LEAGUE (KPFL)";
    cout << "\n==================================================";
    cout << "\n 1. Team Management";
    cout << "\n 2. Player Management";
    cout << "\n 3. Coach Management";
    cout << "\n 4. Match Officials";
    cout << "\n 5. Fixture Management";
    cout << "\n 6. League Commissioner";
    cout << "\n 7. Match Results";
    cout << "\n 8. Stadium Management";
    cout << "\n 9. Stadium Shop";
    cout << "\n10. Spectator Management";
    cout << "\n11. View League Summary";
    cout << "\n12. Test Exceptions";
    cout << "\n 0. Exit";
    cout << "\n==================================================";
    cout << "\nEnter option: ";
    cin >> choice;

    return choice;
}

int generateRandomID() {
    return (rand() % 10000) + 1;
}
