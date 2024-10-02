#include <iostream>
#include "deck.h"
#include "money.h"

using namespace std;

void displayMenu() {
    cout << "\n======= Jack Black Black Jack Game Menu =====\n";
    cout << "1. New Game\n";
    cout << "2. Load Game\n";
    cout << "3. Save Game\n";
    cout << "4. Exit\n";
    cout << "================================================\n";
    cout << "Choose an option: ";
}

int main() {
    Deck deck("deck.txt");
    Money money("money.txt");
    bool exitGame = false;

    while (!exitGame) {
        displayMenu();

        int choice;

        cin >> choice;

        string firstCard = deck.dealCard();
        cout << "Your first card is: " << firstCard << " \n";

        int card1Val = deck.getValue(firstCard);
        
        cout << "Your first card value is: " << card1Val << "\n";

        int funds = money.getMoney("money.txt");

        cout << "Your amount of money is " << funds << "\n"; 


        money.saveMoney();
        // Switch statement to account for each choice given
        switch(choice) {
            case 1: {
                // This needs log and the money class to be made. If this is selected the 'money.txt' should be overwritten
                // to have the default amount of money $1500 dollars made.
                break;
            }

            case 2: {
                // This needs to have the money class done as well. This will read the current funds available to bet from the
                // money.txt file and start the game.
                break;
            }

            case 3: {
                // This option will simply write the current winnings to the 'money.txt' file and exit the game gracefully.
                break;
            }

            case 4: {
                // This will just exit the game without saving any information.
                break;
            }

            default: {
                cout << "Invalid option! Please make another choice.\n";
                break;
            }
        }
    }

    return 0;
}
