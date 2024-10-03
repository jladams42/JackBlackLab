#include <iostream>
#include <string>
#include "deck.h"
#include "game.h"
#include "player.h"

using namespace std;

void displayMenu() {
    cout << "\n======= Jack Black Black Jack Game Menu =====\n";
    cout << "1. New Game\n";
    cout << "2. Load Game\n";
    cout << "3. Exit\n";
    cout << "================================================\n";
    cout << "Choose an option: ";
}

int main() {
    bool isPlaying = true; // Boolean value to determine if the user wants to keep playing

    // Displays the menu and allows the user to interact with the menu until they say they don't want to anymore.
    while (isPlaying) {
        displayMenu();

        int choice;
        cin >> choice;
        cin.ignore();

        // Switch statement to account for each choice given
        switch(choice) {
            case 1: {
                Game game("deck.txt", true); // Plays a hand using the "deck.txt" file and sets newGame to true.
                break;
            }

            case 2: {
                Game game("deck.txt", false); // Plays a hand using the "deck.txt" file and sets newGame to false.
                break;
            }

            case 3: {
                // This will just exit the game without saving any information.
                isPlaying = false;
                break;
            }

            default: {
                // Resets user input after an invalid character or selection (not 1-4) is used.
                cout << "Invalid option! Please make another choice.\n";
                cin.clear();
                cin.ignore();
                break;
            }
        }
    }

    return 0;
}
