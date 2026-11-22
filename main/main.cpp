#include <iostream>

#include <string>
#include <vector>

#include "universal/KPFL.h"

using namespace std;

void displayMainMenu();

int main()
{
    cout << "Za Wurldo!" << endl;

    displayMainMenu();

    return 0;
}

void teamManagementMenu(){

    cout << "\n==================================================";
    cout << "\n      TEAM MANAGEMENT";
    cout << "\n==================================================";
    cout << "\n 1. Create Team";
    cout << "\n 2. Add Player";
    cout << "\n 3. Add Coach";
    cout << "\n 4. Display Team";
    cout << "\nChoice ==> ";
}

void playerMenu(){
    cout << "\n========== PLAYER MANAGEMENT ==========";
    cout << "\n1. Register Player";
    cout << "\n2. Update Player";
    cout << "\n3. Display Player";
    cout << "\n4. Check Eligibility";
    cout << "\n0. Back";
    cout << "\nChoice ==> ";
}

void coachMenu(){
    cout << "\n========== COACH MANAGEMENT ==========";
    cout << "\n1. Register Coach";
    cout << "\n2. Display Coach";
    cout << "\n3. Update Experience";
    cout << "\n0. Back";
    cout << "\nChoice ==> ";
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

void displayMainMenu()
{
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
}