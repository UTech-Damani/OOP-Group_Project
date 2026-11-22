#include <iostream>

#include <string>
#include <KPFLExceptions.h>
#include <vector>

#include "KPFL.h"

using namespace std;

void displayMainMenu();

int main()
{
    cout << "Za Wurldo!" << endl;
    return 0;
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