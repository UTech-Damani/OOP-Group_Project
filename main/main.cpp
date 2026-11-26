#include <iostream>
#include <windows.h>

#include <string>
#include <vector>
#include <ctype.h>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <iomanip>
#include <sstream>
#include <cmath>

#include "universal/KPFL.h"
#include "universal/FileManager.h"

using namespace std;

vector<MatchOfficial> officials;
vector<Spectator> spectators;
LeagueCommissioner commissioner;
StadiumShop shop;


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
int selectStadium(FootballLeague& league);
string teamNameFor(FootballLeague& league, int teamID);
void spectatorManagement(FootballLeague& league);
string currentDateTime();
void logRecord(const string& fileName, const string& line);
int selectSpectator(bool allowWalkIn);
void footballLeagueMenu(FootballLeague& league);
void fileManagement(FootballLeague& league);
void reportsMenu(FootballLeague& league);

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

// Lists registered stadiums and returns the chosen stadium ID, or -1 if none/invalid.
int selectStadium(FootballLeague& league)
{
    vector<Stadium>& stadiums = league.getStadiums();

    if (stadiums.empty()) {
        cout << "\nNo stadiums registered. Add one under Stadium Management first.\n";
        return -1;
    }

    cout << "\nREGISTERED STADIUMS\n";
    for (size_t i = 0; i < stadiums.size(); ++i) {
        cout << "\n" << i + 1 << ". " << stadiums[i].getStadiumName()
             << " (ID: " << stadiums[i].getStadiumID()
             << ", Capacity: " << stadiums[i].getSeatingCapacity() << ")";
    }

    int stadiumChoice;
    cout << "\nSelect Stadium: ";
    if (!readInt(stadiumChoice) || stadiumChoice < 1 ||
        static_cast<size_t>(stadiumChoice) > stadiums.size()) {
        cout << "\nInvalid stadium selection.\n";
        return -1;
    }

    return stadiums[stadiumChoice - 1].getStadiumID();
}

string currentDateTime()
{
    time_t now = time(nullptr);
    char buffer[20];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M", localtime(&now));
    return buffer;
}

// Appends a sale record to a CSV log. A logging failure is reported
// but does not undo a sale that has already been completed.
void logRecord(const string& fileName, const string& line)
{
    try {
        FileManager fileManager("data");
        fileManager.appendLine(fileName, line);
    } catch (const KPFLExceptions& e) {
        cout << "\nWarning: sale completed but could not be written to "
             << fileName << ". " << e.getMessage() << '\n';
    }
}

// Lists spectators and returns the chosen index, -1 for a walk-in customer
// (only when allowed), or -2 if the selection is invalid.
int selectSpectator(bool allowWalkIn)
{
    if (spectators.empty()) {
        if (allowWalkIn)
            return -1;
        cout << "No spectators registered.\n";
        return -2;
    }

    for (size_t i = 0; i < spectators.size(); ++i)
        cout << i + 1 << ". " << spectators[i].getFullName() << '\n';

    if (allowWalkIn)
        cout << "0. Walk-in customer\n";

    int spectatorChoice;
    cout << "Select Spectator: ";
    if (!readInt(spectatorChoice)) {
        cout << "Invalid selection.\n";
        return -2;
    }

    if (allowWalkIn && spectatorChoice == 0)
        return -1;

    if (spectatorChoice < 1 ||
        static_cast<size_t>(spectatorChoice) > spectators.size()) {
        cout << "Invalid selection.\n";
        return -2;
    }

    return spectatorChoice - 1;
}

string teamNameFor(FootballLeague& league, int teamID)
{
    FootballTeam* team = league.findTeam(teamID);
    return team != nullptr ? team->getTeamName() : "Unknown";
}

int main()
{
    srand(time(NULL));

    FootballLeague league;
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
                spectatorManagement(league);
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
                
                cout << "\nSelect Team: ";
                cin >> teamChoice;
            
                teamChoice--;

                if (teamChoice < 0 ||
                    static_cast<size_t>(teamChoice) >= league.getTeams().size()) {
                    cout << "\nInvalid Team Selection!\n";
                    break;
                }

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
            
                cout << "\nSelect Team: ";
                cin >> teamChoice;
            
                teamChoice--;

                if (teamChoice < 0 ||
                    static_cast<size_t>(teamChoice) >= league.getTeams().size()) {
                    cout << "\nInvalid Team Selection!\n";
                    break;
                }
    
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
                
                cout << "\nSelect Team: ";
                cin >> teamChoice;
                
                teamChoice--;

                if (teamChoice < 0 ||
                    static_cast<size_t>(teamChoice) >= league.getTeams().size()) {
                    cout << "\nInvalid Team Selection!\n";
                    break;
                }
                
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
            
            // UPDATE TEAM
            case 6: {
                if(league.getTeams().empty()){
                    cout << "\nNo Teams Registered.\n";
                    break;
                }

                int teamID;
                cout << "\nEnter Team ID: ";
                if (!readInt(teamID)) {
                    cout << "\nInvalid Team ID.\n";
                    break;
                }

                FootballTeam* team = league.findTeam(teamID);
                if (team == nullptr) {
                    cout << "\nTeam Not Found!\n";
                    break;
                }

                string name, parish;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                cout << "New Team Name (leave blank to keep \"" << team->getTeamName() << "\"): ";
                getline(cin, name);
                cout << "New Parish (leave blank to keep \"" << team->getParish() << "\"): ";
                getline(cin, parish);

                if (!name.empty())
                    team->setTeamName(name);
                if (!parish.empty())
                    team->setParish(parish);

                cout << "\nTeam Updated Successfully!\n";
                break;
            }

            // SEARCH TEAM (by ID or by name)
            case 7: {
                if(league.getTeams().empty()){
                    cout << "\nNo Teams Registered.\n";
                    break;
                }

                string term;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "\nEnter Team ID or part of the Team Name: ";
                getline(cin, term);

                string lowerTerm = term;
                for (char& c : lowerTerm) c = tolower(c);

                bool found = false;
                for (FootballTeam& team : league.getTeams()) {
                    string lowerName = team.getTeamName();
                    for (char& c : lowerName) c = tolower(c);

                    bool idMatch = to_string(team.getTeamID()) == term;
                    bool nameMatch = !lowerTerm.empty() &&
                                     lowerName.find(lowerTerm) != string::npos;

                    if (idMatch || nameMatch) {
                        found = true;
                        cout << "\n----------------------------------";
                        cout << "\nTeam ID: " << team.getTeamID();
                        cout << "\nTeam Name: " << team.getTeamName();
                        cout << "\nParish: " << team.getParish();
                        cout << "\nStatus: " << team.getTeamStatus();
                        cout << "\nPlayers: " << team.getPlayers().size();
                        cout << "\nCoaches: " << team.getCoaches().size();
                        cout << "\nPoints: " << team.getPoints();
                        cout << "\n----------------------------------\n";
                    }
                }

                if (!found)
                    cout << "\nNo matching team found.\n";
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

                cout << "\nSelect Team: ";
                cin >> teamChoice;

                teamChoice--;

                if (teamChoice < 0 ||
                    static_cast<size_t>(teamChoice) >= league.getTeams().size()) {

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

                for (size_t i = 0; i < league.getTeams().size(); ++i) {
                    cout << i + 1 << ". "
                         << league.getTeams()[i].getTeamName()
                         << endl;
                }

                cout << "\nSelect Team: ";
                cin >> teamChoice;

                teamChoice--;

                if (teamChoice < 0 ||
                    static_cast<size_t>(teamChoice) >= league.getTeams().size()) {

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

                for (size_t i = 0; i < league.getTeams().size(); ++i) {
                    cout << i + 1 << ". "
                         << league.getTeams()[i].getTeamName()
                         << endl;
                }

                cout << "\nSelect Team: ";
                cin >> teamChoice;

                teamChoice--;

                if (teamChoice < 0 ||
                    static_cast<size_t>(teamChoice) >= league.getTeams().size()) {

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

                for (size_t i = 0; i < league.getTeams().size(); ++i) {
                    cout << i + 1 << ". "
                         << league.getTeams()[i].getTeamName()
                         << endl;
                }

                cout << "\nSelect Team: ";
                cin >> teamChoice;

                teamChoice--;

                if (teamChoice < 0 ||
                    static_cast<size_t>(teamChoice) >= league.getTeams().size()) {

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

            // REMOVE PLAYER
            case 5: {
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
                cout << "\nSelect Team: ";
                if (!readInt(teamChoice) || teamChoice < 1 ||
                    static_cast<size_t>(teamChoice) > league.getTeams().size()) {
                    cout << "\nInvalid Team Selection!\n";
                    break;
                }

                int removeID;
                cout << "\nEnter Player ID: ";
                if (!readInt(removeID)) {
                    cout << "\nInvalid ID.\n";
                    break;
                }

                if (league.getTeams()[teamChoice - 1].removePlayer(removeID))
                    cout << "\nPlayer Removed Successfully!\n";
                else
                    cout << "\nPlayer Not Found!\n";
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

                cout << "\nSelect Team: ";
                cin >> teamChoice;

                teamChoice--;

                if (teamChoice < 0 ||
                    static_cast<size_t>(teamChoice) >= league.getTeams().size()) {

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

                for (size_t i = 0; i < league.getTeams().size(); ++i) {
                    cout << i + 1 << ". "
                         << league.getTeams()[i].getTeamName()
                         << endl;
                }

                int teamChoice;

                cout << "\nSelect Team: ";
                cin >> teamChoice;

                teamChoice--;

                if (teamChoice < 0 ||
                    static_cast<size_t>(teamChoice) >= league.getTeams().size()) {

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

                for (size_t i = 0; i < league.getTeams().size(); ++i) {
                    cout << i + 1 << ". "
                         << league.getTeams()[i].getTeamName()
                         << endl;
                }

                int teamChoice;

                cout << "\nSelect Team: ";
                cin >> teamChoice;

                teamChoice--;

                if (teamChoice < 0 ||
                    static_cast<size_t>(teamChoice) >= league.getTeams().size()) {

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

            // REMOVE COACH
            case 4: {
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
                cout << "\nSelect Team: ";
                if (!readInt(teamChoice) || teamChoice < 1 ||
                    static_cast<size_t>(teamChoice) > league.getTeams().size()) {
                    cout << "\nInvalid Team Selection!\n";
                    break;
                }

                int removeID;
                cout << "\nEnter Coach ID: ";
                if (!readInt(removeID)) {
                    cout << "\nInvalid ID.\n";
                    break;
                }

                if (league.getTeams()[teamChoice - 1].removeCoach(removeID))
                    cout << "\nCoach Removed Successfully!\n";
                else
                    cout << "\nCoach Not Found!\n";
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

                try
                {
                    commissioner.assignOfficial(
                        fixtures[fixtureChoice - 1],
                        officials[officialChoice - 1]
                    );

                    cout << "\nOfficial assigned successfully!\n";
                }
                catch (const KPFLExceptions& exception)
                {
                    cout << "\nOfficial could not be assigned: "
                         << exception.getMessage() << '\n';
                }
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

                int stadiumID = selectStadium(league);
                if(stadiumID == -1)
                    break;

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
                proposed.setStadiumID(stadiumID);

                try{
                    league.createFixture(proposed, teams[home - 1], teams[away - 1]);
                    cout << "\nFixture Created Successfully!\n";
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

                try
                {
                    commissioner.assignOfficial(
                        fixtures[fixtureChoice - 1],
                        officials[officialChoice - 1]
                    );

                    cout << "\nOfficial assigned successfully!\n";
                }
                catch (const KPFLExceptions& exception)
                {
                    cout << "\nOfficial could not be assigned: "
                         << exception.getMessage() << '\n';
                }
                break;
            }

            case 3:
            {
                // Results are entered through the Match Results menu,
                // which validates scores and awards league points.
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

                cout << "\nSelect Team: ";
                cin >> teamChoice;

                if(teamChoice < 1 || static_cast<size_t>(teamChoice) > teams.size())
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

                try
                {
                    commissioner.assignOfficial(
                        fixtures[fixtureChoice - 1],
                        officials[officialChoice - 1]
                    );

                    cout << "\nOfficial assigned successfully!\n";
                }
                catch (const KPFLExceptions& exception)
                {
                    cout << "\nOfficial could not be assigned: "
                         << exception.getMessage() << '\n';
                }
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


void spectatorManagement(FootballLeague& league){
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
            // PURCHASE TICKET (limited by stadium seating capacity)
            case 2: {
                int index = selectSpectator(false);
                if (index < 0)
                    break;

                vector<int> openIDs;
                for (Fixture& fixture : league.getFixtures()) {
                    if (fixture.getStadiumID() != 0 && !fixture.hasResult() &&
                        fixture.getFixtureStatus() == "Scheduled") {
                        openIDs.push_back(fixture.getFixtureID());
                        cout << "\n" << openIDs.size() << ". Fixture "
                             << fixture.getFixtureID() << ": "
                             << teamNameFor(league, fixture.getHomeTeamID()) << " vs "
                             << teamNameFor(league, fixture.getAwayTeamID());
                    }
                }

                if (openIDs.empty()) {
                    cout << "No upcoming fixtures with a stadium assigned.\n";
                    break;
                }

                int fixtureChoice, quantity;
                cout << "\nSelect Fixture: ";
                if (!readInt(fixtureChoice) || fixtureChoice < 1 ||
                    static_cast<size_t>(fixtureChoice) > openIDs.size()) {
                    cout << "Invalid fixture selection.\n";
                    break;
                }

                Fixture* fixture = league.findFixture(openIDs[fixtureChoice - 1]);
                Stadium* stadium = league.findStadium(fixture->getStadiumID());
                if (stadium == nullptr) {
                    cout << "The stadium for this fixture is not registered.\n";
                    break;
                }

                int remaining = stadium->getSeatingCapacity() - fixture->getAttendance();
                cout << "Ticket price: $" << fixed << setprecision(2) << stadium->getTicketPrice()
                     << " (GCT inclusive) | Seats remaining: " << remaining << '\n';

                cout << "Number of Tickets: ";
                if (!readInt(quantity) || quantity <= 0) {
                    cout << "Quantity must be at least 1.\n";
                    break;
                }

                try {
                    if (quantity > remaining)
                        throw CapacityExceededException();

                    double total = round(stadium->getTicketPrice() * quantity * 100.0) / 100.0;
                    double amountPaid;
                    cout << "Total due: $" << total << "\nAmount Paid: $";
                    if (!readDouble(amountPaid) || amountPaid < 0) {
                        cout << "Invalid amount.\n";
                        break;
                    }
                    if (amountPaid < total)
                        throw InsufficientPaymentException();

                    double gct = shop.calculateIncludedGCT(total);
                    double subtotal = total - gct;
                    double change = round((amountPaid - total) * 100.0) / 100.0;

                    fixture->setAttendance(fixture->getAttendance() + quantity);

                    Spectator& spectator = spectators[index];
                    spectator.setTicketsPurchased(spectator.getTicketsPurchased() + quantity);
                    spectator.addToTotalSpent(total);

                    cout << "\n============ TICKET RECEIPT ============\n";
                    cout << "Fixture " << fixture->getFixtureID() << " at "
                         << stadium->getStadiumName() << "\n";
                    cout << "General Admission x" << quantity << " @ $"
                         << stadium->getTicketPrice() << "\n";
                    cout << "Subtotal (before GCT): $" << subtotal << "\n";
                    cout << "GCT (15%):             $" << gct << "\n";
                    cout << "Total:                 $" << total << "\n";
                    cout << "Amount Paid:           $" << amountPaid << "\n";
                    cout << "Change:                $" << change << "\n";
                    cout << "========================================\n";

                    int transactionID = generateRandomID();
                    stringstream ticketLine, saleLine;
                    ticketLine << transactionID << "," << fixture->getFixtureID()
                               << ",General," << stadium->getTicketPrice() << ","
                               << quantity << "," << spectator.getIdNom();
                    saleLine << transactionID << "," << currentDateTime()
                             << ",Tickets for fixture " << fixture->getFixtureID()
                             << " x" << quantity << "," << subtotal << "," << gct << ","
                             << total << "," << amountPaid << "," << change;

                    logRecord(FileManager::TICKETS_FILE, ticketLine.str());
                    logRecord(FileManager::TRANSACTIONS_FILE, saleLine.str());
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
    int choice;

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
            // ADD STADIUM
            case 1: {
                int id, capacity, conditionChoice;
                double price;
                string name, location, condition;

                cout << "\nStadium ID: ";
                if (!readInt(id) || id <= 0) {
                    cout << "\nInvalid ID. It must be a positive number.\n";
                    break;
                }

                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Stadium Name: ";
                getline(cin, name);
                cout << "Location: ";
                getline(cin, location);

                if (name.empty() || location.empty()) {
                    cout << "\nName and location cannot be blank.\n";
                    break;
                }

                cout << "Seating Capacity: ";
                if (!readInt(capacity) || capacity <= 0) {
                    cout << "\nInvalid capacity. It must be greater than 0.\n";
                    break;
                }

                cout << "Field Condition (1 = Good, 2 = Fair, 3 = Poor): ";
                if (!readInt(conditionChoice) || conditionChoice < 1 || conditionChoice > 3) {
                    cout << "\nInvalid field condition.\n";
                    break;
                }
                condition = (conditionChoice == 1) ? "Good" :
                            (conditionChoice == 2) ? "Fair" : "Poor";

                cout << "Ticket Price (GCT inclusive): $";
                if (!readDouble(price) || price < 0) {
                    cout << "\nInvalid ticket price.\n";
                    break;
                }

                try {
                    league.addStadiums(Stadium(id, name, location, capacity,
                                               condition, price, 0));
                    cout << "\nStadium Added Successfully!\n";
                } catch (const KPFLExceptions& e) {
                    cout << "\n" << e.getMessage() << '\n';
                }
                break;
            }

            // DISPLAY STADIUMS
            case 2: {
                if (league.getStadiums().empty()) {
                    cout << "\nNo stadiums registered.\n";
                    break;
                }

                for (const Stadium& stadium : league.getStadiums()) {
                    cout << "\n----------------------------------";
                    cout << "\nStadium ID: " << stadium.getStadiumID();
                    cout << "\nName: " << stadium.getStadiumName();
                    cout << "\nLocation: " << stadium.getLocation();
                    cout << "\nSeating Capacity: " << stadium.getSeatingCapacity();
                    cout << "\nField Condition: " << stadium.getFieldCondition();
                    cout << "\nTicket Price: $" << fixed << setprecision(2)
                         << stadium.getTicketPrice();
                    cout << "\n----------------------------------\n";
                }
                break;
            }

            // CHECK CAPACITY (per fixture at the chosen stadium)
            case 3:
            // VIEW SCHEDULED FIXTURES
            case 4: {
                int stadiumID = selectStadium(league);
                if (stadiumID == -1)
                    break;

                Stadium* stadium = league.findStadium(stadiumID);
                bool any = false;

                cout << "\n" << stadium->getStadiumName()
                     << " | Capacity: " << stadium->getSeatingCapacity() << "\n";

                for (Fixture& fixture : league.getFixtures()) {
                    if (fixture.getStadiumID() != stadiumID)
                        continue;

                    any = true;
                    cout << "\nFixture " << fixture.getFixtureID() << ": "
                         << teamNameFor(league, fixture.getHomeTeamID()) << " vs "
                         << teamNameFor(league, fixture.getAwayTeamID());

                    if (choice == 3) {
                        cout << "\n  Tickets sold: " << fixture.getAttendance()
                             << " | Seats remaining: "
                             << stadium->getSeatingCapacity() - fixture.getAttendance() << "\n";
                    } else {
                        Date date = fixture.getFixtureDateMember();
                        ProjectTime time = fixture.getFixtureTimeMember();
                        cout << "\n  Date: " << date.getDay() << "/" << date.getMonth()
                             << "/" << date.getYear()
                             << " | Time: " << setfill('0') << setw(2) << time.getHours()
                             << ":" << setw(2) << time.getMinutes() << setfill(' ')
                             << " | Status: " << fixture.getFixtureStatus() << "\n";
                    }
                }

                if (!any)
                    cout << "\nNo fixtures scheduled at this stadium.\n";
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

void stadiumShopMenu(){
    int choice;

    do {
        cout << "\n============ STADIUM SHOP ============\n";
        cout << "1. Add Product\n";
        cout << "2. Display Inventory\n";
        cout << "3. Purchase Product\n";
        cout << "4. Restock Product\n";
        cout << "0. Back\n";
        cout << "\nChoice ==> ";

        if (!readInt(choice)) {
            cout << "\nInvalid choice. Enter a number.\n";
            continue;
        }

        switch (choice) {
            // ADD PRODUCT
            case 1: {
                int type, id, stock;
                double price;
                string name;

                cout << "\nProduct Type (1 = Merchandise, 2 = Food/Beverage): ";
                if (!readInt(type) || (type != 1 && type != 2)) {
                    cout << "\nInvalid product type.\n";
                    break;
                }

                cout << "Product ID: ";
                if (!readInt(id) || id <= 0) {
                    cout << "\nInvalid ID. It must be a positive number.\n";
                    break;
                }
                if (shop.findProduct(id) != nullptr) {
                    cout << "\n" << DuplicateRegistrationException().getMessage() << '\n';
                    break;
                }

                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Product Name: ";
                getline(cin, name);
                if (name.empty()) {
                    cout << "\nProduct name cannot be blank.\n";
                    break;
                }

                cout << "Price before GCT: $";
                if (!readDouble(price) || price < 0) {
                    cout << "\nInvalid price.\n";
                    break;
                }

                cout << "Quantity in Stock: ";
                if (!readInt(stock) || stock < 0) {
                    cout << "\nQuantity cannot be negative.\n";
                    break;
                }

                Product* product = nullptr;

                if (type == 1) {
                    string size, brand;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Size: ";
                    getline(cin, size);
                    cout << "Brand: ";
                    getline(cin, brand);
                    product = new Merchandise(size, brand, id, name, price, stock);
                } else {
                    string category;
                    int day, month, year;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Category (e.g. Drink, Burger, Popcorn): ";
                    getline(cin, category);
                    cout << "Expiry Day: ";
                    if (!readInt(day)) break;
                    cout << "Expiry Month: ";
                    if (!readInt(month)) break;
                    cout << "Expiry Year: ";
                    if (!readInt(year)) break;
                    product = new FoodItems(Date(day, month, year), category, id, name, price, stock);
                }

                shop.addProduct(product);   // adds 15% GCT to the price
                cout << "\nProduct added. Selling price incl. GCT: $"
                     << fixed << setprecision(2) << product->getPrice() << "\n";
                break;
            }

            // DISPLAY INVENTORY (polymorphic Display through Product*)
            case 2:
                if (shop.getProducts().empty()) {
                    cout << "\nNo products in inventory.\n";
                    break;
                }
                for (Product* product : shop.getProducts())
                    product->Display();
                break;

            // PURCHASE PRODUCT(S)
            case 3: {
                if (shop.getProducts().empty()) {
                    cout << "\nNo products in inventory.\n";
                    break;
                }

                int index = selectSpectator(true);
                if (index == -2)
                    break;

                vector<StadiumShop::SaleLine> cart;

                while (true) {
                    cout << "\nID    Product              Price      Stock\n";
                    for (Product* product : shop.getProducts()) {
                        cout << left << setw(6) << product->getProductID()
                             << setw(21) << product->getProductName()
                             << "$" << setw(10) << fixed << setprecision(2) << product->getPrice()
                             << product->getQuantityInStock() << '\n';
                    }

                    int productID, quantity;
                    cout << "Product ID to add (0 to checkout): ";
                    if (!readInt(productID)) {
                        cout << "Invalid ID.\n";
                        continue;
                    }
                    if (productID == 0)
                        break;

                    Product* product = shop.findProduct(productID);
                    if (product == nullptr) {
                        cout << "Product not found.\n";
                        continue;
                    }

                    cout << "Quantity: ";
                    if (!readInt(quantity) || quantity <= 0) {
                        cout << "Quantity must be at least 1.\n";
                        continue;
                    }

                    bool merged = false;
                    for (StadiumShop::SaleLine& line : cart) {
                        if (line.product == product) {
                            line.quantity += quantity;
                            merged = true;
                        }
                    }
                    if (!merged)
                        cart.push_back({product, quantity});
                }

                if (cart.empty()) {
                    cout << "\nNo items selected.\n";
                    break;
                }

                double cartTotal = 0.0;
                for (const StadiumShop::SaleLine& line : cart)
                    cartTotal += line.product->getPrice() * line.quantity;

                double amountPaid;
                cout << "\nTotal due: $" << fixed << setprecision(2) << cartTotal
                     << "\nAmount Paid: $";
                if (!readDouble(amountPaid) || amountPaid < 0) {
                    cout << "Invalid amount.\n";
                    break;
                }

                try {
                    double subtotal, gct, total, change;
                    shop.checkout(cart, amountPaid, subtotal, gct, total, change);
                    StadiumShop::printReceipt(cart, subtotal, gct, total, amountPaid, change);

                    stringstream items;
                    for (const StadiumShop::SaleLine& line : cart) {
                        items << line.product->getProductName() << " x" << line.quantity << " ";
                    }

                    if (index >= 0) {
                        for (const StadiumShop::SaleLine& line : cart)
                            for (int i = 0; i < line.quantity; ++i)
                                spectators[index].buyProduct(line.product->getPrice());
                    }

                    stringstream saleLine;
                    saleLine << generateRandomID() << "," << currentDateTime() << ","
                             << items.str() << "," << subtotal << "," << gct << ","
                             << total << "," << amountPaid << "," << change;
                    logRecord(FileManager::TRANSACTIONS_FILE, saleLine.str());
                } catch (const KPFLExceptions& e) {
                    cout << "\nTransaction cancelled: " << e.getMessage() << '\n';
                }
                break;
            }

            // RESTOCK PRODUCT
            case 4: {
                int productID, amount;
                cout << "\nProduct ID: ";
                if (!readInt(productID)) {
                    cout << "\nInvalid ID.\n";
                    break;
                }

                Product* product = shop.findProduct(productID);
                if (product == nullptr) {
                    cout << "\nProduct not found.\n";
                    break;
                }

                cout << "Quantity to add: ";
                if (!readInt(amount) || amount <= 0) {
                    cout << "\nQuantity must be at least 1.\n";
                    break;
                }

                product->increaseStock(amount);
                cout << "\n" << product->getProductName() << " now has "
                     << product->getQuantityInStock() << " in stock.\n";
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

void resultsMenu(FootballLeague& league){
    int choice;

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
            // ENTER MATCH RESULT (awards points: win = 3, draw = 1, loss = 0)
            case 1: {
                vector<Fixture>& fixtures = league.getFixtures();
                vector<int> openIDs;

                for (Fixture& fixture : fixtures) {
                    if (!fixture.hasResult() &&
                        fixture.getFixtureStatus() != "Cancelled" &&
                        fixture.getFixtureStatus() != "Postponed") {
                        openIDs.push_back(fixture.getFixtureID());
                        cout << "\n" << openIDs.size() << ". Fixture "
                             << fixture.getFixtureID() << ": "
                             << teamNameFor(league, fixture.getHomeTeamID()) << " vs "
                             << teamNameFor(league, fixture.getAwayTeamID());
                    }
                }

                if (openIDs.empty()) {
                    cout << "\nNo fixtures are waiting for a result.\n";
                    break;
                }

                int fixtureChoice;
                cout << "\nSelect Fixture: ";
                if (!readInt(fixtureChoice) || fixtureChoice < 1 ||
                    static_cast<size_t>(fixtureChoice) > openIDs.size()) {
                    cout << "\nInvalid fixture selection.\n";
                    break;
                }

                Fixture* fixture = league.findFixture(openIDs[fixtureChoice - 1]);
                int homeScore, awayScore;

                cout << teamNameFor(league, fixture->getHomeTeamID()) << " Goals: ";
                if (!readInt(homeScore)) {
                    cout << "\nInvalid score.\n";
                    break;
                }
                cout << teamNameFor(league, fixture->getAwayTeamID()) << " Goals: ";
                if (!readInt(awayScore)) {
                    cout << "\nInvalid score.\n";
                    break;
                }

                try {
                    MatchResult result;
                    result.setHomeScore(homeScore);   // throws InvalidScoreException if negative
                    result.setAwayScore(awayScore);

                    league.recordFixtureResult(fixture->getFixtureID(), result);
                    cout << "\nResult recorded and league points awarded.\n";
                } catch (const KPFLExceptions& e) {
                    cout << "\n" << e.getMessage() << '\n';
                }
                break;
            }

            // DISPLAY RESULT
            case 2: {
                bool any = false;

                for (Fixture& fixture : league.getFixtures()) {
                    if (!fixture.hasResult())
                        continue;

                    any = true;
                    MatchResult result = fixture.getResult();
                    string home = teamNameFor(league, fixture.getHomeTeamID());
                    string away = teamNameFor(league, fixture.getAwayTeamID());
                    string winner = result.getHomeScore() > result.getAwayScore() ? home :
                                    result.getAwayScore() > result.getHomeScore() ? away : "Draw";

                    cout << "\nFixture " << fixture.getFixtureID() << ": "
                         << home << " " << result.getHomeScore() << " - "
                         << result.getAwayScore() << " " << away
                         << " | Winner: " << winner
                         << " | Status: " << fixture.getFixtureStatus() << "\n";
                }

                if (!any)
                    cout << "\nNo results recorded yet.\n";
                break;
            }

            // VIEW STANDINGS
            case 3:
                if (league.getTeams().empty())
                    cout << "\nNo Registered Teams.\n";
                else
                    league.getStandings();
                break;

            case 0:
                cout << "\nReturning to previous menu...\n";
                break;

            default:
                cout << "\nInvalid choice. Try again.\n";
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

                int stadiumID = selectStadium(league);
                if (stadiumID == -1)
                    break;

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
                fixture.setStadiumID(stadiumID);

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

                    Stadium* venue = league.findStadium(fixture.getStadiumID());
                    cout << "\nStadium: "
                         << (venue != nullptr ? venue->getStadiumName() : "Not assigned");

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

// ---------- persistence helpers (one per data file) ----------

vector<string> splitFields(const string& line, char delimiter)
{
    vector<string> fields;
    stringstream ss(line);
    string field;
    while (getline(ss, field, delimiter))
        fields.push_back(field);
    if (!line.empty() && line.back() == delimiter)
        fields.push_back("");   // keep a trailing empty field (e.g. a blank status)
    return fields;
}

void saveTeamsFile(FootballLeague& league, FileManager& fileManager)
{
    vector<FootballTeam>& teams = league.getTeams();
    vector<Persistable*> teamRecords;
    for (FootballTeam& team : teams)
        teamRecords.push_back(&team);

    fileManager.saveTeams(teamRecords.data(), teamRecords.size());
    cout << "\n" << teams.size() << " team(s) saved.\n";
}

void loadTeamsFile(FootballLeague& league, FileManager& fileManager)
{
    unique_ptr<FootballTeam> teams[100];
    int count = fileManager.loadTeams(teams, 100);

    league.getTeams().clear();
    for (int i = 0; i < count; ++i)
        league.addFootBallTeams(*teams[i]);   // keeps the saved status (e.g. suspended)

    league.setNumberOfTeams(count);
    cout << "\n" << count << " team(s) loaded.\n";
}

void saveFixturesFile(FootballLeague& league, FileManager& fileManager)
{
    vector<Fixture>& fixtures = league.getFixtures();
    vector<Persistable*> fixtureRecords;
    for (Fixture& fixture : fixtures)
        fixtureRecords.push_back(&fixture);

    fileManager.saveFixtures(fixtureRecords.data(), fixtureRecords.size());
    cout << "\n" << fixtures.size() << " fixture(s) saved.\n";
}

void loadFixturesFile(FootballLeague& league, FileManager& fileManager)
{
    unique_ptr<Fixture> fixtures[100];
    int count = fileManager.loadFixtures(fixtures, 100);

    league.getFixtures().clear();
    for (int i = 0; i < count; ++i)
        league.getFixtures().push_back(*fixtures[i]);

    cout << "\n" << count << " fixture(s) loaded.\n";
}

// people.csv: type|teamID|id|name|age|gender|subtype fields...
void savePeopleFile(FootballLeague& league, FileManager& fileManager)
{
    vector<string> lines;

    for (FootballTeam& team : league.getTeams()) {
        for (Player& player : team.getPlayers()) {
            lines.push_back("Player|" + to_string(team.getTeamID()) + "|" +
                to_string(player.getIdNom()) + "|" + player.getFullName() + "|" +
                to_string(player.getAge()) + "|" + player.getGender() + "|" +
                player.getPositionOnField() + "|" + to_string(player.getJerseyNom()) + "|" +
                to_string(player.getGoalScored()) + "|" + player.getPlayerStatus());
        }

        for (Coach& coach : team.getCoaches()) {
            lines.push_back("Coach|" + to_string(team.getTeamID()) + "|" +
                to_string(coach.getIdNom()) + "|" + coach.getFullName() + "|" +
                to_string(coach.getAge()) + "|" + coach.getGender() + "|" +
                coach.getQualification() + "|" + coach.getCoachingRole() + "|" +
                to_string(coach.getYearsExperience()));
        }
    }

    for (MatchOfficial& official : officials) {
        lines.push_back("Official|0|" + to_string(official.getIdNom()) + "|" +
            official.getFullName() + "|" + to_string(official.getAge()) + "|" +
            official.getGender() + "|" + official.getOfficiatingRole() + "|" +
            official.getRank() + "|" + (official.getAvailability() ? "1" : "0") + "|" +
            to_string(official.getYearsExperience()));
    }

    for (Spectator& spectator : spectators) {
        stringstream line;
        line << "Spectator|0|" << spectator.getIdNom() << "|" << spectator.getFullName()
             << "|" << spectator.getAge() << "|" << spectator.getGender() << "|"
             << spectator.getTicketsPurchased() << "|" << spectator.getTotalAmountSpent()
             << "|" << spectator.getBalance();
        lines.push_back(line.str());
    }

    fileManager.saveLines(FileManager::PEOPLE_FILE, lines);
    cout << "\n" << lines.size() << " person record(s) saved.\n";
}

// Load teams first so players and coaches can be put back on their team.
void loadPeopleFile(FootballLeague& league, FileManager& fileManager)
{
    vector<string> lines = fileManager.readLines(FileManager::PEOPLE_FILE);

    for (FootballTeam& team : league.getTeams()) {
        team.getPlayers().clear();
        team.getCoaches().clear();
    }
    officials.clear();
    spectators.clear();

    int loaded = 0, skipped = 0;

    for (const string& line : lines) {
        vector<string> f = splitFields(line, '|');

        try {
            if (f.size() < 6)
                throw DataFileException();

            string type = f[0];
            int teamID = stoi(f[1]);
            int id = stoi(f[2]);
            int age = stoi(f[4]);

            if (type == "Player" && f.size() >= 10) {
                FootballTeam* team = league.findTeam(teamID);
                if (team == nullptr)
                    throw DataFileException();
                Player player(id, f[3], age, f[5], f[6], stoi(f[7]), stoi(f[8]), f[9]);
                team->addPlayer(player);
            }
            else if (type == "Coach" && f.size() >= 9) {
                FootballTeam* team = league.findTeam(teamID);
                if (team == nullptr)
                    throw DataFileException();
                Coach coach(id, f[3], age, f[5], f[6], f[7], stoi(f[8]));
                team->addCoach(coach);
            }
            else if (type == "Official" && f.size() >= 10) {
                officials.push_back(MatchOfficial(id, f[3], age, f[5], f[6], f[7],
                                                  f[8] == "1", stoi(f[9])));
            }
            else if (type == "Spectator" && f.size() >= 9) {
                spectators.push_back(Spectator(id, f[3], age, f[5], stoi(f[6]),
                                               stod(f[7]), stod(f[8])));
            }
            else {
                throw DataFileException();
            }
            ++loaded;
        }
        catch (const KPFLExceptions&) { ++skipped; }
        catch (const exception&) { ++skipped; }   // stoi/stod on a malformed field
    }

    cout << "\n" << loaded << " person record(s) loaded.";
    if (skipped > 0)
        cout << " " << skipped << " malformed or orphaned record(s) skipped.";
    cout << '\n';
}

void saveStadiumsFile(FootballLeague& league, FileManager& fileManager)
{
    vector<string> lines;
    for (const Stadium& stadium : league.getStadiums())
        lines.push_back(stadium.toFileString());

    fileManager.saveLines(FileManager::STADIUMS_FILE, lines);
    cout << "\n" << lines.size() << " stadium(s) saved.\n";
}

void loadStadiumsFile(FootballLeague& league, FileManager& fileManager)
{
    vector<string> lines = fileManager.readLines(FileManager::STADIUMS_FILE);

    league.getStadiums().clear();
    for (const string& line : lines)
        league.addStadiums(Stadium::fromFileString(line));

    cout << "\n" << lines.size() << " stadium(s) loaded.\n";
}

// products.csv: type,id,name,price incl. GCT,stock,then subtype fields
void saveProductsFile(FileManager& fileManager)
{
    vector<string> lines;

    for (Product* product : shop.getProducts()) {
        stringstream line;
        line << fixed << setprecision(2);

        if (Merchandise* item = dynamic_cast<Merchandise*>(product)) {
            line << "Merchandise," << item->getProductID() << "," << item->getProductName()
                 << "," << item->getPrice() << "," << item->getQuantityInStock() << ","
                 << item->getSizeOfItem() << "," << item->getBrand();
        }
        else if (FoodItems* item = dynamic_cast<FoodItems*>(product)) {
            Date expiry = item->getExpiryDate();
            line << "Food," << item->getProductID() << "," << item->getProductName()
                 << "," << item->getPrice() << "," << item->getQuantityInStock() << ","
                 << item->getCategory() << "," << expiry.getDay() << ","
                 << expiry.getMonth() << "," << expiry.getYear();
        }
        else {
            continue;
        }

        lines.push_back(line.str());
    }

    fileManager.saveLines(FileManager::PRODUCTS_FILE, lines);
    cout << "\n" << lines.size() << " product(s) saved.\n";
}

void loadProductsFile(FileManager& fileManager)
{
    vector<string> lines = fileManager.readLines(FileManager::PRODUCTS_FILE);

    shop.clearProducts();
    int loaded = 0, skipped = 0;

    for (const string& line : lines) {
        vector<string> f = splitFields(line, ',');

        try {
            if (f.size() >= 7 && f[0] == "Merchandise") {
                shop.addTaxInclusiveProduct(new Merchandise(f[5], f[6], stoi(f[1]), f[2],
                                                            stod(f[3]), stoi(f[4])));
                ++loaded;
            }
            else if (f.size() >= 9 && f[0] == "Food") {
                Date expiry(stoi(f[6]), stoi(f[7]), stoi(f[8]));
                shop.addTaxInclusiveProduct(new FoodItems(expiry, f[5], stoi(f[1]), f[2],
                                                          stod(f[3]), stoi(f[4])));
                ++loaded;
            }
            else {
                ++skipped;
            }
        }
        catch (const exception&) { ++skipped; }
    }

    cout << "\n" << loaded << " product(s) loaded.";
    if (skipped > 0)
        cout << " " << skipped << " malformed record(s) skipped.";
    cout << '\n';
}

void fileManagement(FootballLeague& league){
    int choice;

    do {
        cout << "\n===== FILE MANAGER =====\n";
        cout << "\n 1. Save Teams";
        cout << "\n 2. Load Teams";
        cout << "\n 3. Save Fixtures";
        cout << "\n 4. Load Fixtures";
        cout << "\n 5. Save People";
        cout << "\n 6. Load People (load teams first)";
        cout << "\n 7. Save Stadiums";
        cout << "\n 8. Load Stadiums";
        cout << "\n 9. Save Products";
        cout << "\n10. Load Products";
        cout << "\n11. Save All";
        cout << "\n12. Load All";
        cout << "\n 0. Back";
        cout << "\nChoice ==> ";
        if (!readInt(choice)) {
            cout << "\nInvalid choice. Enter a number.\n";
            continue;
        }

        try {
            FileManager fileManager("data");

            switch(choice){
                case 1: saveTeamsFile(league, fileManager); break;
                case 2: loadTeamsFile(league, fileManager); break;
                case 3: saveFixturesFile(league, fileManager); break;
                case 4: loadFixturesFile(league, fileManager); break;
                case 5: savePeopleFile(league, fileManager); break;
                case 6: loadPeopleFile(league, fileManager); break;
                case 7: saveStadiumsFile(league, fileManager); break;
                case 8: loadStadiumsFile(league, fileManager); break;
                case 9: saveProductsFile(fileManager); break;
                case 10: loadProductsFile(fileManager); break;

                case 11:
                    saveTeamsFile(league, fileManager);
                    saveStadiumsFile(league, fileManager);
                    saveFixturesFile(league, fileManager);
                    savePeopleFile(league, fileManager);
                    saveProductsFile(fileManager);
                    break;

                case 12:
                    // Order matters: people are attached to teams that must already exist.
                    loadTeamsFile(league, fileManager);
                    loadStadiumsFile(league, fileManager);
                    loadFixturesFile(league, fileManager);
                    loadPeopleFile(league, fileManager);
                    loadProductsFile(fileManager);
                    break;

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

// ---------- management reports ----------

void reportsMenu(FootballLeague& league)
{
    int choice;

    do {
        cout << "\n============== REPORTS ==============";
        cout << "\n1. League Standings";
        cout << "\n2. Fixture Attendance and Ticket Revenue";
        cout << "\n3. Sales and Inventory";
        cout << "\n0. Back";
        cout << "\nChoice ==> ";

        if (!readInt(choice)) {
            cout << "\nInvalid choice. Enter a number.\n";
            continue;
        }

        switch (choice) {
            case 1:
                if (league.getTeams().empty())
                    cout << "\nNo Registered Teams.\n";
                else
                    league.getStandings();
                break;

            case 2: {
                if (league.getFixtures().empty()) {
                    cout << "\nNo fixtures available.\n";
                    break;
                }

                double totalRevenue = 0.0;
                int totalTickets = 0;

                cout << "\n================ FIXTURE ATTENDANCE REPORT ================\n";
                cout << left << setw(6) << "ID" << setw(30) << "Match" << setw(14) << "Status"
                     << setw(12) << "Sold/Cap" << "Revenue\n";
                cout << "-----------------------------------------------------------------------\n";

                for (Fixture& fixture : league.getFixtures()) {
                    Stadium* stadium = league.findStadium(fixture.getStadiumID());
                    string match = teamNameFor(league, fixture.getHomeTeamID()) + " vs " +
                                   teamNameFor(league, fixture.getAwayTeamID());
                    string soldCap = to_string(fixture.getAttendance()) + "/" +
                                     (stadium ? to_string(stadium->getSeatingCapacity()) : "?");
                    double revenue = stadium ? fixture.getAttendance() * stadium->getTicketPrice() : 0.0;

                    totalRevenue += revenue;
                    totalTickets += fixture.getAttendance();

                    cout << left << setw(6) << fixture.getFixtureID() << setw(30) << match.substr(0, 29)
                         << setw(14) << fixture.getFixtureStatus() << setw(12) << soldCap
                         << "$" << fixed << setprecision(2) << revenue << '\n';
                }

                cout << "-----------------------------------------------------------------------\n";
                cout << "Tickets sold: " << totalTickets
                     << " | Ticket revenue (GCT incl.): $" << totalRevenue << '\n';
                break;
            }

            case 3: {
                cout << "\n================ SALES AND INVENTORY REPORT ================\n";

                // Sales history comes from the transaction log, so it includes earlier sessions.
                int transactionCount = 0;
                double revenue = 0.0, gct = 0.0;
                try {
                    FileManager fileManager("data");
                    for (const string& line : fileManager.readLines(FileManager::TRANSACTIONS_FILE)) {
                        vector<string> f = splitFields(line, ',');
                        if (f.size() < 8)
                            continue;
                        gct += stod(f[f.size() - 4]);
                        revenue += stod(f[f.size() - 3]);
                        ++transactionCount;
                    }
                } catch (const KPFLExceptions&) {
                    // no transactions logged yet
                } catch (const exception&) {
                    cout << "Some transaction records could not be read.\n";
                }

                cout << fixed << setprecision(2);
                cout << "Transactions (tickets and shop): " << transactionCount << '\n';
                cout << "Total revenue (GCT incl.):       $" << revenue << '\n';
                cout << "GCT collected:                   $" << gct << '\n';

                cout << "\nINVENTORY\n";
                if (shop.getProducts().empty()) {
                    cout << "No products in inventory.\n";
                    break;
                }

                cout << left << setw(6) << "ID" << setw(22) << "Product" << setw(12) << "Price"
                     << setw(8) << "Stock" << "Note\n";
                for (Product* product : shop.getProducts()) {
                    cout << left << setw(6) << product->getProductID()
                         << setw(22) << product->getProductName().substr(0, 21)
                         << "$" << setw(11) << product->getPrice()
                         << setw(8) << product->getQuantityInStock()
                         << (product->getQuantityInStock() == 0 ? "OUT OF STOCK" :
                             product->getQuantityInStock() <= 5 ? "Low stock" : "")
                         << '\n';
                }
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

int generateRandomID() {
    return (rand() % 10000) + 1;
}