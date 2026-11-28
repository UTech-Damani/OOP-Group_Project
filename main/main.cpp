/*
Group Members:
Damani Williams - 2007591
Monecia Hamilton - 2409578
Aaron Elliston - 2409567
Jamelia Freeman - 2407243

Group Name: Imperial Strikaz

Business Name: Kingston Premier Football League (KPFL)

Business Type: Sports / Football League Administration

Course: CIT2004 - Object-Oriented Programming

Teacher: Oral Robinson

Occurrence: UDC: 8am - 11am

Due Date: Novemeber 27, 2026

Project Title:
Kingston Premier Football League (KPFL)
Football League and Match-Day Management System

Project Description:
This project involves developing a C++ Football League and
Match-Day Management System for the Kingston Premier Football
League (KPFL). It manages teams, players, coaches, officials,
stadiums, fixtures, match results, ticket sales and stadium-shop
transactions.

The system applies object-oriented programming concepts,
collections, file handling and custom exception handling to
streamline league operations, maintain records and ensure
reliable match-day management.
*/

#include <iostream>  // Provides input and output operations, such as cin and cout.
#include <windows.h> // Provides Windows-specific functions.

#include <string>    // Provides the string data type.
#include <vector>    // Provides the vector container for storing collections of objects.
#include <ctype.h>   // Provides character-handling functions, such as tolower().
#include <cstdlib>   // Provides general utility functions, such as rand() and srand().
#include <ctime>     // Provides time-related functions, such as time().
#include <limits>    // Provides numeric limits for input validation.

#include "universal/KPFL.h"         // Includes the main KPFL system classes.
#include "universal/FileManager.h"  // Includes functionality for saving and loading system data.

using namespace std;

// Global collections for storing match officials, spectators and stadiums.
vector<MatchOfficial> officials;
vector<Spectator> spectators;
vector<Stadium> stadiums;

// Global commissioner object used to manage league administration.
LeagueCommissioner commissioner;

// Function declarations for the main menu and utility operations.
int displayMainMenu();       // Displays the main system menu and returns the user's selection.
int generateRandomID();      // Generates a random identification number.
bool readInt(int& value);    // Reads and validates an integer input.
bool readDouble(double& value); // Reads and validates a decimal number.

// Function declarations for managing league members.
void teamManagement(FootballLeague& league);   // Handles football team management.
void playerManagement(FootballLeague& league); // Handles player management.
void coachManagement(FootballLeague& league);  // Handles coach management.

// Function for testing the system's custom exception classes.
void testExceptions();

// Function declarations for managing officials and fixtures.
void officialMenu(FootballLeague& league);        // Handles match official management.
void fixtureManagementMenu(FootballLeague& league); // Handles fixture scheduling and management.
void commissionerMenu(FootballLeague& league);    // Handles commissioner operations.
void resultsMenu(FootballLeague& league);          // Handles recording and displaying match results.

// Function declarations for stadium and match-day management.
void stadiumMenu(FootballLeague& league); // Handles stadium management.
void stadiumShopMenu();                   // Handles stadium shop operations.
void spectatorManagement();               // Handles spectator registration and management.

// Function declarations for general league operations.
void footballLeagueMenu(FootballLeague& league); // Handles football league operations.
void fileManagement(FootballLeague& league);     // Handles saving and loading system data.
void reportsMenu(FootballLeague& league);        // Displays league reports and statistics.
void liveMatchMenu(FootballLeague& league);      // Handles live match updates and events.

bool readInt(int& value)
{
    cin >> value;
    if (!cin) {
        if (cin.eof()) {
            value = 0;
            return false;
        }
        cin.clear();
        cin.ignore();
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
        cin.ignore();
        value = 0.0;
        return false;
    }
    return true;
}

int main()
{
    srand(time(NULL)); // Seeds the random number generator.

    Date startDate(1, 12, 2026); // Sets the league start date.

    Date endDate(31, 12, 2027); // Sets the league end date.

    // Creates the Football League object.
    FootballLeague league(1, "Kingston Premier Football League", "2026 Season", startDate, endDate, 0, "Active");
    int choice;

    cout << "Za Wurldo!" << endl;

    // Repeatedly displays the main menu until the user chooses to exit.
    do{
        choice = displayMainMenu();

        // Executes the selected menu operation.
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

            case 14:
                reportsMenu(league);
                break;

            case 0:
                cout << "You are now exiting the KPFL Demo program..." << endl;
                break;

            default:
                break;
        }
    }while(choice != 0);

    return 0; // Indicates successful program termination.
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
        cout << "\n 6. Update Team";
        cout << "\n 7. Search Team"; 
        cout << "\n 0. Back";
        cout << "\n==================================================";
        cout << "\nChoice ==> ";
        
        if (!readInt(choice)) {
            cout << "\nInvalid choice. Enter a number.\n";
            continue;
        }
        
        switch(choice){
            case 1: {
                int id;
                string name;
                string parish;
                
                cin.ignore();
                
                cout << "Team Name: ";
                getline(cin,name);
                
                cout << "Parish: ";
                getline(cin,parish);

                cout << "Registration Number (ID): ";
                cin >> id;
                
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
                
                for(size_t i = 0; i < league.getTeams().size(); ++i)
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
                catch(const KPFLExceptions& e)
                    {
                        cout << e.getMessage() << endl;
                    }
                break;
            }
        
            case 3:{
                if(league.getTeams().empty())
                    {
                        cout << "\nNo Teams Registered.\n";
                        break;
                    }
                
                    cout << "\nRegistered Teams\n";

                for(size_t i = 0; i < league.getTeams().size(); ++i)
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
                if(league.getTeams().empty())
                    {
                        cout << "\nNo Teams Registered.\n";
                        break;
                    }
                
                cout << "\nRegistered Teams\n";
                
                for(size_t i = 0; i < league.getTeams().size(); ++i)
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
                
                cout << endl;
                
                
                league.getTeams()[teamChoice].Display();
                
                break;
            }
            
            case 5:{
                if(league.getTeams().empty())
                    {
                        cout << "\nNo Teams Registered.\n";
                        break;
                    }
                
                for(FootballTeam& team : league.getTeams()){
                    cout << "\n------------------------------------\n";
                    team.Display();
                }
                
                break;
            }

            case 6: {
                if(league.getTeams().empty())
                    {
                        cout << "\nNo Teams Registered.\n";
                        break;
                    }

                int teamID;
                bool found = false;

                cout << "\nEnter Team ID: ";
                cin >> teamID;

                for(FootballTeam& team : league.getTeams())
                {
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

                if(!found)
                    {
                        cout << "\nTeam Not Found!\n";
                    }
                break;
            }

            case 7: {
                if(league.getTeams().empty())
                    {
                        cout << "\nNo Teams Registered.\n";
                        break;
                    }

                int teamID;
                bool found = false;

                cout << "\nEnter Team ID: ";
                cin >> teamID;

                for(FootballTeam& team : league.getTeams())
                {
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

                if(!found)
                    {
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


    while (choice != 0)
        {

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

        switch (choice) 
        {

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
                catch (const KPFLExceptions& e) 
                    {
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

                for (size_t i = 0; i < league.getTeams().size(); ++i)
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

                if (players.empty()) 
                    {
                        cout << "\nThis Team Has No Registered Players.\n";
                        break;
                    }

                int playerID;
                bool found = false;

                cout << "\nEnter Player ID: ";
                cin >> playerID;

                for (Player& player : players) 
                {

                    if (player.getIdNom() == playerID) 
                        {

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
                                if (!readInt(age) || age < league.getMinimumAge())
                                    {
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

                                    if (statusChoice >= 1 && statusChoice <= 6)
                                        {
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

                if (league.getTeams().empty()) 
                    {
                        cout << "\nNo Teams Registered.\n";
                        break;
                    }

                for (size_t i = 0; i < league.getTeams().size(); ++i) 
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

                int playerID;
                bool found = false;

                cout << "\nEnter Player ID: ";
                cin >> playerID;

                for (Player& player :
                     league.getTeams()[teamChoice].getPlayers()) 
                {

                    if (player.getIdNom() == playerID) 
                        {
                            player.Display();
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

            // CHECK ELIGIBILITY
            case 4: {

                int playerID;
                bool found = false;

                if (league.getTeams().empty()) {
                    cout << "\nNo Teams Registered.\n";
                    break;
                }

                for (size_t i = 0; i < league.getTeams().size(); ++i) 
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

                cout << "Player ID: ";
                cin >> playerID;

                for (Player& player :
                     league.getTeams()[teamChoice].getPlayers()) 
                {

                    if (player.getIdNom() == playerID) 
                    {

                        if (player.isEligible()) 
                            {
                                cout << "\nPlayer Is Eligible.\n";
                            }
                        else 
                            {
                                cout << "\nPlayer Is Not Eligible.\n";
                            }

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

            case 5:{
                if (league.getTeams().empty())
                    {
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

        if (!readInt(choice))
            {
                cout << "\nInvalid choice. Enter a number.\n";
                continue;
            }

        switch (choice) {

            // REGISTER COACH
            case 1: {

                if (league.getTeams().empty()) 
                    {
                        cout << "\nNo Teams Registered.\n";
                        break;
                    }

                cout << "\n========== REGISTER COACH ==========\n";

                for (size_t i = 0; i < league.getTeams().size(); ++i)
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

                switch (qualChoice) 
                    {
                        case 1: qualification = "Level 1"; break;
                        case 2: qualification = "Level 2"; break;
                        case 3: qualification = "Level 3"; break;

                    default:
                        cout << "\nInvalid Qualification Option!\n";
                        break;
                    }

                if (qualChoice < 1 || qualChoice > 3) 
                    {
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

                switch (roleChoice)
                    {
                        case 1: role = "Head Coach"; break;
                        case 2: role = "Assistant Coach"; break;
                        case 3: role = "Goalkeeping Coach"; break;

                    default:
                        cout << "\nInvalid Coaching Role Option!\n";
                        break;
                    }

                if (roleChoice < 1 || roleChoice > 3) 
                    {
                        break;
                    }

                try {

                    Coach coach(id, name, age, gender, qualification, role, experience);

                    coach.setTeam(&league.getTeams()[teamChoice]);
                    

                    league.getTeams()[teamChoice].addCoach(coach);

                    cout << "\nCoach Registered Successfully!\n";

                }
                catch (const KPFLExceptions& e)
                    {
                        cout << e.getMessage() << endl;
                    }

                break;
            }

            // DISPLAY COACH
            case 2: {

                if (league.getTeams().empty()) 
                    {
                        cout << "\nNo Teams Registered.\n";
                        break;
                    }

                cout << "\n========== SELECT TEAM ==========\n";

                for (size_t i = 0; i < league.getTeams().size(); ++i) 
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

                vector<Coach>& coaches =
                    league.getTeams()[teamChoice].getCoaches();

                if (coaches.empty()) 
                    {
                        cout << "\nThis Team Has No Registered Coaches.\n";
                        break;
                    }

                int coachID;
                bool found = false;

                cout << "\nEnter Coach ID: ";
                cin >> coachID;

                for (Coach& coach : coaches) 
                {

                    if (coach.getIdNom() == coachID)
                        {

                            coach.Display();
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

            // UPDATE EXPERIENCE
            case 3: {

                if (league.getTeams().empty())
                    {
                        cout << "\nNo Teams Registered.\n";
                        break;
                    }

                cout << "\n========== SELECT TEAM ==========\n";

                for (size_t i = 0; i < league.getTeams().size(); ++i) 
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

                vector<Coach>& coaches =
                    league.getTeams()[teamChoice].getCoaches();

                if (coaches.empty()) 
                    {
                        cout << "\nThis Team Has No Registered Coaches.\n";
                        break;
                    }

                int coachID;
                bool found = false;

                cout << "\nEnter Coach ID: ";
                cin >> coachID;

                for (Coach& coach : coaches) 
                {

                    if (coach.getIdNom() == coachID) 
                    {

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

                if (!found) 
                    {
                        cout << "\nCoach Not Found!\n";
                    }

                break;
            }

            case 4:{
                if (league.getTeams().empty())
                    {
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
                int roleChoice, rankChoice;

                string name, gender, role, rank;

                vector<string> roles =
                {
                    "Referee",
                    "Assistant Referee",
                    "Fourth Official",
                    "Video Assistant Referee (VAR)"
                };

                vector<string> ranks =
                {
                    "Level 1",
                    "Level 2",
                    "Level 3",
                    "Elite"
                };

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

                // Select officiating role
                cout << "\n--- Select Officiating Role ---\n";

                for(int i = 0; i < roles.size(); i++)
                {
                    cout << i + 1 << ". " << roles[i] << endl;
                }

                cout << "Enter choice: ";
                cin >> roleChoice;

                // Select rank
                cout << "\n--- Select Official Rank ---\n";

                for(int i = 0; i < ranks.size(); i++)
                {
                    cout << i + 1 << ". " << ranks[i] << endl;
                }

                cout << "Enter choice: ";
                cin >> rankChoice;

                cout << "\nAvailability (1 = Available, 0 = Unavailable): ";
                cin >> available;

                cout << "Years of Experience: ";
                cin >> experience;

                if(id <= 0 || age < 0 || experience < 0 ||
                (available != 0 && available != 1) ||
                roleChoice < 1 || roleChoice > roles.size() ||
                rankChoice < 1 || rankChoice > ranks.size())
                {
                    cout << "\nInvalid information entered.\n";
                    break;
                }

                role = roles[roleChoice - 1];
                rank = ranks[rankChoice - 1];

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
        cout << "\n5. Manage Live Match";
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

                if(stadiums.empty())
                    {
                        cout << "\nNo stadiums registered.\n";
                        break;
                    }
                    
                    cout << "\nREGISTERED STADIUMS\n";
                    
                    for(size_t i = 0; i < stadiums.size(); i++)
                    {
                        cout << "\n" << i + 1 << ". " << stadiums[i].getStadiumName();
                    }
                    
                    int stadiumChoice;
                    
                    cout << "\nSelect Stadium: ";
                    cin >> stadiumChoice;
                    
                    if(stadiumChoice < 1 || static_cast<size_t>(stadiumChoice) > stadiums.size()){
                        cout << "\nInvalid stadium selection.\n";
                        break;
                    }
                proposed.setFixtureStatus("Scheduled");

                proposed.setStadium(&stadiums[stadiumChoice - 1]);

                try{
                    league.createFixture(proposed, teams[home - 1], teams[away - 1]);
                } catch(const KPFLExceptions& e){
                    cout << "\n" << e.getMessage() << '\n';
                }

                cout << "\nFixture Created Successfully!\n";

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
                resultsMenu(league);

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

            case 5:
                liveMatchMenu(league);
                break;

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
                        commissioner.approveTeam(teams[teamChoice]);
                        cout << "\nTeam approval completed.\n";
                    }
                    else if(choice == 2)
                    {
                        commissioner.suspendTeam(teams[teamChoice]);
                        cout << "\nTeam suspended successfully.\n";
                    }
                    else if(choice == 3)
                    {
                        commissioner.reinstateTeam(teams[teamChoice]);
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
// Handles spectator registration, ticket purchases and account balances.
void spectatorManagement(){
    int choice;

    do {
        // Displays the spectator management options.
        cout << "\n========== SPECTATOR MANAGEMENT ==========";
        cout << "\n1. Register Spectator";
        cout << "\n2. Purchase Ticket";
        cout << "\n3. Display Spectators";
        cout << "\n4. Add Funds";
        cout << "\n0. Back";
        cout << "\nChoice ==> ";
        // Checks that the menu choice is a valid number.
        if (!readInt(choice)) {
            cout << "\nInvalid choice. Enter a number.\n";
            continue;
        }

        // Performs the operation selected by the user.
        switch (choice) {
            // Registers a new spectator.
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

                // Creates the spectator and adds them to the list.
                spectators.push_back(Spectator(id, name, age, gender, 0, 0.0, 0.0));
                cout << "Spectator registered successfully.\n";
                break;
            }
            // Processes a spectator's ticket purchase.
            case 2: {
                // Checks that at least one spectator is registered.
                if (spectators.empty()) 
                {
                    cout << "No spectators registered.\n";
                    break;
                }

                // Displays the registered spectators.
                for (size_t i = 0; i < spectators.size(); ++i)
                    cout << i + 1 << ". " << spectators[i].getFullName() << '\n';

                int spectatorChoice;
                cout << "Select Spectator: ";
                // Validates the selected spectator number.
                if (!readInt(spectatorChoice)) 
                {
                    cout << "Invalid selection.\n";
                    break;
                }

                // Checks that the selected spectator exists.
                if (spectatorChoice < 1 || static_cast<size_t>(spectatorChoice) > spectators.size())
                {
                    cout << "Invalid selection.\n";
                    break;
                }

                // Attempts to deduct the ticket cost and record the purchase.
                try {
                    // Retrieves the selected spectator.
                    Spectator& spectator = spectators[spectatorChoice - 1];
                    // Deducts the ticket price from the spectator's balance.
                    spectator.deductBalance(100.0);
                    spectator.buyTicket();
                    spectator.setTotalAmountSpent(spectator.getTotalAmountSpent() + 100.0);
                    cout << "Ticket purchased successfully.\n";
                // Handles errors that prevent the ticket purchase.
                } catch (const KPFLExceptions& exception)
                    
                    {
                        cout << exception.getMessage() << '\n';
                    }
                break;
            }
            // Displays the registered spectators and their balances.
            case 3:
                if (spectators.empty()) 
                {
                    cout << "No spectators registered.\n";
                } 
                else 
                {
                    // Goes through each spectator in the list.
                    for (Spectator& spectator : spectators) 
                    {
                        spectator.Display();
                        cout << "Balance: $" << spectator.getBalance() << "\n\n";
                    }
                }
                break;
            // Adds funds to a spectator's account.
            case 4: {
                if (spectators.empty())
                {
                    cout << "No spectators registered.\n";
                    break;
                }

                for (size_t i = 0; i < spectators.size(); ++i)
                    cout << i + 1 << ". " << spectators[i].getFullName() << '\n';

                int spectatorChoice;
                double amount;
                cout << "Select Spectator: ";
                if (!readInt(spectatorChoice)) 
                {
                    cout << "Invalid selection.\n";
                    break;
                }
                cout << "Amount: ";
                // Checks that the amount entered is valid and not negative.
                if (!readDouble(amount) || amount < 0)
                {
                    cout << "Invalid amount.\n";
                    break;
                }

                if (spectatorChoice < 1 || static_cast<size_t>(spectatorChoice) > spectators.size())
                {
                    cout << "Invalid selection.\n";
                    break;
                }

                Spectator& spectator = spectators[spectatorChoice - 1];
                // Adds the entered amount to the spectator's balance.
                spectator.setBalance(spectator.getBalance() + amount);
                cout << "Funds added successfully.\n";
                break;
            }
            // Returns to the previous menu.
            case 0:
                cout << "\nReturning to previous menu...\n";
                break;
            // Handles menu choices that are not listed.
            default:
                cout << "\nInvalid choice. Try again.\n";
        }
    } while (choice != 0);
}

// Manages stadium registration, capacity and scheduled fixtures.
void stadiumMenu(FootballLeague& league){
    int choice = -1;

    do {
        // Displays the stadium management options.
        cout << "\n========== STADIUM MANAGEMENT ==========";
        cout << "\n1. Add Stadium";
        cout << "\n2. Display Stadium";
        cout << "\n3. Check Capacity";
        cout << "\n4. View Scheduled Fixtures";
        cout << "\n0. Back";
        cout << "\nChoice ==> ";

        // Checks that the menu choice is a valid number.
        if (!readInt(choice))
        {
            cout << "\nInvalid choice. Enter a number.\n";
            continue;
        }

        // Performs the selected stadium operation.
        switch (choice) 
        {
            // Registers a new stadium.
            case 1: {
                // Generates an ID and prepares the stadium details.
                int id = generateRandomID();
                int capacity = 0;
                int initialOccupancy = 0;
                double ticketPrice = 0.0;
                string name, location, condition;

                // Clears the input line before reading text.
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                cout << "\nStadium Name: ";
                getline(cin, name);

                cout << "Location: ";
                getline(cin, location);

                cout << "Field Condition: ";
                getline(cin, condition);

                cout << "Seating Capacity: ";
                // Validates the stadium's seating capacity.
                if (!readInt(capacity) || capacity < 0) {
                    cout << "\nInvalid seating capacity.\n";
                    break;
                }

                cout << "Ticket Price: ";
                // Validates the stadium's ticket price.
                if (!readDouble(ticketPrice) || ticketPrice < 0.0) 
                {
                    cout << "\nInvalid ticket price.\n";
                    break;
                }

                cout << "Initial Occupancy: ";
                // Validates the initial stadium occupancy.
                if (!readInt(initialOccupancy) || initialOccupancy < 0)
                {
                    cout << "\nInvalid occupancy.\n";
                    break;
                }

                // Creates a stadium using the information entered.
                Stadium stadium(id, name, location, capacity, condition, ticketPrice, 0);

                // Sets the initial occupancy when tickets are already sold.
                if (initialOccupancy > 0) {
                    try {
                        stadium.sellTickets(initialOccupancy);
                    } catch (const KPFLExceptions& e) 
                        {
                        cout << "\nWarning: Could not set initial occupancy — "
                             << e.getMessage() << "\n";
                        }
                }

                // Adds the new stadium to the registered stadiums.
                stadiums.push_back(stadium);
                cout << "\nStadium added successfully! (ID: " << id << ")\n";
                break;
            }

            // Displays the details of registered stadiums.
            case 2: {
                // Checks whether any stadiums have been registered.
                if (stadiums.empty()) {
                    cout << "\nNo stadiums registered.\n";
                    break;
                }

                // Displays each stadium's information.
                for (size_t i = 0; i < stadiums.size(); ++i) 
                {
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

            // Checks stadium capacity and allows ticket sales.
            case 3: {
                if (stadiums.empty())
                {
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
                if (!readInt(selection) || selection < 1 || static_cast<size_t>(selection) > stadiums.size()) 
                {
                    cout << "\nInvalid stadium selection.\n";
                    break;
                }

                // Retrieves the stadium selected by the user.
                Stadium& selected = stadiums[selection - 1];

                cout << "\nStadium: " << selected.getStadiumName();
                cout << "\nCurrent Occupancy: " << selected.getOccupancy();
                cout << "\nSeating Capacity: " << selected.getSeatingCapacity();
                cout << "\nRemaining Seats: " << selected.getRemainingSeats() << "\n";

                // Stores the number of tickets to sell.
                int ticketsToSell = 0;
                cout << "\nEnter tickets to sell (0 to skip): ";
                if (!readInt(ticketsToSell)) {
                    cout << "\nInvalid ticket count.\n";
                    break;
                }

                // Sells tickets when the user enters a non-zero amount.
                if (ticketsToSell != 0) 
                {
                    try {
                        // Updates the stadium occupancy after the sale.
                        selected.sellTickets(ticketsToSell);
                        cout << "\nSold " << ticketsToSell
                             << " ticket(s). Remaining seats: "
                             << selected.getRemainingSeats() << "\n";
                    } catch (const KPFLExceptions& e)
                        {
                        cout << "\n" << e.getMessage() << "\n";
                        }
                }
                break;
            }

            // Displays fixtures scheduled at the selected stadium.
            case 4: {
                if (stadiums.empty()) 
                {
                    cout << "\nNo stadiums registered.\n";
                    break;
                }

                for (size_t i = 0; i < stadiums.size(); ++i) 
                {
                    cout << (i + 1) << ". " << stadiums[i].getStadiumName() << "\n";
                }

                int selection = 0;
                cout << "\nSelect Stadium: ";
                if (!readInt(selection) || selection < 1 || static_cast<size_t>(selection) > stadiums.size())
                {
                    cout << "\nInvalid stadium selection.\n";
                    break;
                }

                Stadium& selected = stadiums[selection - 1];
                // Retrieves the fixtures assigned to the selected stadium.
                vector<Fixture*>& stadiumFixtures = selected.getFixtures();

                // Checks whether the stadium has assigned fixtures.
                if (!stadiumFixtures.empty())
                {
                    cout << "\n========== FIXTURES AT " << selected.getStadiumName() << " ==========\n";
                    // Displays each fixture assigned to the stadium.
                    for (Fixture* f : stadiumFixtures) {
                        if (f != nullptr) {
                            cout << "\nFixture ID: " << f->getFixtureID();
                            cout << "\nStatus: " << f->getFixtureStatus();
                            cout << "\nAttendance: " << f->getAttendance() << "\n";
                        }
                    }
                } else 
                {
                    // Retrieves league fixtures when none are linked to this stadium.
                    vector<Fixture>& leagueFixtures = league.getFixtures();
                    if (leagueFixtures.empty()) 
                    {
                        cout << "\nNo scheduled fixtures available.\n";
                    } else 
                        {
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

            // Returns to the main menu.
            case 0:
                cout << "\nReturning to Main Menu...\n";
                break;

            // Handles invalid menu selections.
            default:
                cout << "\nInvalid option!\n";
                break;
        }
    } while (choice != 0);
}

// Manages shop products, inventory and spectator purchases.
void stadiumShopMenu(){
    int choice = -1;
    // Keeps the shop information available between menu visits.
    static StadiumShop shop(1, "KPFL Stadium Shop", 0, "Main Concourse", 0.0, 0);
    // Stores the products available in the shop.
    static vector<Product*> catalog;

    do {
        // Displays the stadium shop options.
        cout << "\n============ STADIUM SHOP ============\n";
        cout << "1. Add Product\n";
        cout << "2. Display Inventory\n";
        cout << "3. Purchase Product\n";
        cout << "0. Back\n";
        cout << "\nChoice ==> ";

        // Checks that the menu choice is a valid number.
        if (!readInt(choice))
        {
            cout << "\nInvalid choice. Enter a number.\n";
            continue;
        }

        // Performs the selected shop operation.
        switch (choice) {
            // Adds a new product to the shop.
            case 1: {
                int typeChoice = 0;
                cout << "\nProduct Type:\n";
                cout << "1. Food Item\n";
                cout << "2. Merchandise\n";
                cout << "3. Ticket Item\n";
                cout << "Choice ==> ";
                // Validates the selected product type.
                if (!readInt(typeChoice) || typeChoice < 1 || typeChoice > 3) {
                    cout << "\nInvalid product type.\n";
                    break;
                }

                // Generates a product ID and prepares its details.
                int id = generateRandomID();
                int qty = 0;
                double preTaxPrice = 0.0;
                string name;

                // Clears the input line before reading the product name.
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Product Name: ";
                getline(cin, name);

                cout << "Pre-Tax Price: ";
                // Validates the product's pre-tax price.
                if (!readDouble(preTaxPrice) || preTaxPrice < 0.0) 
                {
                    cout << "\nInvalid price.\n";
                    break;
                }

                cout << "Quantity in Stock: ";
                // Validates the quantity available in stock.
                if (!readInt(qty) || qty < 0) 
                {
                    cout << "\nInvalid quantity.\n";
                    break;
                }

                // Holds the product created according to its type.
                Product* prod = nullptr;

                // Creates a food item when that product type is selected.
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

                    // Creates the food item and sets its product details.
                    FoodItems* item = new FoodItems();
                    item->setProductID(id);
                    item->setProductName(name);
                    item->setPrice(preTaxPrice);
                    item->setQuantityInStock(qty);
                    item->setCategory(category);

                    // Stores the food item's expiry date.
                    Date expiryDate;
                    expiryDate.setDay(day);
                    expiryDate.setMonth(month);
                    expiryDate.setYear(year);

                    item->setExpiryDate(expiryDate);

                    prod = item;
                // Creates merchandise when that product type is selected.
                } else if (typeChoice == 2) {
                    string size, brand;
                    cout << "Size: ";
                    getline(cin, size);
                    cout << "Brand: ";
                    getline(cin, brand);
                    // Creates the merchandise item and sets its details.
                    Merchandise* item = new Merchandise();
                    item->setProductID(id);
                    item->setProductName(name);
                    item->setPrice(preTaxPrice);
                    item->setQuantityInStock(qty);
                    item->setSizeOfItem(size);
                    item->setBrand(brand);
                    prod = item;
                // Creates a ticket item when the ticket product type is selected.
                } else {
                    string category, seat;
                    cout << "Ticket Category: ";
                    getline(cin, category);
                    cout << "Seat Number: ";
                    getline(cin, seat);
                    // Creates the ticket item and sets its details.
                    Tickets* item = new Tickets();
                    item->setProductID(id);
                    item->setProductName(name);
                    item->setPrice(preTaxPrice);
                    item->setQuantityInStock(qty);
                    item->setTicketCategory(category);
                    item->setSeatNumber(seat);
                    prod = item;
                }

                // Adds the product after it has been created successfully.
                if (prod != nullptr)
                {
                    // Stores the product in the shop catalog.
                    catalog.push_back(prod);
                    shop.addProduct(prod);
                    cout << "\nProduct added with 15%% GCT. Final Price: $"
                         << prod->getPrice() << "\n";
                }
                break;
            }

            // Displays the shop inventory.
            case 2: {
                // Checks whether the shop contains any products.
                if (catalog.empty())
                {
                    cout << "\nNo products in shop inventory.\n";
                    break;
                }

                cout << "\n========== SHOP INVENTORY ==========";
                cout << "\nShop: " << shop.getShopName()
                     << " | Products: " << shop.getProductCount()
                     << " | Inventory Value: $" << shop.getInventoryValue()
                     << " | Sold: " << shop.getTotalProductsSold() << "\n";

                // Displays each product in the catalog.
                for (size_t i = 0; i < catalog.size(); ++i) {
                    cout << "\n[" << (i + 1) << "]";
                    catalog[i]->Display();
                }
                break;
            }

            // Processes a product purchase.
            case 3: {
                // Checks that products are available for purchase.
                if (catalog.empty()) 
                {
                    cout << "\nNo products available to purchase.\n";
                    break;
                }

                // Checks that a spectator is registered.
                if (spectators.empty())
                {
                    cout << "\nNo spectators registered. Register one in Spectator Management first.\n";
                    break;
                }

                // Checks that a stadium is registered.
                if (stadiums.empty()) 
                {
                    cout << "\nNo stadiums registered.\n";
                    break;
                }

                // Displays spectators so the buyer can be selected.
                cout << "\n========== SELECT SPECTATOR ==========\n";

                for (int i = 0; i < spectators.size(); i++) {
                    cout << i + 1 << ". "
                        << spectators[i].getFullName()
                        << " (Balance: $"
                        << spectators[i].getBalance()
                        << ")\n";
                }

                // Stores the selected spectator.
                int specChoice;

                cout << "Select Spectator: ";
                readInt(specChoice);

                // Validates the spectator selection.
                if (specChoice < 1 || specChoice > spectators.size())
                {
                    cout << "\nInvalid spectator selection.\n";
                    break;
                }

                // Displays products available for purchase.
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

                // Stores the selected product.
                int prodChoice;

                cout << "Select Product: ";
                readInt(prodChoice);

                // Validates the product selection.
                if (prodChoice < 1 || prodChoice > catalog.size())
                {
                    cout << "\nInvalid product selection.\n";
                    break;
                }

                // Displays stadiums for ticket-related purchases.
                cout << "\n========== SELECT STADIUM ==========\n";

                for (int i = 0; i < stadiums.size(); i++)
                    {
                        cout << i + 1 << ". "
                        << stadiums[i].getStadiumName()
                        << "\n";
                    }

                // Stores the selected stadium.
                int stadiumChoice;

                cout << "Select Stadium: ";
                readInt(stadiumChoice);

                // Validates the stadium selection.
                if (stadiumChoice < 1 || stadiumChoice > stadiums.size())
                {
                    cout << "\nInvalid stadium selection.\n";
                    break;
                }

                // Attempts to complete the purchase and update the related records.
                try {
                    // Retrieves the selected spectator, product and stadium.
                    Spectator* specPtr = &spectators[specChoice - 1];
                    
                    Product* prodPtr = catalog[prodChoice - 1];
                    
                    Stadium* stadiumPtr = &stadiums[stadiumChoice - 1];
                    
                    
                    // Checks whether the selected product is a ticket.
                    if (prodPtr->isTicket())
                    {
                        // Checks that the stadium has space for another ticket.
                        if (!stadiumPtr->canSellTickets(1))
                        {
                            throw CapacityExceededException();
                        }
                    
                        stadiumPtr->sellTickets(1);
                    }
                    
                    // Calculates the GCT included in the product price.
                    double includedGCT = shop.calculateIncludedGCT(prodPtr->getPrice());
                    
                    // Processes the purchase transaction.
                    shop.transaction(specPtr,prodPtr);
                    
                    cout << "\nPurchase Complete!\n";
                    cout << "Included GCT: $" << includedGCT << endl;
                    }
                        catch (const KPFLExceptions& e) {
                        cout << "\nTransaction failed: " << e.getMessage() << "\n";
                    }

                break;

            }

            // Returns to the main menu.
            case 0:
                cout << "\nReturning to Main Menu...\n";
                break;

            // Handles invalid menu selections.
            default:
                cout << "\nInvalid option!\n";
                break;
        }
    } while (choice != 0);
}

// Manages match results and league standings.
void resultsMenu(FootballLeague& league)
{
    int choice = -1;
    // Retrieves the league fixtures and teams.
    vector<Fixture>& fixtures = league.getFixtures();
    vector<FootballTeam>& teams = league.getTeams();

    // Stores the details of a recorded fixture result.
    struct RecordedFixtureResult {
        int fixtureID;
        string homeTeamName;
        string awayTeamName;
        MatchResult result;
    };

    // Keeps recorded results available between menu visits.
    static vector<RecordedFixtureResult> recordedResults;

    do {
        // Displays the match results options.
        cout << "\n========== MATCH RESULTS ==========";
        cout << "\n1. Enter Match Result";
        cout << "\n2. Display Result";
        cout << "\n3. View League Standings";
        cout << "\n0. Back";
        cout << "\nChoice ==> ";

        // Checks that the menu choice is a valid number.
        if (!readInt(choice)) 
        {
            cout << "\nInvalid choice. Enter a number.\n";
            continue;
        }

        // Performs the selected results operation.
        switch (choice) 
        {
            // Enters the result for a selected fixture.
            case 1: {
                // Checks whether fixtures are available.
                if (fixtures.empty()) 
                {
                    cout << "\nNo fixtures available.\n";
                    break;
                }

                // Displays the fixtures and their current statuses.
                for (size_t i = 0; i < fixtures.size(); ++i)
                    {
                    cout << (i + 1) << ". Fixture ID: " << fixtures[i].getFixtureID()
                         << " | Status: " << fixtures[i].getFixtureStatus() << "\n";
                }

                int fixtureChoice = 0;
                cout << "\nSelect Fixture: ";
                if (!readInt(fixtureChoice) || fixtureChoice < 1 || static_cast<size_t>(fixtureChoice) > fixtures.size())
                {
                    cout << "\nInvalid fixture selection.\n";
                    break;
                }

                // Retrieves the selected fixture.
                Fixture& fixture = fixtures[fixtureChoice - 1];

                // Prepares pointers for the home and away teams.
                FootballTeam* home = nullptr;
                FootballTeam* away = nullptr;
                // Finds the teams participating in the selected fixture.
                for (FootballTeam& team : teams) {
                    if (team.getTeamID() == fixture.getHomeTeamID())
                    {
                        home = &team;
                    }
                    if (team.getTeamID() == fixture.getAwayTeamID())
                    {
                        away = &team;
                    }
                }

                // Checks that both teams were found.
                if (home == nullptr || away == nullptr)
                {
                    cout << "\nUnable to locate fixture teams.\n";
                    break;
                }

                // Stores the scores and match statistics.
                int homeScore = 0;
                int awayScore = 0;
                string stats;

                // Collects the goals scored by each team.
                cout << "\n" << home->getTeamName() << " Goals: ";
                if (!readInt(homeScore))
                {
                    cout << "\nInvalid input.\n";
                    break;
                }

                cout << away->getTeamName() << " Goals: ";
                if (!readInt(awayScore))
                {
                    cout << "\nInvalid input.\n";
                    break;
                }

                // Clears the input line before reading the match statistics.
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Match Statistics: ";
                getline(cin, stats);

                // Attempts to create and record the match result.
                try {
                    // Creates an object to store the match result.
                    MatchResult matchRes;
                    matchRes.setHomeScore(homeScore);
                    matchRes.setAwayScore(awayScore);
                    matchRes.setMatchStatistics(stats);
                    // Determines the result and updates the teams' league records.
                    matchRes.determineWinner(*home, *away);
                    fixture.recordResults(matchRes);

                    // Checks whether this fixture already has a saved result.
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
                    // Stores the result if no previous record was found.
                    if (!updated)
                    {
                        recordedResults.push_back({
                            fixture.getFixtureID(),
                            home->getTeamName(),
                            away->getTeamName(),
                            matchRes
                        });
                    }

                    cout << "\nMatch result recorded successfully!\n";
                    matchRes.Display();
                // Handles errors raised while recording the result.
                } catch (const KPFLExceptions& e) 
                    {
                    cout << "\n" << e.getMessage() << "\n";
                    }
                break;
            }

            // Displays previously recorded match results.
            case 2: {
                // Checks whether any match results have been recorded.
                if (recordedResults.empty())
                {
                    cout << "\nNo match results recorded yet.\n";
                    break;
                }

                // Displays each saved fixture result.
                for (const RecordedFixtureResult& entry : recordedResults)
                    {
                    cout << "\n----------------------------------";
                    cout << "\nFixture ID: " << entry.fixtureID
                         << " (" << entry.homeTeamName << " vs " << entry.awayTeamName << ")";
                    entry.result.Display();
                }
                break;
            }

            // Displays the current league standings.
            case 3: {
                if (teams.empty())
                {
                    cout << "\nNo registered teams.\n";
                    break;
                }
                // Retrieves and displays the league standings.
                league.getStandings();
                break;
            }

            // Returns to the previous menu.
            case 0:
                cout << "\nReturning to Main Menu...\n";
                break;

            // Handles invalid menu selections.
            default:
                cout << "\nInvalid option!\n";
                break;
        }
    } while (choice != 0);
}

// Provides access to team, fixture, result and standings operations.
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

        // Checks that the menu choice is a valid number.
        if (!readInt(choice))
        {
            cout << "\nInvalid choice. Enter a number.\n";
            continue;
        }

        // Performs the selected league operation.
        switch (choice)
        {
            // REGISTER TEAM
            case 1:
            {
                // Creates a team object to hold the registration details.
                FootballTeam team;

                // Generates a team ID and prepares the team details.
                int id = generateRandomID();
                string name, parish;

                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                cout << "\n========== REGISTER TEAM ==========\n";

                cout << "Team Name: ";
                getline(cin, name);

                cout << "Parish: ";
                getline(cin, parish);

                // Sets the team's ID, name and parish.
                team.setTeamID(id);
                team.setTeamName(name);
                team.setParish(parish);

                // Attempts to register the team with the league.
                // Attempts to record the league result.
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
                // Retrieves the registered teams.
                vector<FootballTeam>& teams = league.getTeams();

                // Ensures that at least two teams are available for a fixture.
                if (teams.size() < 2)
                {
                    cout << "\nAt least two teams are required.\n";
                    break;
                }

                // Displays the teams available for fixture selection.
                cout << "\n========== REGISTERED TEAMS ==========\n";

                for (size_t i = 0; i < teams.size(); ++i)
                {
                    cout << i + 1 << ". "
                         << teams[i].getTeamName()
                         << " (ID: " << teams[i].getTeamID() << ")\n";
                }

                // Stores the selected home and away team numbers.
                int home, away;

                cout << "\nSelect Home Team: ";
                if (!readInt(home)) break;

                cout << "Select Away Team: ";
                if (!readInt(away)) break;

                // Validates the team selections and prevents a team playing itself.
                if (home < 1 || away < 1 ||
                    static_cast<size_t>(home) > teams.size() ||
                    static_cast<size_t>(away) > teams.size() ||
                    home == away)
                {
                    cout << "\nInvalid team selection.\n";
                    break;
                }

                // Stores the fixture ID, date and time.
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

                // Creates a fixture object and sets its details.
                Fixture fixture;

                fixture.setFixtureID(id);
                fixture.setFixtureDate(day, month, year);
                fixture.setFixtureTime(hours, minutes, seconds);
                fixture.setFixtureStatus("Scheduled");

                // Checks whether a stadium is available for the fixture.
                if(stadiums.empty())
                {
                    cout << "\nNo stadiums registered.\n";
                    break;
                }

                cout << "\nREGISTERED STADIUMS\n";

                for(size_t i = 0; i < stadiums.size(); i++)
                {
                    cout << "\n" << i + 1
                        << ". "
                        << stadiums[i].getStadiumName();
                }

                int stadiumChoice;

                cout << "\nSelect Stadium: ";
                cin >> stadiumChoice;

                if(stadiumChoice < 1 ||
                static_cast<size_t>(stadiumChoice) > stadiums.size())
                {
                    cout << "\nInvalid stadium selection.\n";
                    break;
                }

                // Assigns the selected stadium to the fixture.
                fixture.setStadium(
                    &stadiums[stadiumChoice - 1]
                );

                try
                {
                    // Attempts to add the fixture to the league.
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
            // Records the result of a league fixture.
            case 3:
            {
                vector<Fixture>& fixtures = league.getFixtures();
                vector<FootballTeam>& teams = league.getTeams();

                // Checks whether any fixtures are available.
                if (fixtures.empty())
                {
                    cout << "\nNo Fixtures Available.\n";
                    break;
                }

                // Displays the fixtures that can be selected.
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

                // Retrieves the selected fixture.
                Fixture& fixture = fixtures[fixtureChoice - 1];

                // Prevents results from being entered for completed or unavailable fixtures.
                if (fixture.getFixtureStatus() == "Full Time" ||
                    fixture.getFixtureStatus() == "Cancelled" ||
                    fixture.getFixtureStatus() == "Postponed")
                {
                    cout << "\nThis fixture cannot accept a result.\n";
                    break;
                }

                // Prepares pointers for the home and away teams.
                FootballTeam* home = nullptr;
                FootballTeam* away = nullptr;

                // Finds the teams participating in the fixture.
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

                // Stores the goals scored by both teams.
                int homeScore, awayScore;

                cout << "\n" << home->getTeamName() << " Goals: ";
                if (!readInt(homeScore)) break;

                cout << away->getTeamName() << " Goals: ";
                if (!readInt(awayScore)) break;

                try
                {
                    // Creates an object to store the result.
                    MatchResult result;

                    result.setHomeScore(homeScore);
                    result.setAwayScore(awayScore);

                    // Determines the winner and updates league points.
                    result.determineWinner(*home, *away);

                    // Saves the result to the fixture.
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
            // Displays the league standings.
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
            // Displays information about registered teams.
            case 5:
            {
                vector<FootballTeam>& teams = league.getTeams();

                if (teams.empty())
                {
                    cout << "\nNo Registered Teams.\n";
                    break;
                }

                // Displays the registered team details.
                cout << "\n========== REGISTERED TEAMS ==========\n";

                // Finds the names of the teams using their IDs.
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
            // Displays the fixtures in the league.
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

                // Goes through each fixture to display its details.
                for (Fixture& fixture : fixtures)
                {
                    // Prepares the names of the home and away teams.
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

                    // Displays the stadium when one has been assigned.
                    if(fixture.getStadium() != nullptr)
                    {
                        cout << "\nStadium: " << fixture.getStadium()->getStadiumName();
                    }

                    cout << "\nDate: ";
                    fixture.getFixtureDate();

                    cout << "\nTime: ";
                    fixture.getFixtureTime();

                    cout << "\nStatus: " << fixture.getFixtureStatus();

                    cout << "\n----------------------------------\n";
                }

                break;
            }

            // Returns to the previous menu.
            case 0:
                cout << "\nReturning to Main Menu...\n";
                break;

            // Handles invalid menu selections.
            default:
                cout << "\nInvalid Option!\n";
        }

    } while (choice != 0);
}

// Allows the user to test the league system's custom exceptions.
void testExceptions() {

    int choice;

    do {
        // Displays the available exception tests.
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
        // Checks that the menu choice is a valid number.
        if (!readInt(choice)) {
            cout << "\nInvalid choice. Enter a number.\n";
            continue;
        }

        // Attempts to throw the exception selected by the user.
        try {

            // Selects which exception to test.
            switch (choice) {

                // Tests the underage exception.
                case 1:
                    throw UnderageException();

                // Tests the duplicate registration exception.
                case 2:
                    throw DuplicateRegistrationException();

                // Tests the team eligibility exception.
                case 3:
                    throw TeamNotEligibleException();

                // Tests the fixture scheduling conflict exception.
                case 4:
                    throw SchedulingConflictException();

                // Tests the incomplete fixture exception.
                case 5:
                    throw FixtureIncompleteException();

                // Tests the invalid score exception.
                case 6:
                    throw InvalidScoreException();

                // Tests the insufficient payment exception.
                case 7:
                    throw InsufficientPaymentException();

                // Tests the insufficient stock exception.
                case 8:
                    throw InsufficientStockException();

                // Tests the stadium capacity exception.
                case 9:
                    throw CapacityExceededException();

                // Tests the data file exception.
                case 10:
                    throw DataFileException();

                case 0:
                    cout << "\nReturning to previous menu...\n";
                    break;

                default:
                    cout << "\nInvalid choice. Try again.\n";
            }

        }
        // Catches the selected exception and displays its message.
        catch (const KPFLExceptions& e) {
            cout << "\nException successfully caught!";
            cout << "\nError Message: " << e.getMessage() << "\n";
            Sleep(3000);
        }

    } while (choice != 0);
}

void fileManagement(FootballLeague& league){
    int choice;

    // Creates a FileManager object using the data directory.
    FileManager fileManager("data");

    // Repeatedly displays the file management menu until the user returns.
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

        // Validates the menu selection.
        if (!readInt(choice)) {
            cout << "\nInvalid choice. Enter a number.\n";
            continue;
        }

        // Handles file operations and catches related exceptions.
        try {
            switch(choice){
                case 1: {
                    // Retrieves the registered teams.
                    vector<FootballTeam>& teams = league.getTeams();
                    vector<Persistable*> teamRecords;
                    teamRecords.reserve(teams.size());

                    // Converts team addresses into Persistable pointers.
                    for (FootballTeam& team : teams)
                        teamRecords.push_back(&team);

                    // Saves the team records to a file.
                    fileManager.saveTeams(teamRecords.data(), teamRecords.size());
                    cout << "\nTeams saved successfully.\n";
                    break;
                }

                case 2: {
                    // Loads team records from the file.
                    unique_ptr<FootballTeam> teams[100];
                    int count = fileManager.loadTeams(teams, 100);

                    // Replaces the current teams with the loaded teams.
                    league.getTeams().clear();
                    for (int i = 0; i < count; ++i)
                        league.registerTeam(*teams[i]);

                    cout << "\n" << count << " Team(s) loaded successfully.\n";
                    break;
                }

                case 3: {
                    // Retrieves the fixtures and prepares them for saving.
                    vector<Fixture> fixtures = league.getFixtures();
                    vector<Persistable*> fixtureRecords;
                    fixtureRecords.reserve(fixtures.size());

                    // Converts fixture addresses into Persistable pointers.
                    for (Fixture& fixture : fixtures)
                        fixtureRecords.push_back(&fixture);

                    // Saves the fixture records to a file.
                    fileManager.saveFixtures(fixtureRecords.data(), fixtureRecords.size());
                    cout << "\nFixtures saved successfully.\n";
                    break;
                }

                case 4: {
                    // Loads fixture records from the file.
                    unique_ptr<Fixture> fixtures[100];
                    int count = fileManager.loadFixtures(fixtures, 100);
                    league.getFixtures().clear();

                    // Adds the loaded fixtures to the league.
                    for (int i = 0; i < count; ++i)
                        league.getFixtures().push_back(*fixtures[i]);

                    cout << "\n" << count << "Fixture(s) loaded successfully.\n";
                    break;
                }

                case 5: {
                    int count = 0;

                    // Clears the existing people records before saving new ones.
                    fileManager.clearFile(FileManager::PEOPLE_FILE);

                    // Saves player records from each registered team.
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

                        // Saves coach records from each registered team.
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
                    int count = 0;

                    // Reads and displays the saved people records.
                    cout << "\nPeople Records:\n";
                    for (const string& line : fileManager.readLines(FileManager::PEOPLE_FILE)) {
                        cout << line << '\n';
                        ++count;
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
        // Displays an error message if a file operation fails.
        catch (const KPFLExceptions& exception){
            cout << "\nFile operation failed: "
                 << exception.getMessage() << '\n';
        }
    } while (choice != 0);
}

// Provides user a menu with all possible options
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
    cout << "\n14. Reports";
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

// Generate a random number between 1 and 10000
int generateRandomID() {
    return (rand() % 10000) + 1;
}

void reportsMenu(FootballLeague& league){

    int choice;

    // Repeatedly displays the reports menu until the user returns.
    do{
        cout << "\n========== MANAGEMENT REPORTS ==========";
        cout << "\n1. League Standings Report";
        cout << "\n2. Fixture Report";
        cout << "\n3. Stadium Report";
        cout << "\n0. Back";
        cout << "\nChoice ==> ";

        cin >> choice;

        // Executes the selected report.
        switch(choice)
        {
            case 1:
            {
                // Displays the current league standings.
                cout << "\n========== LEAGUE STANDINGS ==========\n";

                league.getStandings();

                break;
            }

            case 2:
            {
                // Displays information about scheduled fixtures.
                cout << "\n========== FIXTURE REPORT ==========\n";

                // Checks whether any fixtures are available.
                if(league.getFixtures().empty())
                {
                    cout << "\nNo fixtures available.\n";
                    break;
                }

                // Displays the details of each fixture.
                for(Fixture& fixture : league.getFixtures())
                {
                    cout << "\nFixture ID: "
                        << fixture.getFixtureID();

                    cout << "\nStatus: "
                        << fixture.getFixtureStatus();

                    cout << "\nDate: ";
                    fixture.getFixtureDate();

                    cout << "\nTime: ";
                    fixture.getFixtureTime();

                    // Displays the stadium if one is assigned.
                    if(fixture.getStadium() != nullptr)
                    {
                        cout << "\nStadium: "
                            << fixture.getStadium()->getStadiumName();
                    }

                    cout << "\n----------------------------------\n";
                }

                break;
            }

            case 3:
            {
                // Displays information about registered stadiums.
                cout << "\n========== STADIUM REPORT ==========\n";

                // Checks whether any stadiums are registered.
                if(stadiums.empty())
                {
                    cout << "\nNo stadiums registered.\n";
                    break;
                }

                // Displays the details of each stadium.
                for(Stadium& stadium : stadiums)
                {
                    cout << "\nStadium ID: "
                        << stadium.getStadiumID();

                    cout << "\nName: "
                        << stadium.getStadiumName();

                    cout << "\nCapacity: "
                        << stadium.getSeatingCapacity();

                    cout << "\nOccupancy: "
                        << stadium.getOccupancy();

                    cout << "\nRemaining Seats: "
                        << stadium.getRemainingSeats();

                    cout << "\nTicket Price: $"
                        << stadium.getTicketPrice();

                    cout << "\n----------------------------------\n";
                }

                break;
            }

            case 0:
                cout << "\nReturning...\n";
                break;

            default:
                cout << "\nInvalid Option!\n";
        }

    }while(choice != 0);

}

void liveMatchMenu(FootballLeague& league)
{
    // Retrieves references to the league's fixtures and registered teams.
    vector<Fixture>& fixtures = league.getFixtures();
    vector<FootballTeam>& teams = league.getTeams();

    // Checks whether any fixtures are available.
    if(fixtures.empty())
    {
        cout << "\nNo fixtures available.\n";
        return;
    }

    cout << "\n========== AVAILABLE FIXTURES ==========\n";

    // Displays all available fixtures and their statuses.
    for(size_t i = 0; i < fixtures.size(); i++)
    {
        cout << "\n" << i + 1
            << ". Fixture ID: " << fixtures[i].getFixtureID()
            << " | Status: " << fixtures[i].getFixtureStatus();
    }

    int choice;

    cout << "\n\nSelect Fixture: ";

    // Validates the user's fixture selection.
    if(!readInt(choice) || choice < 1 ||
    static_cast<size_t>(choice) > fixtures.size())
    {
        cout << "\nInvalid fixture selection.\n";
        return;
    }

    // Retrieves a reference to the selected fixture.
    Fixture& fixture = fixtures[choice - 1];

    // Find the participating teams
    FootballTeam* home = nullptr;
    FootballTeam* away = nullptr;

    // Locates the home and away teams using their IDs.
    for(FootballTeam& team : teams)
    {
        if(team.getTeamID() == fixture.getHomeTeamID())
        {
            home = &team;
        }

        if(team.getTeamID() == fixture.getAwayTeamID())
        {
            away = &team;
        }
    }

    // Checks whether both participating teams were found.
    if(home == nullptr || away == nullptr)
    {
        cout << "\nUnable to locate the participating teams.\n";
        return;
    }

    int option = -1;

    // Repeatedly displays the live match menu until the user returns.
    do
    {
    cout << "\n\n========== LIVE MATCH MANAGEMENT ==========";

    // Displays the current score, match minute and status.
    cout << "\n\n" << home->getTeamName()
         << " " << fixture.getLiveHomeScore()
         << " - " << fixture.getLiveAwayScore()
         << " " << away->getTeamName();

    cout << "\nMatch Minute: " << fixture.getCurrentMinute() << "'";

    cout << "\nMatch Status: " << fixture.getFixtureStatus();

    // Displays the available live match operations.
    cout << "\n\n1. Start Match";
    cout << "\n2. Update Match Minute";
    cout << "\n3. Record Home Team Goal";
    cout << "\n4. Record Away Team Goal";
    cout << "\n5. Half-Time";
    cout << "\n6. Resume Match";
    cout << "\n7. View Match Events";
    cout << "\n8. End Match";
    cout << "\n0. Return";

    cout << "\n\nChoice ==> ";

    // Validates the user's menu selection.
    if(!readInt(option))
    {
        cout << "\nInvalid input.\n";
        continue;
    }

        try
        {
            switch(option)
            {
                // START MATCH
                case 1:
                {
                    fixture.startMatch();

                    cout << "\nMatch started successfully!\n";

                    break;
                }

                // UPDATE MATCH MINUTE
                case 2:
                {
                    int minute;

                    cout << "\nEnter Current Match Minute: ";

                    if(!readInt(minute))
                    {
                        cout << "\nInvalid minute.\n";
                        break;
                    }

                    fixture.updateMatchMinute(minute);

                    cout << "\nMatch minute updated successfully!\n";

                    break;
                }

                // HOME TEAM GOAL
                case 3:
                {
                    fixture.recordLiveGoal(
                        true,
                        home->getTeamName()
                    );

                    cout << "\nGoal recorded for "
                         << home->getTeamName() << "!\n";

                    break;
                }

                // AWAY TEAM GOAL
                case 4:
                {
                    fixture.recordLiveGoal(
                        false,
                        away->getTeamName()
                    );

                    cout << "\nGoal recorded for "
                         << away->getTeamName() << "!\n";

                    break;
                }

                // HALF-TIME
                case 5:
                {
                    fixture.startHalfTime();

                    cout << "\nHalf-time!\n";

                    break;
                }

                // RESUME MATCH
                case 6:
                {
                    fixture.resumeMatch();

                    cout << "\nSecond half has started!\n";

                    break;
                }

                // VIEW MATCH EVENTS
                case 7:
                {
                    cout << "\n========== MATCH EVENTS ==========\n";

                    const vector<string>& events =
                        fixture.getMatchEvents();

                    if(events.empty())
                    {
                        cout << "\nNo match events recorded.\n";
                    }
                    else
                    {
                        for(const string& event : events)
                        {
                            cout << "\n" << event;
                        }
                    }

                    break;
                }

                // END MATCH
                case 8:
                {
                    fixture.finishLiveMatch();

                    MatchResult result;

                    result.setHomeScore(
                        fixture.getLiveHomeScore()
                    );

                    result.setAwayScore(
                        fixture.getLiveAwayScore()
                    );

                    // Combine match events into the statistics
                    string statistics;

                    for(const string& event :
                        fixture.getMatchEvents())
                    {
                        statistics += event + "\n";
                    }

                    result.setMatchStatistics(statistics);

                    // Record the final result
                    fixture.recordResults(result);

                    // Update league points and goal statistics
                    result.determineWinner(*home, *away);

                    // Complete the fixture
                    fixture.completeFixture();

                    cout << "\n========== FULL-TIME ==========\n";

                    cout << "\n" << home->getTeamName()
                         << " " << result.getHomeScore()
                         << " - " << result.getAwayScore()
                         << " " << away->getTeamName();

                    cout << "\nWinner: "
                         << result.getWinner();

                    cout << "\n\nFixture completed successfully!\n";

                    break;
                }

                case 0:
                {
                    cout << "\nReturning to Fixture Management...\n";

                    break;
                }

                default:
                {
                    cout << "\nInvalid option.\n";
                }
            }
        }
        catch(const KPFLExceptions& e)
        {
            cout << "\nOperation failed: "
                 << e.getMessage() << "\n";
        }

    } while(option != 0);
}


