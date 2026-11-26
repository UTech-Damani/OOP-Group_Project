#include <iostream>
#ifdef _WIN32
#include <windows.h>
#else
#include <thread>
#include <chrono>
inline void Sleep(unsigned long ms) { std::this_thread::sleep_for(std::chrono::milliseconds(ms)); }
#endif

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
vector<Product*> shopProducts;
StadiumShop kpflShop;
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
void spectatorManagement(FootballLeague& league);
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

void loadStartupData(FootballLeague& league)
{
    FileManager manager("data");
    try {
        ifstream checkTeams("data/teams.csv");
        if (checkTeams) {
            unique_ptr<FootballTeam> loaded[500];
            int count=manager.loadTeams(loaded,500);
            for(int i=0;i<count;++i) league.getTeams().push_back(*loaded[i]);
        }
        ifstream checkStadiums("data/stadiums.csv");
        if (checkStadiums) {
            unique_ptr<Stadium> loaded[200];
            int count=manager.loadStadiums(loaded,200);
            for(int i=0;i<count;++i) league.getStadiums().push_back(*loaded[i]);
        }
        ifstream checkFixtures("data/fixtures.csv");
        if (checkFixtures) {
            unique_ptr<Fixture> loaded[1000];
            int count=manager.loadFixtures(loaded,1000);
            for(int i=0;i<count;++i) league.getFixtures().push_back(*loaded[i]);
        }
        for (Stadium& stadium : league.getStadiums()) stadium.clearFixtures();
        for (Fixture& fixture : league.getFixtures()) {
            for (Stadium& stadium : league.getStadiums())
                if (stadium.getStadiumID()==fixture.getStadiumID()) {
                    fixture.setStadium(&stadium);
                    stadium.addFixture(&fixture);
                    break;
                }
        }
        ifstream savedResults("data/results.csv");
        string resultLine;
        while(savedResults && getline(savedResults,resultLine)) {
            if(resultLine.empty()) continue;
            vector<string> f; string value; stringstream rs(resultLine);
            while(getline(rs,value,'|')) f.push_back(value);
            try {
                if(f.size()>=4) {
                    int fixtureID=stoi(f[0]);
                    for(const Fixture& fixture : league.getFixtures()) {
                        if(fixture.getFixtureID()==fixtureID && !fixture.hasResult()) {
                            MatchResult result; result.setHomeScore(stoi(f[1])); result.setAwayScore(stoi(f[2]));
                            if(f.size()>4) result.setMatchStatistics(f[4]);
                            league.recordFixtureResult(fixtureID,result);
                            break;
                        }
                    }
                }
            } catch (...) { cerr << "Skipped malformed result record.\n"; }
        }
        ifstream people("data/people.csv");
        string line;
        while(people && getline(people,line)) {
            if(line.empty()) continue;
            vector<string> f; string value; stringstream ss(line);
            while(getline(ss,value,'|')) f.push_back(value);
            try {
                if(f.size()>=10 && f[0]=="Player") {
                    FootballTeam* team=league.findTeam(stoi(f[9])); if(!team) continue;
                    Player person(stoi(f[1]),f[2],stoi(f[3]),f[4],f[5],stoi(f[6]),stoi(f[7]),f[8]);
                    team->addPlayer(person);
                } else if(f.size()>=9 && f[0]=="Coach") {
                    FootballTeam* team=league.findTeam(stoi(f[8])); if(!team) continue;
                    Coach person(stoi(f[1]),f[2],stoi(f[3]),f[4],f[5],f[6],stoi(f[7]));
                    team->addCoach(person);
                } else if(f.size()>=9 && f[0]=="Official") {
                    officials.push_back(MatchOfficial(stoi(f[1]),f[2],stoi(f[3]),f[4],f[5],f[6],f[7]=="1",stoi(f[8])));
                } else if(f.size()>=8 && f[0]=="Spectator") {
                    spectators.push_back(Spectator(stoi(f[1]),f[2],stoi(f[3]),f[4],stoi(f[5]),stod(f[6]),stod(f[7])));
                }
            } catch (...) { cerr << "Skipped malformed people record.\n"; }
        }
        for (Fixture& fixture : league.getFixtures()) {
            for (int officialID : fixture.getAssignedOfficialIDs()) {
                for (MatchOfficial& official : officials) {
                    if (official.getIdNom()==officialID && official.assignFixture(fixture)) {
                        fixture.addOfficial(&official);
                        break;
                    }
                }
            }
        }
        ifstream products("data/products.csv");
        while(products && getline(products,line)) {
            if(line.empty()) continue;
            try {
                vector<string> f; string value; stringstream ss(line);
                while(getline(ss,value,'|')) f.push_back(value);
                Product* item=nullptr;
                if(f.size()>=7 && f[0]=="M") item=new Merchandise(f[5],f[6],stoi(f[1]),f[2],stod(f[3]),stoi(f[4]));
                else if(f.size()>=9 && f[0]=="F") item=new FoodItems(Date(stoi(f[5]),stoi(f[6]),stoi(f[7])),f[8],stoi(f[1]),f[2],stod(f[3]),stoi(f[4]));
                else if(f.size()>=10 && f[0]=="T") item=new Tickets(f[5],Date(stoi(f[6]),stoi(f[7]),stoi(f[8])),f[9],stoi(f[1]),f[2],stod(f[3]),stoi(f[4]));
                if(item) { shopProducts.push_back(item); kpflShop.addProduct(item,false); }
            } catch (...) { cerr << "Skipped malformed product record.\n"; }
        }
    } catch (const KPFLExceptions& e) {
        cerr << "Startup data could not be completely loaded: " << e.getMessage() << '\n';
    }
}

int main()
{
    srand(time(NULL));

    FootballLeague league;
    officials.reserve(100);
    spectators.reserve(500);
    loadStartupData(league);
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

                }catch(const KPFLExceptions& e){

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

            case 5: {
                vector<FootballTeam>& teams = league.getTeams();
                for (size_t i=0;i<teams.size();++i) cout << i+1 << ". " << teams[i].getTeamName() << '\n';
                int ti, pid; cout << "Select team: "; if(!readInt(ti)) break;
                if(ti<1 || static_cast<size_t>(ti)>teams.size()) break;
                cout << "Player ID to remove: "; if(!readInt(pid)) break;
                cout << (teams[ti-1].removePlayer(pid) ? "Player removed.\n" : "Player not found.\n");
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
                        string qualification, role;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "New qualification (Level 1/Level 2/Level 3): ";
                        getline(cin, qualification);
                        cout << "New coaching role (Head Coach/Assistant Coach/Goalkeeping Coach): ";
                        getline(cin, role);
                        cout << "New years of experience: ";
                        if (!readInt(experience) || experience < 0) {
                            cout << "Invalid years of experience.\n";
                            break;
                        }
                        coach.setQualification(qualification);
                        coach.setCoachingRole(role);
                        coach.setYearsExperience(experience);
                        cout << "Coach details updated.\n";

                        break;
                    }
                }

                if (!found) {
                    cout << "\nCoach Not Found!\n";
                }

                break;
            }

            case 4: {
                vector<FootballTeam>& teams=league.getTeams();
                for(size_t i=0;i<teams.size();++i) cout << i+1 << ". " << teams[i].getTeamName() << '\n';
                int ti,cid; cout << "Select team: "; if(!readInt(ti)) break;
                if(ti<1 || static_cast<size_t>(ti)>teams.size()) break;
                cout << "Coach ID to remove: "; if(!readInt(cid)) break;
                cout << (teams[ti-1].removeCoach(cid) ? "Coach removed.\n" : "Coach not found.\n");
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

                vector<Stadium>& stadiums = league.getStadiums();
                if (stadiums.empty()) {
                    cout << "Register a stadium before scheduling fixtures.\n";
                    break;
                }
                for (size_t i = 0; i < stadiums.size(); ++i)
                    cout << "\n" << i + 1 << ". " << stadiums[i].getStadiumName()
                         << " (ID " << stadiums[i].getStadiumID() << ")";
                int stadiumChoice;
                cout << "\nSelect Stadium: ";
                if (!readInt(stadiumChoice) || stadiumChoice < 1 ||
                    static_cast<size_t>(stadiumChoice) > stadiums.size()) {
                    cout << "Invalid stadium selection.\n";
                    break;
                }

                Fixture proposed;
                proposed.setFixtureID(id);
                proposed.setFixtureDate(day, month, year);
                proposed.setFixtureTime(hours, minutes, seconds);
                proposed.setFixtureStatus("Scheduled");
                proposed.assignStadiumID(stadiums[stadiumChoice - 1].getStadiumID());

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
                if (fixtures.empty()) { cout << "No fixtures available.\n"; break; }
                for (size_t i=0; i<fixtures.size(); ++i)
                    cout << "\n" << i+1 << ". Fixture ID: " << fixtures[i].getFixtureID();
                int selected, homeScore, awayScore;
                cout << "\nSelect fixture: ";
                if (!readInt(selected) || selected<1 || static_cast<size_t>(selected)>fixtures.size()) { cout << "Invalid fixture.\n"; break; }
                cout << "Home score: "; if (!readInt(homeScore)) { cout << "Invalid score.\n"; break; }
                cout << "Away score: "; if (!readInt(awayScore)) { cout << "Invalid score.\n"; break; }
                try {
                    MatchResult result;
                    result.setHomeScore(homeScore);
                    result.setAwayScore(awayScore);
                    league.recordFixtureResult(fixtures[selected-1].getFixtureID(), result);
                    cout << "Result recorded and league statistics updated.\n";
                } catch (const KPFLExceptions& e) { cout << e.getMessage() << '\n'; }
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

                vector<Fixture>& fixtures = league.getFixtures();
                if (fixtures.empty()) { cout << "No fixtures are scheduled.\n"; break; }
                for (size_t i=0; i<fixtures.size(); ++i)
                    cout << "\n" << i+1 << ". Fixture " << fixtures[i].getFixtureID()
                         << " | Stadium ID: " << fixtures[i].getStadiumID();
                int fixtureChoice;
                cout << "\nSelect fixture: ";
                if (!readInt(fixtureChoice) || fixtureChoice<1 || static_cast<size_t>(fixtureChoice)>fixtures.size()) { cout << "Invalid fixture.\n"; break; }
                Fixture& fixture = fixtures[fixtureChoice-1];
                Stadium* selectedStadium = nullptr;
                for (Stadium& st : league.getStadiums())
                    if (st.getStadiumID()==fixture.getStadiumID()) { selectedStadium=&st; break; }
                if (!selectedStadium) { cout << "Fixture stadium was not found.\n"; break; }
                try {
                    Spectator& spectator = spectators[spectatorChoice - 1];
                    const double price = selectedStadium->getTicketPrice();
                    if (!selectedStadium->canSellTickets(1)) throw CapacityExceededException();
                    spectator.deductBalance(price);
                    try { selectedStadium->sellTickets(1); }
                    catch (...) { spectator.setBalance(spectator.getBalance() + price); throw; }
                    spectator.buyTicket();
                    spectator.addToTotalSpent(price);
                    FileManager ticketFiles("data");
                    ticketFiles.appendLine(FileManager::TICKETS_FILE,
                        to_string(spectator.getIdNom()) + "|" +
                        to_string(fixture.getFixtureID()) + "|" +
                        to_string(selectedStadium->getStadiumID()) + "|" + to_string(price));
                    cout << "Ticket purchased for $" << price << ".\n";
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
        cout << "\n========== STADIUM MANAGEMENT =========="
             << "\n1. Register Stadium\n2. Display Stadiums\n3. Check Capacity\n4. View Scheduled Fixtures\n0. Back\nChoice ==> ";
        if (!readInt(choice)) { cout << "Invalid input.\n"; continue; }
        try {
            if (choice == 1) {
                int id, capacity; double price; string name, location, condition;
                cout << "Stadium ID: "; if(!readInt(id)) continue;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Stadium name: "; getline(cin,name);
                cout << "Location: "; getline(cin,location);
                cout << "Seating capacity: "; if(!readInt(capacity)) continue;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Field condition (Good/Fair/Poor): "; getline(cin,condition);
                cout << "Ticket price: $"; if(!readDouble(price)) continue;
                if (id<=0 || capacity<=0 || price<0 || name.empty()) { cout << "Invalid stadium details.\n"; continue; }
                for (const Stadium& st : league.getStadiums())
                    if (st.getStadiumID()==id) throw DuplicateRegistrationException();
                league.addStadiums(Stadium(id,name,location,capacity,condition,price,0));
                cout << "Stadium registered.\n";
            } else if (choice == 2) {
                if (league.getStadiums().empty()) cout << "No stadiums registered.\n";
                for (const Stadium& st : league.getStadiums())
                    cout << "\nID: " << st.getStadiumID() << " | " << st.getStadiumName()
                         << " | " << st.getLocation() << " | Capacity: " << st.getSeatingCapacity()
                         << " | Occupancy: " << st.getOccupancy() << " | Ticket: $" << st.getTicketPrice();
            } else if (choice == 3) {
                int id, quantity; cout << "Stadium ID: "; if(!readInt(id)) continue;
                cout << "Number of tickets: "; if(!readInt(quantity)) continue;
                bool found=false;
                for (const Stadium& st : league.getStadiums()) if(st.getStadiumID()==id) {
                    found=true; cout << (st.canSellTickets(quantity) ? "Capacity available.\n" : "Insufficient capacity or invalid quantity.\n"); break;
                }
                if(!found) cout << "Stadium not found.\n";
            } else if (choice == 4) {
                for (const Fixture& f : league.getFixtures()) {
                    cout << "\nFixture " << f.getFixtureID() << " | Stadium ID: " << f.getStadiumID()
                         << " | Status: " << f.getFixtureStatus();
                }
            } else if (choice != 0) cout << "Invalid choice.\n";
        } catch (const KPFLExceptions& e) { cout << e.getMessage() << '\n'; }
    } while(choice != 0);
}

void stadiumShopMenu(){
    int choice;
    do {
        cout << "\n============ STADIUM SHOP ============\n1. Add Product\n2. Display Inventory\n3. Purchase Product\n4. Restock Product\n5. Remove Product\n0. Back\nChoice ==> ";
        if(!readInt(choice)) { cout << "Invalid input.\n"; continue; }
        if(choice==1) {
            int type, id, quantity; double price; string name;
            cout << "1. Merchandise  2. Food item: "; if(!readInt(type) || (type!=1 && type!=2)) continue;
            cout << "Product ID: "; if(!readInt(id)) continue;
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout << "Product name: "; getline(cin,name);
            cout << "Pre-tax price: $"; if(!readDouble(price)) continue;
            cout << "Quantity: "; if(!readInt(quantity)) continue;
            if(id<=0 || quantity<0 || price<0) { cout << "Invalid product details.\n"; continue; }
            bool duplicate=false; for(Product* p:shopProducts) if(p && p->getProductID()==id) duplicate=true;
            if(duplicate) { cout << "Duplicate product ID.\n"; continue; }
            Product* product=nullptr;
            if(type==1) {
                string size,brand; cout << "Brand: "; getline(cin,brand); cout << "Size: "; getline(cin,size);
                product=new Merchandise(size,brand,id,name,price,quantity);
            } else {
                int day,month,year; string category;
                cout << "Expiry day: "; if(!readInt(day)) continue;
                cout << "Expiry month: "; if(!readInt(month)) continue;
                cout << "Expiry year: "; if(!readInt(year)) continue;
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                cout << "Category: "; getline(cin,category);
                Date expiry(day,month,year);
                product=new FoodItems(expiry,category,id,name,price,quantity);
            }
            shopProducts.push_back(product); kpflShop.addProduct(product);
            cout << "Product added. Price including 15% GCT: $" << product->getPrice() << '\n';
        } else if(choice==2) {
            if(shopProducts.empty()) cout << "Inventory is empty.\n";
            for(Product* p:shopProducts) if(p) p->Display();
        } else if(choice==3) {
            if(spectators.empty() || shopProducts.empty()) { cout << "Register a spectator and add products first.\n"; continue; }
            for(size_t i=0;i<spectators.size();++i) cout << i+1 << ". " << spectators[i].getFullName() << '\n';
            int si, pi; cout << "Select spectator: "; if(!readInt(si)) continue;
            if(si<1 || static_cast<size_t>(si)>spectators.size()) continue;
            for(size_t i=0;i<shopProducts.size();++i) cout << i+1 << ". " << shopProducts[i]->getProductName() << " ($" << shopProducts[i]->getPrice() << ") stock " << shopProducts[i]->getQuantityInStock() << '\n';
            cout << "Select product: "; if(!readInt(pi)) continue;
            if(pi<1 || static_cast<size_t>(pi)>shopProducts.size()) continue;
            try {
                Product* purchased = shopProducts[pi-1];
                double tendered;
                cout << "Cash tendered: $";
                if(!readDouble(tendered)) break;
                double change = kpflShop.transactionWithCash(&spectators[si-1],purchased,tendered);
                FileManager records("data");
                records.appendLine(FileManager::TRANSACTIONS_FILE,
                    to_string(spectators[si-1].getIdNom()) + "|" +
                    to_string(purchased->getProductID()) + "|" +
                    purchased->getProductName() + "|" + to_string(purchased->getPrice()));
                const double includedTax = kpflShop.calculateIncludedGCT(purchased->getPrice());
                cout << "Purchase complete.\n"
                     << "Price including GCT: $" << purchased->getPrice() << '\n'
                     << "GCT included: $" << includedTax << '\n'
                     << "Change: $" << change << '\n';
            } catch(const KPFLExceptions& e) { cout << e.getMessage() << '\n'; }
        } else if(choice==4) {
            if(shopProducts.empty()) { cout << "Inventory is empty.\n"; continue; }
            for(size_t i=0;i<shopProducts.size();++i) cout << i+1 << ". " << shopProducts[i]->getProductName() << " stock " << shopProducts[i]->getQuantityInStock() << '\n';
            int selected, quantity; cout << "Select product: "; if(!readInt(selected)) continue;
            if(selected<1 || static_cast<size_t>(selected)>shopProducts.size()) continue;
            cout << "Quantity to add: "; if(!readInt(quantity)) continue;
            try { shopProducts[selected-1]->increaseStock(quantity); cout << "Stock updated.\n"; }
            catch(const KPFLExceptions& e) { cout << e.getMessage() << '\n'; }
        } else if(choice==5) {
            if(shopProducts.empty()) { cout << "Inventory is empty.\n"; continue; }
            for(size_t i=0;i<shopProducts.size();++i) cout << i+1 << ". " << shopProducts[i]->getProductName() << '\n';
            int selected; cout << "Select product to remove: "; if(!readInt(selected)) continue;
            if(selected<1 || static_cast<size_t>(selected)>shopProducts.size()) continue;
            Product* removed=shopProducts[selected-1];
            kpflShop.removeProduct(removed); shopProducts.erase(shopProducts.begin()+selected-1); delete removed;
            cout << "Product removed.\n";
        } else if(choice!=0) cout << "Invalid choice.\n";
    } while(choice!=0);
}

void resultsMenu(FootballLeague& league){
    int choice;
    do {
        cout << "\n========== MATCH RESULTS ==========\n1. Enter Match Result\n2. Display Results\n3. View League Standings\n0. Back\nChoice ==> ";
        if(!readInt(choice)) { cout << "Invalid input.\n"; continue; }
        if(choice==1) {
            if(league.getFixtures().empty()) { cout << "No fixtures.\n"; continue; }
            for(const Fixture& f:league.getFixtures()) cout << "\nFixture ID: " << f.getFixtureID() << " Status: " << f.getFixtureStatus();
            int id, hs, as; cout << "\nFixture ID: "; if(!readInt(id)) continue;
            cout << "Home score: "; if(!readInt(hs)) continue;
            cout << "Away score: "; if(!readInt(as)) continue;
            try { MatchResult result; result.setHomeScore(hs); result.setAwayScore(as); league.recordFixtureResult(id,result); cout << "Result recorded.\n"; }
            catch(const KPFLExceptions& e) { cout << e.getMessage() << '\n'; }
        } else if(choice==2) {
            for(const Fixture& f:league.getFixtures()) if(f.hasResult()) { cout << "\nFixture " << f.getFixtureID() << ": "; f.getResult().Display(); }
        } else if(choice==3) league.getStandings();
        else if(choice!=0) cout << "Invalid choice.\n";
    } while(choice!=0);
}

void footballLeagueMenu(FootballLeague& league){
    int choice;
    do {
        cout << "\n========== FOOTBALL LEAGUE ==========\n1. Register Team\n2. Update Team\n3. Search Team\n4. View Standings\n5. Display Teams\n6. Display Fixtures\n7. Management Reports\n8. Demonstrate Person Polymorphism\n0. Back\nChoice ==> ";
        if(!readInt(choice)) { cout << "Invalid input.\n"; continue; }
        if(choice==1) {
            int id; string name, parish;
            cout << "Team ID: "; if(!readInt(id)) continue;
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout << "Team name: "; getline(cin,name); cout << "Parish: "; getline(cin,parish);
            try { FootballTeam team; team.setTeamID(id); team.setTeamName(name); team.setParish(parish); team.setTeamStatus("registered"); league.registerTeam(team); }
            catch(const KPFLExceptions& e) { cout << e.getMessage() << '\n'; }
        } else if(choice==2) {
            int id; string name, parish; cout << "Team ID: "; if(!readInt(id)) continue;
            cin.ignore(numeric_limits<streamsize>::max(),'\n'); cout << "New team name: "; getline(cin,name); cout << "New parish: "; getline(cin,parish);
            cout << (league.updateTeam(id,name,parish) ? "Team updated.\n" : "Team not found or details invalid.\n");
        } else if(choice==3) {
            int id; cout << "Team ID: "; if(!readInt(id)) continue;
            const FootballTeam* t=league.findTeam(id);
            if(t) cout << "\n" << t->getTeamName() << " | " << t->getParish() << " | " << t->getTeamStatus() << " | Points: " << t->getPoints() << '\n';
            else cout << "Team not found.\n";
        } else if(choice==4) league.getStandings();
        else if(choice==5) { for(const FootballTeam& t:league.getTeams()) cout << "\n" << t.getTeamID() << " | " << t.getTeamName() << " | " << t.getParish() << " | " << t.getTeamStatus(); }
        else if(choice==6) { for(const Fixture& f:league.getFixtures()) f.Display(); }
        else if(choice==7) {
            cout << "\nREPORT 1: LEAGUE STANDINGS\n"; league.getStandings();
            cout << "\nREPORT 2: FIXTURE SCHEDULE\n"; for(const Fixture& f:league.getFixtures()) f.Display();
            cout << "\nREPORT 3: STADIUM CAPACITY\n";
            for(const Stadium& st:league.getStadiums()) cout << st.getStadiumName() << " | Occupancy " << st.getOccupancy() << "/" << st.getSeatingCapacity() << " | Remaining " << st.getRemainingSeats() << '\n';
            ofstream standingsFile("data/report_standings.txt",ios::trunc);
            if(standingsFile) {
                standingsFile << "TEAM,PLAYED,WINS,DRAWS,LOSSES,GOALS_FOR,GOALS_AGAINST,GOAL_DIFFERENCE,POINTS\n";
                for(const FootballTeam& t:league.getTeams()) standingsFile << t.getTeamName() << "," << (t.getWins()+t.getDraws()+t.getLosses()) << "," << t.getWins() << "," << t.getDraws() << "," << t.getLosses() << "," << t.getGoalsFor() << "," << t.getGoalsAgainst() << "," << t.getGoalDifference() << "," << t.getPoints() << '\n';
            }
            ofstream fixturesFile("data/report_fixtures.txt",ios::trunc);
            if(fixturesFile) for(const Fixture& f:league.getFixtures()) fixturesFile << f.getFixtureID() << "," << f.getHomeTeamID() << "," << f.getAwayTeamID() << "," << f.getStadiumID() << "," << f.getFixtureStatus() << "," << f.hasResult() << '\n';
            ofstream stadiumFile("data/report_stadiums.txt",ios::trunc);
            if(stadiumFile) for(const Stadium& st:league.getStadiums()) stadiumFile << st.getStadiumID() << "," << st.getStadiumName() << "," << st.getOccupancy() << "," << st.getSeatingCapacity() << "," << st.getRemainingSeats() << '\n';
            cout << "\nThree report files were written to the data folder.\n";
        } else if(choice==8) {
            bool displayed=false;
            for(FootballTeam& team:league.getTeams()) {
                for(Player& player:team.getPlayers()) {
                    Person* person=&player;
                    person->Display(); displayed=true;
                }
                for(Coach& coach:team.getCoaches()) {
                    Person* person=&coach;
                    person->Display(); displayed=true;
                }
            }
            for(MatchOfficial& official:officials) { Person* person=&official; person->Display(); displayed=true; }
            for(Spectator& spectator:spectators) { Person* person=&spectator; person->Display(); displayed=true; }
            if(!displayed) cout << "No Person-derived objects are available.\n";
        } else if(choice!=0) cout << "Invalid choice.\n";
    } while(choice!=0);
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
        cout << "\n 7. Save Stadiums";
        cout << "\n 8. Load Stadiums";
        cout << "\n 9. Save Products";
        cout << "\n10. Load Products";
        cout << "\n11. View Ticket Records";
        cout << "\n12. View Transactions";
        cout << "\n13. Save Results";
        cout << "\n14. Load Results";
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
                    for (int i = 0; i < count; ++i) {
                        league.getTeams().push_back(*teams[i]);
                        league.getTeams().back().rebindMembers();
                    }
                    league.setNumberOfTeams(count);
                    cout << "\n" << count << " Team(s) loaded successfully.\n";
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
                    for (Fixture& fixture : league.getFixtures())
                        for (int officialID : fixture.getAssignedOfficialIDs())
                            for (MatchOfficial& official : officials)
                                if (official.getIdNom()==officialID && official.assignFixture(fixture)) {
                                    fixture.addOfficial(&official); break;
                                }
                    cout << "\n" << count << " Fixture(s) loaded successfully.\n";
                    break;
                }

                case 5: {
                    ofstream output("data/people.csv", ios::trunc);
                    if(!output) throw DataFileException();
                    int count=0;
                    for(FootballTeam& team:league.getTeams()) {
                        for(Player& player:team.getPlayers()) {
                            output << "Player|" << player.getIdNom() << "|" << player.getFullName() << "|"
                                   << player.getAge() << "|" << player.getGender() << "|"
                                   << player.getPositionOnField() << "|" << player.getJerseyNom() << "|"
                                   << player.getGoalScored() << "|" << player.getPlayerStatus() << "|"
                                   << team.getTeamID() << '\n'; ++count;
                        }
                        for(Coach& coach:team.getCoaches()) {
                            output << "Coach|" << coach.getIdNom() << "|" << coach.getFullName() << "|"
                                   << coach.getAge() << "|" << coach.getGender() << "|"
                                   << coach.getQualification() << "|" << coach.getCoachingRole() << "|"
                                   << coach.getYearsExperience() << "|" << team.getTeamID() << '\n'; ++count;
                        }
                    }
                    for(MatchOfficial& official:officials) {
                        output << "Official|" << official.getIdNom() << "|" << official.getFullName() << "|"
                               << official.getAge() << "|" << official.getGender() << "|"
                               << official.getOfficiatingRole() << "|" << official.getRank() << "|"
                               << (official.getAvailability()?1:0) << "|" << official.getYearsExperience() << '\n'; ++count;
                    }
                    for(Spectator& spectator:spectators) {
                        output << "Spectator|" << spectator.getIdNom() << "|" << spectator.getFullName() << "|"
                               << spectator.getAge() << "|" << spectator.getGender() << "|"
                               << spectator.getTicketsPurchased() << "|" << spectator.getTotalAmountSpent() << "|"
                               << spectator.getBalance() << '\n'; ++count;
                    }
                    if(!output) throw DataFileException();
                    cout << count << " people records saved.\n";
                    break;
                }

                case 6: {
                    ifstream input("data/people.csv");
                    if(!input) throw DataFileException();
                    for(FootballTeam& team:league.getTeams()) { team.getPlayers().clear(); team.getCoaches().clear(); }
                    officials.clear(); spectators.clear();
                    string line; int count=0;
                    while(getline(input,line)) {
                        if(line.empty()) continue;
                        vector<string> f; string value; stringstream parser(line);
                        while(getline(parser,value,'|')) f.push_back(value);
                        try {
                            if(f.size()>=10 && f[0]=="Player") {
                                FootballTeam* team=league.findTeam(stoi(f[9])); if(!team) continue;
                                Player person(stoi(f[1]),f[2],stoi(f[3]),f[4],f[5],stoi(f[6]),stoi(f[7]),f[8]);
                                team->addPlayer(person); ++count;
                            } else if(f.size()>=9 && f[0]=="Coach") {
                                FootballTeam* team=league.findTeam(stoi(f[8])); if(!team) continue;
                                Coach person(stoi(f[1]),f[2],stoi(f[3]),f[4],f[5],f[6],stoi(f[7]));
                                team->addCoach(person); ++count;
                            } else if(f.size()>=9 && f[0]=="Official") {
                                officials.push_back(MatchOfficial(stoi(f[1]),f[2],stoi(f[3]),f[4],f[5],f[6],f[7]=="1",stoi(f[8]))); ++count;
                            } else if(f.size()>=8 && f[0]=="Spectator") {
                                spectators.push_back(Spectator(stoi(f[1]),f[2],stoi(f[3]),f[4],stoi(f[5]),stod(f[6]),stod(f[7]))); ++count;
                            }
                        } catch (...) { throw DataFileException(); }
                    }
                    for (Fixture& fixture : league.getFixtures()) {
                        for (int officialID : fixture.getAssignedOfficialIDs()) {
                            for (MatchOfficial& official : officials) {
                                if (official.getIdNom()==officialID && official.assignFixture(fixture)) {
                                    fixture.addOfficial(&official);
                                    break;
                                }
                            }
                        }
                    }
                    cout << count << " people reconstructed.\n";
                    break;
                }

                case 7: {
                    vector<Persistable*> records;
                    for (Stadium& stadium : league.getStadiums()) records.push_back(&stadium);
                    fileManager.saveStadiums(records.data(), static_cast<int>(records.size()));
                    cout << "Stadiums saved.\n";
                    break;
                }
                case 8: {
                    unique_ptr<Stadium> loaded[100];
                    int count=fileManager.loadStadiums(loaded,100);
                    league.getStadiums().clear();
                    for(int i=0;i<count;++i) league.getStadiums().push_back(*loaded[i]);
                    for(Stadium& stadium:league.getStadiums()) stadium.clearFixtures();
                    for(Fixture& fixture:league.getFixtures()) for(Stadium& stadium:league.getStadiums())
                        if(stadium.getStadiumID()==fixture.getStadiumID()) { fixture.setStadium(&stadium); stadium.addFixture(&fixture); break; }
                    cout << count << " stadium(s) loaded.\n";
                    break;
                }

                case 9: {
                    ofstream out("data/products.csv", ios::trunc);
                    if(!out) throw DataFileException();
                    for(Product* product : shopProducts) if(product) {
                        if (Merchandise* m=dynamic_cast<Merchandise*>(product))
                            out << "M|" << m->getProductID() << "|" << m->getProductName() << "|" << m->getPrice() << "|" << m->getQuantityInStock() << "|" << m->getSizeOfItem() << "|" << m->getBrand() << "\n";
                        else if (FoodItems* f=dynamic_cast<FoodItems*>(product)) {
                            Date d=f->getExpiryDate();
                            out << "F|" << f->getProductID() << "|" << f->getProductName() << "|" << f->getPrice() << "|" << f->getQuantityInStock() << "|" << d.getDay() << "|" << d.getMonth() << "|" << d.getYear() << "|" << f->getCategory() << "\n";
                        } else if (Tickets* t=dynamic_cast<Tickets*>(product)) {
                            Date d=t->getMatchDate();
                            out << "T|" << t->getProductID() << "|" << t->getProductName() << "|" << t->getPrice() << "|" << t->getQuantityInStock() << "|" << t->getTicketCategory() << "|" << d.getDay() << "|" << d.getMonth() << "|" << d.getYear() << "|" << t->getSeatNumber() << "\n";
                        }
                    }
                    cout << "Products saved.\n";
                    break;
                }
                case 10: {
                    ifstream in("data/products.csv"); if(!in) throw DataFileException();
                    for(Product* product : shopProducts) delete product;
                    shopProducts.clear(); kpflShop.clearInventory();
                    string line;
                    while(getline(in,line)) {
                        stringstream ss(line); vector<string> f; string value;
                        while(getline(ss,value,'|')) f.push_back(value);
                        if(f.size()<5) throw DataFileException();
                        Product* product=nullptr;
                        if(f[0]=="M" && f.size()>=7)
                            product=new Merchandise(f[5],f[6],stoi(f[1]),f[2],stod(f[3]),stoi(f[4]));
                        else if(f[0]=="F" && f.size()>=9)
                            product=new FoodItems(Date(stoi(f[5]),stoi(f[6]),stoi(f[7])),f[8],stoi(f[1]),f[2],stod(f[3]),stoi(f[4]));
                        else if(f[0]=="T" && f.size()>=10)
                            product=new Tickets(f[5],Date(stoi(f[6]),stoi(f[7]),stoi(f[8])),f[9],stoi(f[1]),f[2],stod(f[3]),stoi(f[4]));
                        else throw DataFileException();
                        shopProducts.push_back(product); kpflShop.addProduct(product,false);
                    }
                    cout << shopProducts.size() << " product(s) loaded.\n";
                    break;
                }
                case 11: {
                    ifstream in("data/tickets.csv"); if(!in) throw DataFileException();
                    string line; while(getline(in,line)) cout << line << '\n';
                    break;
                }
                case 12: {
                    ifstream in("data/transactions.csv"); if(!in) throw DataFileException();
                    string line; while(getline(in,line)) cout << line << '\n';
                    break;
                }

                case 13: {
                    ofstream out("data/results.csv",ios::trunc);
                    if(!out) throw DataFileException();
                    for(const Fixture& fixture:league.getFixtures()) if(fixture.hasResult()) {
                        MatchResult result=fixture.getResult();
                        out << fixture.getFixtureID() << "|" << result.getHomeScore() << "|"
                            << result.getAwayScore() << "|" << result.getWinner() << "|"
                            << result.getMatchStatistics() << '\n';
                    }
                    cout << "Match results saved.\n";
                    break;
                }
                case 14: {
                    ifstream in("data/results.csv"); if(!in) throw DataFileException();
                    string line; int loaded=0;
                    while(getline(in,line)) {
                        vector<string> f; string value; stringstream rs(line);
                        while(getline(rs,value,'|')) f.push_back(value);
                        if(f.size()<4) throw DataFileException();
                        int fixtureID=stoi(f[0]);
                        for(const Fixture& fixture:league.getFixtures()) {
                            if(fixture.getFixtureID()==fixtureID && !fixture.hasResult()) {
                                MatchResult result; result.setHomeScore(stoi(f[1])); result.setAwayScore(stoi(f[2]));
                                if(f.size()>4) result.setMatchStatistics(f[4]);
                                league.recordFixtureResult(fixtureID,result); ++loaded; break;
                            }
                        }
                    }
                    cout << loaded << " result(s) loaded.\n";
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