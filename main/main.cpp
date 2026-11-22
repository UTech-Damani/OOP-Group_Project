#include <iostream>

#include <string>
#include <vector>
#include <ctype.h>
#include <cstdlib>
#include <ctime>

#include "universal/KPFL.h"

using namespace std;

int displayMainMenu();
int generateRandomID();
void teamManagement(FootballLeague& league);
void playerManagement(FootballLeague& league);
void coachManagement(FootballLeague& league);

int main()
{
    srand(time(NULL));

    FootballLeague league;

    cout << "Za Wurldo!" << endl;

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
            
            break;

        case 5:
            
            break;

        case 6:
            
            break;

        case 7:
            
            break;

        case 8:

            break;

        case 9:

            break;

        case 10:
            
            break;

        case 11:
            
            break;

        case 12:
            
            break;

        case 0:
            
            break;
        
        default:
            break;
    }

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

void officialMenu(){
    cout << "\n========== MATCH OFFICIALS ==========";
    cout << "\n1. Register Official";
    cout << "\n2. Assign Official";
    cout << "\n3. Display Official";
    cout << "\n4. View Assigned Fixtures";
    cout << "\n0. Back";
    cout << "\nChoice ==> ";
}

void fixtureManagementMenu(){
    cout << "\n========= FIXTURE MANAGEMENT =========\n";
    cout << "1. Schedule Fixture\n";
    cout << "2. Assign Official\n";
    cout << "3. Record Result\n";
    cout << "4. Complete Fixture\n";
    cout << "0. Back\n";
    cout << "\nChoice ==> ";
}

void commissionerMenu(){
    cout << "\n========== LEAGUE COMMISSIONER ==========";
    cout << "\n1. Approve Team";
    cout << "\n2. Suspend Team";
    cout << "\n3. Reinstate Team";
    cout << "\n4. Schedule Fixture";
    cout << "\n5. Assign Official";
    cout << "\n6. Inspect Match Preparation";
    cout << "\n0. Back";
    cout << "\nChoice ==> ";
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

void exceptionMenu(){
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