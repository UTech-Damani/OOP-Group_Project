#include <iostream>
#include <windows.h>

#include <string>
#include <vector>
#include <ctype.h>
#include <cstdlib>
#include <ctime>
#include <limits>

#include "universal/KPFL.h"
#include "universal/FileManager.h"

using namespace std;

vector<MatchOfficial> officials;
vector<Spectator> spectators;
vector<Stadium> stadiums;
LeagueCommissioner commissioner;


int displayMainMenu();
int generateRandomID();
bool readInt(int& value);
bool readDouble(double& value);
void teamManagement(FootballLeague& league);
void playerManagement(FootballLeague& league);
void coachManagement(FootballLeague& league);
void testExceptions();
void officialMenu(FootballLeague& league);
void fixtureManagementMenu(FootballLeague& league);
void commissionerMenu(FootballLeague& league);
void resultsMenu(FootballLeague& league);
void stadiumMenu(FootballLeague& league);
void stadiumShopMenu();
void spectatorManagement();
void footballLeagueMenu(FootballLeague& league);
void fileManagement(FootballLeague& league);

bool readInt(int& value)
{
    cin >> value;
    if (!cin) {
        if (cin.eof()) {
            value = 0;
            return false;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        value = 0;
        return false;
    }
    return true;
}

bool readDouble(double& value)
{
    cin >> value;
    if (!cin) {
        if (cin.eof()) {
            value = 0.0;
            return false;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        value = 0.0;
        return false;
    }
    return true;
}

int main()
{
    srand(time(NULL));

    Date startDate(1, 12, 2026);
    
    Date endDate(31, 12, 2027);
    
    FootballLeague league(1,"Kingston Premier Football League","2026 Season",startDate,endDate,0,"Active");
    int choice;

    cout << "Za Wurldo!" << endl;

    do{
        choice = displayMainMenu();

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
                officialMenu(league);
                break;

            case 5:
                fixtureManagementMenu(league);
                break;

            case 6:
                commissionerMenu(league);
                break;

            case 7:
                resultsMenu(league);
                break;

            case 8:
                stadiumMenu(league);
                break;

            case 9:
                stadiumShopMenu();
                break;

            case 10:
                spectatorManagement();
                break;

            case 11:
                footballLeagueMenu(league);
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
        cout << "\n 6. Update Team"; // Need to do
        cout << "\n 7. Search Team"; // Need to do
        cout << "\n 0. Back";
        cout << "\n==================================================";
        cout << "\nChoice ==> ";
        
        if (!readInt(choice)) {
            cout << "\nInvalid choice. Enter a number.\n";
            continue;
        }
        
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
                
                for(size_t i = 0; i < league.getTeams().size(); ++i){
                    cout << i + 1 << ". "
                    << league.getTeams()[i].getTeamName()
                    << endl;
                }
                
                int teamChoice;
                int teamCount = league.getTeams().size();

                do {
                    cout << "\nSelect Team: ";
                    cin >> teamChoice;
                    teamChoice--;

                    if (teamChoice < 0 || teamChoice >= teamCount)
                    {
                        cout << "\nInvalid Team Selection!\n";
                    }

                } while (teamChoice < 0 || teamChoice >= teamCount);
                

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

                for(size_t i = 0; i < league.getTeams().size(); ++i){
                    cout << i + 1 << ". "
                    << league.getTeams()[i].getTeamName()
                    << endl;
                }
                
                int teamChoice;
                int teamCount = league.getTeams().size();

                do {
                    cout << "\nSelect Team: ";
                    cin >> teamChoice;
                    teamChoice--;

                    if (teamChoice < 0 || teamChoice >= teamCount)
                    {
                        cout << "\nInvalid Team Selection!\n";
                    }

                } while (teamChoice < 0 || teamChoice >= teamCount);
    
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
                
                for(size_t i = 0; i < league.getTeams().size(); ++i){
                    cout << i + 1 << ". "
                    << league.getTeams()[i].getTeamName()
                    << endl;
                }
                
                int teamChoice;
                int teamCount = league.getTeams().size();

                do {
                    cout << "\nSelect Team: ";
                    cin >> teamChoice;
                    teamChoice--;

                    if (teamChoice < 0 || teamChoice >= teamCount)
                    {
                        cout << "\nInvalid Team Selection!\n";
                    }

                } while (teamChoice < 0 || teamChoice >= teamCount);
                
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

            case 6: {
                if(league.getTeams().empty()){
                    cout << "\nNo Teams Registered.\n";
                    break;
                }

                int teamID;
                bool found = false;

                cout << "\nEnter Team ID: ";
                cin >> teamID;

                for(FootballTeam& team : league.getTeams()){
                    if(team.getTeamID() == teamID){

                        found = true;

                        string newName;
                        string newParish;

                        cin.ignore();

                        cout << "New Team Name: ";
                        getline(cin, newName);

                        cout << "New Parish: ";
                        getline(cin, newParish);

                        team.setTeamName(newName);
                        team.setParish(newParish);

                        cout << "\nTeam Updated Successfully!\n";
                        break;
                    }
                }

                if(!found){
                    cout << "\nTeam Not Found!\n";
                }
                break;
            }

            case 7: {
                if(league.getTeams().empty()){
                    cout << "\nNo Teams Registered.\n";
                    break;
                }

                int teamID;
                bool found = false;

                cout << "\nEnter Team ID: ";
                cin >> teamID;

                for(FootballTeam& team : league.getTeams()){
                    if(team.getTeamID() == teamID){

                        found = true;

                        cout << "\n========== TEAM FOUND ==========\n";
                        cout << "Team ID: "
                            << team.getTeamID() << endl;

                        cout << "Team Name: "
                            << team.getTeamName() << endl;

                        cout << "Parish: "
                            << team.getParish() << endl;

                        cout << "Status: "
                            << team.getTeamStatus() << endl;

                        cout << "Players: "
                            << team.getPlayers().size() << endl;

                        cout << "Coaches: "
                            << team.getCoaches().size() << endl;

                        break;
                    }
                }

                if(!found){
                    cout << "\nTeam Not Found!\n";
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
        cout << "5. Remove Player\n";
        cout << "0. Back\n";
        cout << "=======================================\n";
        cout << "Choice ==> ";
        
        if (!readInt(choice)) {
            cout << "\nInvalid choice. Enter a number.\n";
            continue;
        }

        switch (choice) {

            // REGISTER PLAYER
            case 1: {

                if (league.getTeams().empty()) {
                    cout << "\nNo Teams Registered.\n";
                    break;
                }

                cout << "\n========== REGISTER PLAYER ==========\n";

                for (size_t i = 0; i < league.getTeams().size(); ++i) {
                    cout << i + 1 << ". "
                         << league.getTeams()[i].getTeamName()
                         << endl;
                }

                int teamChoice;
                int teamCount = league.getTeams().size();

                do {
                    cout << "\nSelect Team: ";
                    cin >> teamChoice;
                    teamChoice--;

                    if (teamChoice < 0 || teamChoice >= teamCount)
                    {
                        cout << "\nInvalid Team Selection!\n";
                    }

                } while (teamChoice < 0 || teamChoice >= teamCount);

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

                int positionChoice;

                cout << "\n========== PLAYER POSITION ==========\n";
                cout << "1. Goalkeeper\n";
                cout << "2. Centre Back\n";
                cout << "3. Left Back\n";
                cout << "4. Right Back\n";
                cout << "5. Left Wing Back\n";
                cout << "6. Right Wing Back\n";
                cout << "7. Defensive Midfielder\n";
                cout << "8. Central Midfielder\n";
                cout << "9. Attacking Midfielder\n";
                cout << "10. Left Midfielder\n";
                cout << "11. Right Midfielder\n";
                cout << "12. Left Winger\n";
                cout << "13. Right Winger\n";
                cout << "14. Striker\n";
                cout << "15. Centre Forward\n";
                cout << "Choice ==> ";

                cin >> positionChoice;

                switch(positionChoice)
                {
                    case 1: position = "Goalkeeper"; break;
                    case 2: position = "Centre Back"; break;
                    case 3: position = "Left Back"; break;
                    case 4: position = "Right Back"; break;
                    case 5: position = "Left Wing Back"; break;
                    case 6: position = "Right Wing Back"; break;
                    case 7: position = "Defensive Midfielder"; break;
                    case 8: position = "Central Midfielder"; break;
                    case 9: position = "Attacking Midfielder"; break;
                    case 10: position = "Left Midfielder"; break;
                    case 11: position = "Right Midfielder"; break;
                    case 12: position = "Left Winger"; break;
                    case 13: position = "Right Winger"; break;
                    case 14: position = "Striker"; break;
                    case 15: position = "Centre Forward"; break;

                    default:
                        cout << "\nInvalid Position!\n";
                        break;
                }
                
                
                cout << "\nPosition Registered Successfully!\n";

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

                cout << "\n========== SELECT TEAM ==========\n";

                for (size_t i = 0; i < league.getTeams().size(); ++i) {
                    cout << i + 1 << ". "
                         << league.getTeams()[i].getTeamName()
                         << endl;
                }

                int teamChoice;
                int teamCount = league.getTeams().size();

                do {
                    cout << "\nSelect Team: ";
                    cin >> teamChoice;
                    teamChoice--;

                    if (teamChoice < 0 || teamChoice >= teamCount)
                    {
                        cout << "\nInvalid Team Selection!\n";
                    }

                } while (teamChoice < 0 || teamChoice >= teamCount);

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
                                if (!readInt(age) || age < league.getMinimumAge()) {
                                    cout << "Player must be at least " << league.getMinimumAge() << " years old.\n";
                                    break;
                                }
                                player.setAge(age);
                                cout << "\nAge Updated Successfully!\n";
                                break;
                            }

                            case 3: {
                                string position;
                                int positionChoice;

                                cout << "\n========== PLAYER POSITION ==========\n";
                                cout << "1. Goalkeeper\n";
                                cout << "2. Centre Back\n";
                                cout << "3. Left Back\n";
                                cout << "4. Right Back\n";
                                cout << "5. Left Wing Back\n";
                                cout << "6. Right Wing Back\n";
                                cout << "7. Defensive Midfielder\n";
                                cout << "8. Central Midfielder\n";
                                cout << "9. Attacking Midfielder\n";
                                cout << "10. Left Midfielder\n";
                                cout << "11. Right Midfielder\n";
                                cout << "12. Left Winger\n";
                                cout << "13. Right Winger\n";
                                cout << "14. Striker\n";
                                cout << "15. Centre Forward\n";
                                cout << "Choice ==> ";

                                cin >> positionChoice;

                                switch(positionChoice)
                                {
                                    case 1: position = "Goalkeeper"; break;
                                    case 2: position = "Centre Back"; break;
                                    case 3: position = "Left Back"; break;
                                    case 4: position = "Right Back"; break;
                                    case 5: position = "Left Wing Back"; break;
                                    case 6: position = "Right Wing Back"; break;
                                    case 7: position = "Defensive Midfielder"; break;
                                    case 8: position = "Central Midfielder"; break;
                                    case 9: position = "Attacking Midfielder"; break;
                                    case 10: position = "Left Midfielder"; break;
                                    case 11: position = "Right Midfielder"; break;
                                    case 12: position = "Left Winger"; break;
                                    case 13: position = "Right Winger"; break;
                                    case 14: position = "Striker"; break;
                                    case 15: position = "Centre Forward"; break;

                                    default:
                                        cout << "\nInvalid Position!\n";
                                        break;
                                }
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

                for (size_t i = 0; i < league.getTeams().size(); ++i) {
                    cout << i + 1 << ". "
                         << league.getTeams()[i].getTeamName()
                         << endl;
                }

                int teamChoice;
                int teamCount = league.getTeams().size();

                do {
                    cout << "\nSelect Team: ";
                    cin >> teamChoice;
                    teamChoice--;

                    if (teamChoice < 0 || teamChoice >= teamCount)
                    {
                        cout << "\nInvalid Team Selection!\n";
                    }

                } while (teamChoice < 0 || teamChoice >= teamCount);

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

                int playerID;
                bool found = false;

                if (league.getTeams().empty()) {
                    cout << "\nNo Teams Registered.\n";
                    break;
                }

                for (size_t i = 0; i < league.getTeams().size(); ++i) {
                    cout << i + 1 << ". "
                         << league.getTeams()[i].getTeamName()
                         << endl;
                }

                int teamChoice;
                int teamCount = league.getTeams().size();

                do {
                    cout << "\nSelect Team: ";
                    cin >> teamChoice;
                    teamChoice--;

                    if (teamChoice < 0 || teamChoice >= teamCount)
                    {
                        cout << "\nInvalid Team Selection!\n";
                    }

                } while (teamChoice < 0 || teamChoice >= teamCount);

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

            case 5:{
                if (league.getTeams().empty()){
                    cout << "\nNo Teams Registered.\n";
                    break;
                }

                for (size_t i = 0; i < league.getTeams().size(); i++)
                {
                    cout << i + 1 << ". "
                        << league.getTeams()[i].getTeamName()
                        << endl;
                }

                int teamChoice;
                int teamCount = league.getTeams().size();

                do {
                    cout << "\nSelect Team: ";
                    cin >> teamChoice;
                    teamChoice--;

                    if (teamChoice < 0 || teamChoice >= teamCount)
                    {
                        cout << "\nInvalid Team Selection!\n";
                    }

                } while (teamChoice < 0 || teamChoice >= teamCount);

                vector<Player>& players =
                    league.getTeams()[teamChoice].getPlayers();

                int playerID;
                cout << "Enter Player ID: ";
                cin >> playerID;

                bool found = false;

                for (auto it = players.begin();
                    it != players.end(); ++it)
                {
                    if (it->getIdNom() == playerID)
                    {
                        players.erase(it);

                        cout << "\nPlayer Removed Successfully!\n";

                        found = true;
                        break;
                    }
                }

                if (!found)
                {
                    cout << "\nPlayer Not Found!\n";
                }
                break;

            }

            case 0:
                cout << "\nReturning to Main Menu...\n";
                break;

            default:
                cout << "\nInvalid Option!\n";
                break;
        }
    }while(choice != 0);
}


void coachManagement(FootballLeague& league) {

    int choice = -1;

    while (choice != 0) {

        cout << "\n========== COACH MANAGEMENT ==========\n";
        cout << "1. Register Coach\n";
        cout << "2. Display Coach\n";
        cout << "3. Update Experience\n";
        cout << "4. Remove Coach\n";
        cout << "0. Back\n";
        cout << "======================================\n";
        cout << "Choice ==> ";

        if (!readInt(choice)) {
            cout << "\nInvalid choice. Enter a number.\n";
            continue;
        }

        switch (choice) {

            // REGISTER COACH
            case 1: {

                if (league.getTeams().empty()) {
                    cout << "\nNo Teams Registered.\n";
                    break;
                }

                cout << "\n========== REGISTER COACH ==========\n";

                for (size_t i = 0; i < league.getTeams().size(); ++i) {
                    cout << i + 1 << ". "
                         << league.getTeams()[i].getTeamName()
                         << endl;
                }

                int teamChoice;
                int teamCount = league.getTeams().size();

                do {
                    cout << "\nSelect Team: ";
                    cin >> teamChoice;
                    teamChoice--;

                    if (teamChoice < 0 || teamChoice >= teamCount)
                    {
                        cout << "\nInvalid Team Selection!\n";
                    }

                } while (teamChoice < 0 || teamChoice >= teamCount);
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

                for (size_t i = 0; i < league.getTeams().size(); ++i) {
                    cout << i + 1 << ". "
                         << league.getTeams()[i].getTeamName()
                         << endl;
                }

                int teamChoice;
                int teamCount = league.getTeams().size();

                do {
                    cout << "\nSelect Team: ";
                    cin >> teamChoice;
                    teamChoice--;

                    if (teamChoice < 0 || teamChoice >= teamCount)
                    {
                        cout << "\nInvalid Team Selection!\n";
                    }

                } while (teamChoice < 0 || teamChoice >= teamCount);

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

                for (size_t i = 0; i < league.getTeams().size(); ++i) {
                    cout << i + 1 << ". "
                         << league.getTeams()[i].getTeamName()
                         << endl;
                }

                int teamChoice;
                int teamCount = league.getTeams().size();

                do {
                    cout << "\nSelect Team: ";
                    cin >> teamChoice;
                    teamChoice--;

                    if (teamChoice < 0 || teamChoice >= teamCount)
                    {
                        cout << "\nInvalid Team Selection!\n";
                    }

                } while (teamChoice < 0 || teamChoice >= teamCount);

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

            case 4:{
                if (league.getTeams().empty()){
                    cout << "\nNo Teams Registered.\n";
                    break;
                }

                int teamChoice;

                for (size_t i = 0; i < league.getTeams().size(); i++)
                {
                    cout << i + 1 << ". "
                        << league.getTeams()[i].getTeamName()
                        << endl;
                }

                int teamCount = league.getTeams().size();

                do {
                    cout << "\nSelect Team: ";
                    cin >> teamChoice;
                    teamChoice--;

                    if (teamChoice < 0 || teamChoice >= teamCount)
                    {
                        cout << "\nInvalid Team Selection!\n";
                    }

                } while (teamChoice < 0 || teamChoice >= teamCount);

                vector<Coach>& coaches =
                    league.getTeams()[teamChoice].getCoaches();

                int coachID;

                cout << "Enter Coach ID: ";
                cin >> coachID;

                bool found = false;

                for (auto it = coaches.begin();
                    it != coaches.end(); ++it)
                {
                    if (it->getIdNom() == coachID)
                    {
                        coaches.erase(it);

                        cout << "\nCoach Removed Successfully!\n";

                        found = true;
                        break;
                    }
                }

                if (!found)
                {
                    cout << "\nCoach Not Found!\n";
                }
                break;
            }

            case 0:
                cout << "\nReturning to Main Menu...\n";
                break;

            default:
                cout << "\nInvalid Option!\n";
                break;
        }
    }
}

void officialMenu(FootballLeague& league)
{
    int choice;
    vector<Fixture>& fixtures = league.getFixtures();

    do
    {
        cout << "\n========== MATCH OFFICIALS ==========";
        cout << "\n1. Register Official";
        cout << "\n2. Assign Official";
        cout << "\n3. Display Official";
        cout << "\n4. View Assigned Fixtures";
        cout << "\n0. Back";
        cout << "\nChoice ==> ";

        if (!readInt(choice)) {
            cout << "\nInvalid choice. Enter a number.\n";
            continue;
        }

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

                for(size_t i = 0; i < officials.size(); ++i)
                {
                    cout << "\n" << i + 1 << ". "
                         << officials[i].getFullName();
                }

                cout << "\nSelect Official: ";
                cin >> officialChoice;

                if(officialChoice < 1 || static_cast<size_t>(officialChoice) > officials.size())
                {
                    cout << "\nInvalid official selection.\n";
                    break;
                }

                cout << "\nAVAILABLE FIXTURES\n";

                for(size_t i = 0; i < fixtures.size(); ++i)
                {
                    cout << "\n" << i + 1
                         << ". Fixture ID: "
                         << fixtures[i].getFixtureID();
                }

                cout << "\nSelect Fixture: ";
                cin >> fixtureChoice;

                if(fixtureChoice < 1 || static_cast<size_t>(fixtureChoice) > fixtures.size())
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

                for(size_t i = 0; i < officials.size(); ++i)
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

                for(size_t i = 0; i < officials.size(); ++i)
                {
                    cout << "\n" << i + 1 << ". "
                         << officials[i].getFullName();
                }

                cout << "\nSelect Official: ";
                cin >> officialChoice;

                if(officialChoice < 1 || static_cast<size_t>(officialChoice) > officials.size())
                {
                    cout << "\nInvalid selection.\n";
                    break;
                }

                vector<Fixture*>& assigned = officials[officialChoice - 1].getAssignedFixtures();

                if(assigned.empty())
                {
                    cout << "\nNo assigned fixtures.\n";
                    break;
                }

                for(Fixture* fixture : assigned)
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
    vector<Fixture>& fixtures = league.getFixtures();

    do
    {
        cout << "\n========= FIXTURE MANAGEMENT =========";
        cout << "\n1. Schedule Fixture";
        cout << "\n2. Assign Official";
        cout << "\n3. Record Result";
        cout << "\n4. Complete Fixture";
        cout << "\n0. Back";
        cout << "\nChoice ==> ";

        if (!readInt(choice)) {
            cout << "\nInvalid choice. Enter a number.\n";
            continue;
        }

        switch(choice)
        {
            case 1:
            {
                vector<FootballTeam>& teams = league.getTeams();

                if(teams.size() < 2)
                {
                    cout << "\nAt least two teams are required.\n";
                    break;
                }

                cout << "\nREGISTERED TEAMS\n";

                for(size_t i = 0; i < teams.size(); ++i)
                {
                    cout << "\n" << i + 1 << ". "
                         << teams[i].getTeamName();
                }

                int home, away;

                cout << "\nSelect Home Team: ";
                cin >> home;

                cout << "Select Away Team: ";
                cin >> away;

                if(home < 1 || static_cast<size_t>(home) > teams.size() ||
                   away < 1 || static_cast<size_t>(away) > teams.size() || home == away)
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

                try{
                    league.createFixture(proposed, teams[home - 1], teams[away - 1]);
                } catch(const KPFLExceptions& e){
                    cout << "\n" << e.getMessage() << '\n';
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

                for(size_t i = 0; i < officials.size(); ++i)
                {
                    cout << "\n" << i + 1 << ". "
                         << officials[i].getFullName();
                }

                cout << "\nSelect Official: ";
                cin >> officialChoice;

                if(officialChoice < 1 || static_cast<size_t>(officialChoice) > officials.size())
                {
                    cout << "\nInvalid official selection.\n";
                    break;
                }

                for(size_t i = 0; i < fixtures.size(); ++i)
                {
                    cout << "\n" << i + 1
                         << ". Fixture ID: "
                         << fixtures[i].getFixtureID();
                }

                cout << "\nSelect Fixture: ";
                cin >> fixtureChoice;

                if(fixtureChoice < 1 || static_cast<size_t>(fixtureChoice) > fixtures.size())
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

                for(size_t i = 0; i < fixtures.size(); ++i)
                {
                    cout << "\n" << i + 1
                         << ". Fixture ID: "
                         << fixtures[i].getFixtureID();
                }

                cout << "\nSelect Fixture: ";
                cin >> fixtureChoice;

                if(fixtureChoice < 1 || static_cast<size_t>(fixtureChoice) > fixtures.size())
                {
                    cout << "\nInvalid fixture selection.\n";
                    break;
                }

                try
                {
                    fixtures[fixtureChoice - 1].completeFixture();
                    cout << "\nFixture completed successfully!\n";
                }
                catch (const KPFLExceptions& exception)
                {
                    cout << "\nFixture could not be completed. "
                         << exception.getMessage() << '\n';
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
    vector<Fixture>& fixtures = league.getFixtures();

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

        if (!readInt(choice)) {
            cout << "\nInvalid choice. Enter a number.\n";
            continue;
        }

        switch(choice)
        {
            case 1:
            case 2:
            case 3:
            {
                vector<FootballTeam>& teams = league.getTeams();

                if(teams.empty())
                {
                    cout << "\nNo registered teams available.\n";
                    break;
                }

                cout << "\nREGISTERED TEAMS\n";

                for(size_t i = 0; i < teams.size(); ++i)
                {
                    cout << "\n" << i + 1 << ". "
                         << teams[i].getTeamName();
                }

                int teamChoice;
                int teamCount = league.getTeams().size();

                do {
                    cout << "\nSelect Team: ";
                    cin >> teamChoice;
                    teamChoice--;

                    if (teamChoice < 0 || teamChoice >= teamCount)
                    {
                        cout << "\nInvalid Team Selection!\n";
                    }

                } while (teamChoice < 0 || teamChoice >= teamCount);

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
                catch (const KPFLExceptions& exception)
                {
                    cout << "\nTeam could not be approved: "
                         << exception.getMessage() << '\n';
                }

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

                for(size_t i = 0; i < fixtures.size(); ++i)
                {
                    cout << "\n" << i + 1
                         << ". Fixture ID: "
                         << fixtures[i].getFixtureID();
                }

                cout << "\nSelect Fixture: ";
                cin >> fixtureChoice;

                if(fixtureChoice < 1 || static_cast<size_t>(fixtureChoice) > fixtures.size())
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
                catch (const KPFLExceptions& exception)
                {
                    cout << "\nFixture could not be scheduled: "
                         << exception.getMessage() << '\n';
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

                for(size_t i = 0; i < officials.size(); ++i)
                {
                    cout << "\n" << i + 1 << ". "
                         << officials[i].getFullName();
                }

                cout << "\nSelect Official: ";
                cin >> officialChoice;

                if(officialChoice < 1 || static_cast<size_t>(officialChoice) > officials.size())
                {
                    cout << "\nInvalid official selection.\n";
                    break;
                }

                for(size_t i = 0; i < fixtures.size(); ++i)
                {
                    cout << "\n" << i + 1
                         << ". Fixture ID: "
                         << fixtures[i].getFixtureID();
                }

                cout << "\nSelect Fixture: ";
                cin >> fixtureChoice;

                if(fixtureChoice < 1 || static_cast<size_t>(fixtureChoice) > fixtures.size())
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

                for(size_t i = 0; i < fixtures.size(); ++i)
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


void spectatorManagement(){
    int choice;

    do {
        cout << "\n========== SPECTATOR MANAGEMENT ==========";
        cout << "\n1. Register Spectator";
        cout << "\n2. Purchase Ticket";
        cout << "\n3. Display Spectators";
        cout << "\n4. Add Funds";
        cout << "\n0. Back";
        cout << "\nChoice ==> ";
        if (!readInt(choice)) {
            cout << "\nInvalid choice. Enter a number.\n";
            continue;
        }

        switch (choice) {
            case 1: {
                int id, age;
                string name, gender;

                cout << "Spectator ID: ";
                cin >> id;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Name: ";
                getline(cin, name);
                cout << "Age: ";
                cin >> age;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Gender: ";
                getline(cin, gender);

                spectators.push_back(Spectator(id, name, age, gender, 0, 0.0, 0.0));
                cout << "Spectator registered successfully.\n";
                break;
            }
            case 2: {
                if (spectators.empty()) {
                    cout << "No spectators registered.\n";
                    break;
                }

                for (size_t i = 0; i < spectators.size(); ++i)
                    cout << i + 1 << ". " << spectators[i].getFullName() << '\n';

                int spectatorChoice;
                cout << "Select Spectator: ";
                if (!readInt(spectatorChoice)) {
                    cout << "Invalid selection.\n";
                    break;
                }

                if (spectatorChoice < 1 ||
                    static_cast<size_t>(spectatorChoice) > spectators.size()) {
                    cout << "Invalid selection.\n";
                    break;
                }

                try {
                    Spectator& spectator = spectators[spectatorChoice - 1];
                    spectator.deductBalance(100.0);
                    spectator.buyTicket();
                    spectator.setTotalAmountSpent(spectator.getTotalAmountSpent() + 100.0);
                    cout << "Ticket purchased successfully.\n";
                } catch (const KPFLExceptions& exception) {
                    cout << exception.getMessage() << '\n';
                }
                break;
            }
            case 3:
                if (spectators.empty()) {
                    cout << "No spectators registered.\n";
                } else {
                    for (Spectator& spectator : spectators) {
                        spectator.Display();
                        cout << "Balance: $" << spectator.getBalance() << "\n\n";
                    }
                }
                break;
            case 4: {
                if (spectators.empty()) {
                    cout << "No spectators registered.\n";
                    break;
                }

                for (size_t i = 0; i < spectators.size(); ++i)
                    cout << i + 1 << ". " << spectators[i].getFullName() << '\n';

                int spectatorChoice;
                double amount;
                cout << "Select Spectator: ";
                if (!readInt(spectatorChoice)) {
                    cout << "Invalid selection.\n";
                    break;
                }
                cout << "Amount: ";
                if (!readDouble(amount) || amount < 0) {
                    cout << "Invalid amount.\n";
                    break;
                }

                if (spectatorChoice < 1 ||
                    static_cast<size_t>(spectatorChoice) > spectators.size()) {
                    cout << "Invalid selection.\n";
                    break;
                }

                Spectator& spectator = spectators[spectatorChoice - 1];
                spectator.setBalance(spectator.getBalance() + amount);
                cout << "Funds added successfully.\n";
                break;
            }
            case 0:
                cout << "\nReturning to previous menu...\n";
                break;
            default:
                cout << "\nInvalid choice. Try again.\n";
        }
    } while (choice != 0);
}

void stadiumMenu(FootballLeague& league){
    int choice = -1;

    do {
        cout << "\n========== STADIUM MANAGEMENT ==========";
        cout << "\n1. Add Stadium";
        cout << "\n2. Display Stadium";
        cout << "\n3. Check Capacity";
        cout << "\n4. View Scheduled Fixtures";
        cout << "\n0. Back";
        cout << "\nChoice ==> ";

        if (!readInt(choice)) {
            cout << "\nInvalid choice. Enter a number.\n";
            continue;
        }

        switch (choice) {
            case 1: {
                int id = generateRandomID();
                int capacity = 0;
                int initialOccupancy = 0;
                double ticketPrice = 0.0;
                string name, location, condition;

                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                cout << "\nStadium Name: ";
                getline(cin, name);

                cout << "Location: ";
                getline(cin, location);

                cout << "Field Condition: ";
                getline(cin, condition);

                cout << "Seating Capacity: ";
                if (!readInt(capacity) || capacity < 0) {
                    cout << "\nInvalid seating capacity.\n";
                    break;
                }

                cout << "Ticket Price: ";
                if (!readDouble(ticketPrice) || ticketPrice < 0.0) {
                    cout << "\nInvalid ticket price.\n";
                    break;
                }

                cout << "Initial Occupancy: ";
                if (!readInt(initialOccupancy) || initialOccupancy < 0) {
                    cout << "\nInvalid occupancy.\n";
                    break;
                }

                Stadium stadium(id, name, location, capacity, condition, ticketPrice, 0);

                if (initialOccupancy > 0) {
                    try {
                        stadium.sellTickets(initialOccupancy);
                    } catch (const KPFLExceptions& e) {
                        cout << "\nWarning: Could not set initial occupancy — "
                             << e.getMessage() << "\n";
                    }
                }

                stadiums.push_back(stadium);
                cout << "\nStadium added successfully! (ID: " << id << ")\n";
                break;
            }

            case 2: {
                if (stadiums.empty()) {
                    cout << "\nNo stadiums registered.\n";
                    break;
                }

                for (size_t i = 0; i < stadiums.size(); ++i) {
                    cout << "\n----------------------------------";
                    cout << "\nStadium #" << (i + 1);
                    cout << "\nID: " << stadiums[i].getStadiumID();
                    cout << "\nName: " << stadiums[i].getStadiumName();
                    cout << "\nLocation: " << stadiums[i].getLocation();
                    cout << "\nCondition: " << stadiums[i].getFieldCondition();
                    cout << "\nTicket Price: $" << stadiums[i].getTicketPrice();
                    cout << "\nOccupancy: " << stadiums[i].getOccupancy()
                         << " / " << stadiums[i].getSeatingCapacity();
                    cout << "\nRemaining Seats: " << stadiums[i].getRemainingSeats();
                    cout << "\nAvailable: " << (stadiums[i].isAvailable() ? "Yes" : "No");
                    cout << "\n----------------------------------\n";
                }
                break;
            }

            case 3: {
                if (stadiums.empty()) {
                    cout << "\nNo stadiums registered.\n";
                    break;
                }

                for (size_t i = 0; i < stadiums.size(); ++i) {
                    cout << (i + 1) << ". " << stadiums[i].getStadiumName()
                         << " (" << stadiums[i].getOccupancy()
                         << "/" << stadiums[i].getSeatingCapacity() << ")\n";
                }

                int selection = 0;
                cout << "\nSelect Stadium: ";
                if (!readInt(selection) || selection < 1 ||
                    static_cast<size_t>(selection) > stadiums.size()) {
                    cout << "\nInvalid stadium selection.\n";
                    break;
                }

                Stadium& selected = stadiums[selection - 1];

                cout << "\nStadium: " << selected.getStadiumName();
                cout << "\nCurrent Occupancy: " << selected.getOccupancy();
                cout << "\nSeating Capacity: " << selected.getSeatingCapacity();
                cout << "\nRemaining Seats: " << selected.getRemainingSeats() << "\n";

                int ticketsToSell = 0;
                cout << "\nEnter tickets to sell (0 to skip): ";
                if (!readInt(ticketsToSell)) {
                    cout << "\nInvalid ticket count.\n";
                    break;
                }

                if (ticketsToSell != 0) {
                    try {
                        selected.sellTickets(ticketsToSell);
                        cout << "\nSold " << ticketsToSell
                             << " ticket(s). Remaining seats: "
                             << selected.getRemainingSeats() << "\n";
                    } catch (const KPFLExceptions& e) {
                        cout << "\n" << e.getMessage() << "\n";
                    }
                }
                break;
            }

            case 4: {
                if (stadiums.empty()) {
                    cout << "\nNo stadiums registered.\n";
                    break;
                }

                for (size_t i = 0; i < stadiums.size(); ++i) {
                    cout << (i + 1) << ". " << stadiums[i].getStadiumName() << "\n";
                }

                int selection = 0;
                cout << "\nSelect Stadium: ";
                if (!readInt(selection) || selection < 1 ||
                    static_cast<size_t>(selection) > stadiums.size()) {
                    cout << "\nInvalid stadium selection.\n";
                    break;
                }

                Stadium& selected = stadiums[selection - 1];
                vector<Fixture*>& stadiumFixtures = selected.getFixtures();

                if (!stadiumFixtures.empty()) {
                    cout << "\n========== FIXTURES AT " << selected.getStadiumName() << " ==========\n";
                    for (Fixture* f : stadiumFixtures) {
                        if (f != nullptr) {
                            cout << "\nFixture ID: " << f->getFixtureID();
                            cout << "\nStatus: " << f->getFixtureStatus();
                            cout << "\nAttendance: " << f->getAttendance() << "\n";
                        }
                    }
                } else {
                    vector<Fixture>& leagueFixtures = league.getFixtures();
                    if (leagueFixtures.empty()) {
                        cout << "\nNo scheduled fixtures available.\n";
                    } else {
                        cout << "\n========== ALL LEAGUE FIXTURES ==========\n";
                        for (Fixture& f : leagueFixtures) {
                            cout << "\nFixture ID: " << f.getFixtureID();
                            cout << "\nStatus: " << f.getFixtureStatus();
                            cout << "\nAttendance: " << f.getAttendance() << "\n";
                        }
                    }
                }
                break;
            }

            case 0:
                cout << "\nReturning to Main Menu...\n";
                break;

            default:
                cout << "\nInvalid option!\n";
                break;
        }
    } while (choice != 0);
}

void stadiumShopMenu(){
    int choice = -1;
    static StadiumShop shop(1, "KPFL Stadium Shop", 0, "Main Concourse", 0.0, 0);
    static vector<Product*> catalog;

    do {
        cout << "\n============ STADIUM SHOP ============\n";
        cout << "1. Add Product\n";
        cout << "2. Display Inventory\n";
        cout << "3. Purchase Product\n";
        cout << "0. Back\n";
        cout << "\nChoice ==> ";

        if (!readInt(choice)) {
            cout << "\nInvalid choice. Enter a number.\n";
            continue;
        }

        switch (choice) {
            case 1: {
                int typeChoice = 0;
                cout << "\nProduct Type:\n";
                cout << "1. Food Item\n";
                cout << "2. Merchandise\n";
                cout << "3. Ticket Item\n";
                cout << "Choice ==> ";
                if (!readInt(typeChoice) || typeChoice < 1 || typeChoice > 3) {
                    cout << "\nInvalid product type.\n";
                    break;
                }

                int id = generateRandomID();
                int qty = 0;
                double preTaxPrice = 0.0;
                string name;

                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Product Name: ";
                getline(cin, name);

                cout << "Pre-Tax Price: ";
                if (!readDouble(preTaxPrice) || preTaxPrice < 0.0) {
                    cout << "\nInvalid price.\n";
                    break;
                }

                cout << "Quantity in Stock: ";
                if (!readInt(qty) || qty < 0) {
                    cout << "\nInvalid quantity.\n";
                    break;
                }

                Product* prod = nullptr;

                if (typeChoice == 1) {
                    string category;
                    int day, month, year;

                    cout << "Food Category: ";
                    getline(cin, category);

                    cout << "Expiry Day: ";
                    cin >> day;

                    cout << "Expiry Month: ";
                    cin >> month;

                    cout << "Expiry Year: ";
                    cin >> year;

                    FoodItems* item = new FoodItems();
                    item->setProductID(id);
                    item->setProductName(name);
                    item->setPrice(preTaxPrice);
                    item->setQuantityInStock(qty);
                    item->setCategory(category);

                    Date expiryDate;
                    expiryDate.setDay(day);
                    expiryDate.setMonth(month);
                    expiryDate.setYear(year);

                    item->setExpiryDate(expiryDate);
                    
                    prod = item;
                } else if (typeChoice == 2) {
                    string size, brand;
                    cout << "Size: ";
                    getline(cin, size);
                    cout << "Brand: ";
                    getline(cin, brand);
                    Merchandise* item = new Merchandise();
                    item->setProductID(id);
                    item->setProductName(name);
                    item->setPrice(preTaxPrice);
                    item->setQuantityInStock(qty);
                    item->setSizeOfItem(size);
                    item->setBrand(brand);
                    prod = item;
                } else {
                    string category, seat;
                    cout << "Ticket Category: ";
                    getline(cin, category);
                    cout << "Seat Number: ";
                    getline(cin, seat);
                    Tickets* item = new Tickets();
                    item->setProductID(id);
                    item->setProductName(name);
                    item->setPrice(preTaxPrice);
                    item->setQuantityInStock(qty);
                    item->setTicketCategory(category);
                    item->setSeatNumber(seat);
                    prod = item;
                }

                if (prod != nullptr) {
                    catalog.push_back(prod);
                    shop.addProduct(prod);
                    cout << "\nProduct added with 15%% GCT. Final Price: $"
                         << prod->getPrice() << "\n";
                }
                break;
            }

            case 2: {
                if (catalog.empty()) {
                    cout << "\nNo products in shop inventory.\n";
                    break;
                }

                cout << "\n========== SHOP INVENTORY ==========";
                cout << "\nShop: " << shop.getShopName()
                     << " | Products: " << shop.getProductCount()
                     << " | Inventory Value: $" << shop.getInventoryValue()
                     << " | Sold: " << shop.getTotalProductsSold() << "\n";

                for (size_t i = 0; i < catalog.size(); ++i) {
                    cout << "\n[" << (i + 1) << "]";
                    catalog[i]->Display();
                }
                break;
            }

            case 3: {
                if (catalog.empty()) {
                    cout << "\nNo products available to purchase.\n";
                    break;
                }

                if (spectators.empty()) {
                    cout << "\nNo spectators registered. Register one in Spectator Management first.\n";
                    break;
                }

                if (stadiums.empty()) {
                    cout << "\nNo stadiums registered.\n";
                    break;
                }

                cout << "\n========== SELECT SPECTATOR ==========\n";

                for (int i = 0; i < spectators.size(); i++) {
                    cout << i + 1 << ". "
                        << spectators[i].getFullName()
                        << " (Balance: $"
                        << spectators[i].getBalance()
                        << ")\n";
                }

                int specChoice;

                cout << "Select Spectator: ";
                readInt(specChoice);

                if (specChoice < 1 ||
                    specChoice > spectators.size())
                {
                    cout << "\nInvalid spectator selection.\n";
                    break;
                }

                cout << "\n========== SELECT PRODUCT ==========\n";

                for (int i = 0; i < catalog.size(); i++) {
                    cout << i + 1 << ". "
                        << catalog[i]->getProductName()
                        << " - $"
                        << catalog[i]->getPrice()
                        << " (Stock: "
                        << catalog[i]->getQuantityInStock()
                        << ")\n";
                }

                int prodChoice;

                cout << "Select Product: ";
                readInt(prodChoice);

                if (prodChoice < 1 ||
                    prodChoice > catalog.size())
                {
                    cout << "\nInvalid product selection.\n";
                    break;
                }

                cout << "\n========== SELECT STADIUM ==========\n";

                for (int i = 0; i < stadiums.size(); i++) {
                    cout << i + 1 << ". "
                        << stadiums[i].getStadiumName()
                        << "\n";
                }

                int stadiumChoice;

                cout << "Select Stadium: ";
                readInt(stadiumChoice);

                if (stadiumChoice < 1 ||
                    stadiumChoice > stadiums.size())
                {
                    cout << "\nInvalid stadium selection.\n";
                    break;
                }

                try {
                    Spectator* specPtr = &spectators[specChoice - 1];
                    
                    Product* prodPtr = catalog[prodChoice - 1];
                    
                    Stadium* stadiumPtr = &stadiums[stadiumChoice - 1];
                    
                    
                    if (prodPtr->isTicket())
                    {
                        if (!stadiumPtr->canSellTickets(1))
                        {
                            throw CapacityExceededException();
                        }
                    
                        stadiumPtr->sellTickets(1);
                    }
                    
                    double includedGCT = shop.calculateIncludedGCT(prodPtr->getPrice());
                    
                    shop.transaction(specPtr,prodPtr);
                    
                    cout << "\nPurchase Complete!\n";
                    cout << "Included GCT: $" << includedGCT << endl;
                    }
                        catch (const KPFLExceptions& e) {
                        cout << "\nTransaction failed: " << e.getMessage() << "\n";
                    }

                break;

            }

            case 0:
                cout << "\nReturning to Main Menu...\n";
                break;

            default:
                cout << "\nInvalid option!\n";
                break;
        }
    } while (choice != 0);
}

void resultsMenu(FootballLeague& league){
    int choice = -1;
    vector<Fixture>& fixtures = league.getFixtures();
    vector<FootballTeam>& teams = league.getTeams();

    struct RecordedFixtureResult {
        int fixtureID;
        string homeTeamName;
        string awayTeamName;
        MatchResult result;
    };

    vector<RecordedFixtureResult> recordedResults;

    do {
        cout << "\n========== MATCH RESULTS ==========";
        cout << "\n1. Enter Match Result";
        cout << "\n2. Display Result";
        cout << "\n3. View League Standings";
        cout << "\n0. Back";
        cout << "\nChoice ==> ";

        if (!readInt(choice)) {
            cout << "\nInvalid choice. Enter a number.\n";
            continue;
        }

        switch (choice) {
            case 1: {
                if (fixtures.empty()) {
                    cout << "\nNo fixtures available.\n";
                    break;
                }

                for (size_t i = 0; i < fixtures.size(); ++i) {
                    cout << (i + 1) << ". Fixture ID: " << fixtures[i].getFixtureID()
                         << " | Status: " << fixtures[i].getFixtureStatus() << "\n";
                }

                int fixtureChoice = 0;
                cout << "\nSelect Fixture: ";
                if (!readInt(fixtureChoice) || fixtureChoice < 1 ||
                    static_cast<size_t>(fixtureChoice) > fixtures.size()) {
                    cout << "\nInvalid fixture selection.\n";
                    break;
                }

                Fixture& fixture = fixtures[fixtureChoice - 1];

                FootballTeam* home = nullptr;
                FootballTeam* away = nullptr;
                for (FootballTeam& team : teams) {
                    if (team.getTeamID() == fixture.getHomeTeamID()) {
                        home = &team;
                    }
                    if (team.getTeamID() == fixture.getAwayTeamID()) {
                        away = &team;
                    }
                }

                if (home == nullptr || away == nullptr) {
                    cout << "\nUnable to locate fixture teams.\n";
                    break;
                }

                int homeScore = 0;
                int awayScore = 0;
                string stats;

                cout << "\n" << home->getTeamName() << " Goals: ";
                if (!readInt(homeScore)) {
                    cout << "\nInvalid input.\n";
                    break;
                }

                cout << away->getTeamName() << " Goals: ";
                if (!readInt(awayScore)) {
                    cout << "\nInvalid input.\n";
                    break;
                }

                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Match Statistics: ";
                getline(cin, stats);

                try {
                    MatchResult matchRes;
                    matchRes.setHomeScore(homeScore);
                    matchRes.setAwayScore(awayScore);
                    matchRes.setMatchStatistics(stats);
                    matchRes.determineWinner(*home, *away);
                    fixture.recordResults(matchRes);

                    bool updated = false;
                    for (RecordedFixtureResult& entry : recordedResults) {
                        if (entry.fixtureID == fixture.getFixtureID()) {
                            entry.homeTeamName = home->getTeamName();
                            entry.awayTeamName = away->getTeamName();
                            entry.result = matchRes;
                            updated = true;
                            break;
                        }
                    }
                    if (!updated) {
                        recordedResults.push_back({
                            fixture.getFixtureID(),
                            home->getTeamName(),
                            away->getTeamName(),
                            matchRes
                        });
                    }

                    cout << "\nMatch result recorded successfully!\n";
                    matchRes.Display();
                } catch (const KPFLExceptions& e) {
                    cout << "\n" << e.getMessage() << "\n";
                }
                break;
            }

            case 2: {
                if (recordedResults.empty()) {
                    cout << "\nNo match results recorded yet.\n";
                    break;
                }

                for (const RecordedFixtureResult& entry : recordedResults) {
                    cout << "\n----------------------------------";
                    cout << "\nFixture ID: " << entry.fixtureID
                         << " (" << entry.homeTeamName << " vs " << entry.awayTeamName << ")";
                    entry.result.Display();
                }
                break;
            }

            case 3: {
                if (teams.empty()) {
                    cout << "\nNo registered teams.\n";
                    break;
                }
                league.getStandings();
                break;
            }

            case 0:
                cout << "\nReturning to Main Menu...\n";
                break;

            default:
                cout << "\nInvalid option!\n";
                break;
        }
    } while (choice != 0);
}

void footballLeagueMenu(FootballLeague& league)
{
    int choice = -1;

    do
    {
        cout << "\n========== FOOTBALL LEAGUE ==========";
        cout << "\n1. Register Team";
        cout << "\n2. Create Fixture";
        cout << "\n3. Record League Result";
        cout << "\n4. View Standings";
        cout << "\n5. Display Teams";
        cout << "\n6. Display Fixtures";
        cout << "\n0. Back";
        cout << "\nChoice ==> ";

        if (!readInt(choice))
        {
            cout << "\nInvalid choice. Enter a number.\n";
            continue;
        }

        switch (choice)
        {
            // REGISTER TEAM
            case 1:
            {
                FootballTeam team;

                int id = generateRandomID();
                string name, parish;

                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                cout << "\n========== REGISTER TEAM ==========\n";

                cout << "Team Name: ";
                getline(cin, name);

                cout << "Parish: ";
                getline(cin, parish);

                team.setTeamID(id);
                team.setTeamName(name);
                team.setParish(parish);

                try
                {
                    league.registerTeam(team);
                }
                catch (const KPFLExceptions& e)
                {
                    cout << e.getMessage() << endl;
                }

                break;
            }

            // CREATE FIXTURE
            case 2:
            {
                vector<FootballTeam>& teams = league.getTeams();

                if (teams.size() < 2)
                {
                    cout << "\nAt least two teams are required.\n";
                    break;
                }

                cout << "\n========== REGISTERED TEAMS ==========\n";

                for (size_t i = 0; i < teams.size(); ++i)
                {
                    cout << i + 1 << ". "
                         << teams[i].getTeamName()
                         << " (ID: " << teams[i].getTeamID() << ")\n";
                }

                int home, away;

                cout << "\nSelect Home Team: ";
                if (!readInt(home)) break;

                cout << "Select Away Team: ";
                if (!readInt(away)) break;

                if (home < 1 || away < 1 ||
                    static_cast<size_t>(home) > teams.size() ||
                    static_cast<size_t>(away) > teams.size() ||
                    home == away)
                {
                    cout << "\nInvalid team selection.\n";
                    break;
                }

                int id, day, month, year;
                int hours, minutes, seconds;

                cout << "\nFixture ID: ";
                if (!readInt(id)) break;

                cout << "Day: ";
                if (!readInt(day)) break;

                cout << "Month: ";
                if (!readInt(month)) break;

                cout << "Year: ";
                if (!readInt(year)) break;

                cout << "Hours: ";
                if (!readInt(hours)) break;

                cout << "Minutes: ";
                if (!readInt(minutes)) break;

                cout << "Seconds: ";
                if (!readInt(seconds)) break;

                Fixture fixture;

                fixture.setFixtureID(id);
                fixture.setFixtureDate(day, month, year);
                fixture.setFixtureTime(hours, minutes, seconds);
                fixture.setFixtureStatus("Scheduled");

                try
                {
                    league.createFixture(
                        fixture,
                        teams[home - 1],
                        teams[away - 1]
                    );

                    cout << "\nFixture Created Successfully!\n";
                }
                catch (const KPFLExceptions& e)
                {
                    cout << "\n" << e.getMessage() << endl;
                }

                break;
            }

            // RECORD LEAGUE RESULT
            case 3:
            {
                vector<Fixture>& fixtures = league.getFixtures();
                vector<FootballTeam>& teams = league.getTeams();

                if (fixtures.empty())
                {
                    cout << "\nNo Fixtures Available.\n";
                    break;
                }

                cout << "\n========== SCHEDULED FIXTURES ==========\n";

                for (size_t i = 0; i < fixtures.size(); ++i)
                {
                    cout << "\n" << i + 1
                         << ". Fixture ID: "
                         << fixtures[i].getFixtureID()
                         << " | Status: "
                         << fixtures[i].getFixtureStatus();
                }

                int fixtureChoice;

                cout << "\n\nSelect Fixture: ";
                if (!readInt(fixtureChoice)) break;

                if (fixtureChoice < 1 ||
                    static_cast<size_t>(fixtureChoice) > fixtures.size())
                {
                    cout << "\nInvalid Fixture Selection.\n";
                    break;
                }

                Fixture& fixture = fixtures[fixtureChoice - 1];

                if (fixture.getFixtureStatus() == "Full Time" ||
                    fixture.getFixtureStatus() == "Cancelled" ||
                    fixture.getFixtureStatus() == "Postponed")
                {
                    cout << "\nThis fixture cannot accept a result.\n";
                    break;
                }

                FootballTeam* home = nullptr;
                FootballTeam* away = nullptr;

                for (FootballTeam& team : teams)
                {
                    if (team.getTeamID() == fixture.getHomeTeamID())
                        home = &team;

                    if (team.getTeamID() == fixture.getAwayTeamID())
                        away = &team;
                }

                if (home == nullptr || away == nullptr)
                {
                    cout << "\nUnable to locate fixture teams.\n";
                    break;
                }

                int homeScore, awayScore;

                cout << "\n" << home->getTeamName() << " Goals: ";
                if (!readInt(homeScore)) break;

                cout << away->getTeamName() << " Goals: ";
                if (!readInt(awayScore)) break;

                try
                {
                    MatchResult result;

                    result.setHomeScore(homeScore);
                    result.setAwayScore(awayScore);

                    result.determineWinner(*home, *away);

                    fixture.recordResults(result);

                    cout << "\nLeague Result Recorded Successfully!\n";

                    result.Display();
                }
                catch (const KPFLExceptions& e)
                {
                    cout << e.getMessage() << endl;
                }

                break;
            }

            // VIEW STANDINGS
            case 4:
            {
                if (league.getTeams().empty())
                {
                    cout << "\nNo Registered Teams.\n";
                    break;
                }

                league.getStandings();

                break;
            }

            // DISPLAY TEAMS
            case 5:
            {
                vector<FootballTeam>& teams = league.getTeams();

                if (teams.empty())
                {
                    cout << "\nNo Registered Teams.\n";
                    break;
                }

                cout << "\n========== REGISTERED TEAMS ==========\n";

                for (FootballTeam& team : teams)
                {
                    cout << "\n----------------------------------";
                    cout << "\nTeam ID: " << team.getTeamID();
                    cout << "\nTeam Name: " << team.getTeamName();
                    cout << "\nParish: " << team.getParish();
                    cout << "\nStatus: " << team.getTeamStatus();
                    cout << "\nPoints: " << team.getPoints();
                    cout << "\nWins: " << team.getWins();
                    cout << "\nDraws: " << team.getDraws();
                    cout << "\nLosses: " << team.getLosses();
                    cout << "\n----------------------------------\n";
                }

                break;
            }

            // DISPLAY FIXTURES
            case 6:
            {
                vector<Fixture>& fixtures = league.getFixtures();
                vector<FootballTeam>& teams = league.getTeams();

                if (fixtures.empty())
                {
                    cout << "\nNo Fixtures Available.\n";
                    break;
                }

                cout << "\n========== LEAGUE FIXTURES ==========\n";

                for (Fixture& fixture : fixtures)
                {
                    string homeName = "Unknown";
                    string awayName = "Unknown";

                    for (FootballTeam& team : teams)
                    {
                        if (team.getTeamID() == fixture.getHomeTeamID())
                            homeName = team.getTeamName();

                        if (team.getTeamID() == fixture.getAwayTeamID())
                            awayName = team.getTeamName();
                    }

                    cout << "\n----------------------------------";
                    cout << "\nFixture ID: " << fixture.getFixtureID();

                    cout << "\nHome Team: " << homeName;
                    cout << "\nAway Team: " << awayName;

                    cout << "\nDate: ";
                    fixture.getFixtureDate();

                    cout << "\nTime: ";
                    fixture.getFixtureTime();

                    cout << "\nStatus: " << fixture.getFixtureStatus();

                    cout << "\n----------------------------------\n";
                }

                break;
            }

            case 0:
                cout << "\nReturning to Main Menu...\n";
                break;

            default:
                cout << "\nInvalid Option!\n";
        }

    } while (choice != 0);
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
        if (!readInt(choice)) {
            cout << "\nInvalid choice. Enter a number.\n";
            continue;
        }

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
        if (!readInt(choice)) {
            cout << "\nInvalid choice. Enter a number.\n";
            continue;
        }

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
    cout << "\n13. File Management";
    cout << "\n 0. Exit";
    cout << "\n==================================================";
    cout << "\nEnter option: ";
    if (!readInt(choice)) {
        if (cin.eof()) {
            return 0;
        }
        cout << "\nInvalid choice. Enter a number.\n";
        return -1;
    }

    return choice;
}

int generateRandomID() {
    return (rand() % 10000) + 1;
}