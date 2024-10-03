#include "game.h"
#include "deck.h"
#include "player.h"
#include <string>
#include <iostream>
#include <ctime>
#include <typeinfo>


using namespace std;

// Constructor for the game class. Takes in the filename used to call the `Deck` class from a text file.
// Also intializes both playerHand and dealerHand to null as they have no memory allocation at this point.
Game::Game(string filename, bool newGame) : playerHand(nullptr), dealerHand(nullptr) {
    playHand(filename, newGame);
}

Game::~Game(){
}

// This is where basically all the logic lives for the game. It reads in the playerData from the text file to grab
// the amount of money the user has to place bets. 
void Game::playHand(string filename, bool newGame){
    Player player; // Initialize the player object.

    // All the reusable variables for the function.
    int bet, newBal;
    const int size = 10;
    int playerValue = 0;
    int dealerValue = 0;
    string response;
    bool cont = true;
    bool stopRound = false;

    // Checks to see if the user had selected New Game or Load Game.
    if (newGame) {
        player.saveToFile();
        player.displayInfo();
    } else {
        player.loadFromFile();
        player.displayInfo();
    }

    // Uses the '.getBalance' function of the Player class to get the users available funds.
    // It then checks the balance to make sure the user has enough (> 0). 
    int bal = player.getBalance();
    if (bal <= 0){
        cout << "You have no more money to bet! Please start a new game!\n";
        return;
    } else {
        cout << "Enter how much you would like to bet: ";
        cin >> bet;
        // This is validation needed incase the user doesn't input the a proper integer -- Referenced from GeeksForGeeks.
        while(cin.fail()) { 
            cin.clear();
            cin.ignore();
            cout << "Not a valid integer!\n";
            cout << "Enter how much you would like to bet: ";
            cin >> bet;
        }
        cin.ignore();

        // This ensures that the user can't bet more than their available balance.
        while(bet > bal || bet < 1 ){
            cout << "You can't bet more than your available balance or $0! Please choose another amount: ";
            cin >> bet;
            cin.ignore();
        }
    }

    // Initialize the deck of cards to use for the game.
    Deck deck(filename);

    playerHand = new string*[size];  // Dynamic array for the players hand.
    dealerHand = new string*[size]; // Dynamic array for the dealers hand.
    
    // Intial card draw, set at 2 since only 2 cards are needed at first.
    for (int i = 0; i < 2; ++i) {
        playerHand[i] = new string;
        *playerHand[i] = deck.dealCard();
        dealerHand[i] = new string;
        *dealerHand[i] = deck.dealCard();
    }

    // Gets the value of the player and dealers cars as integers.
    for (int i = 0; i < 2; ++i) {
        playerValue += cardValue(playerHand[i]);
        dealerValue += cardValue(dealerHand[i]);
    }

    // Resets the int i value for use in the while loop.
    int i = 2;

    // While loop runs until the user either chooses to stop or loses. (Busts)
    while(cont && !stopRound){
        cout << "Your hand is: ";

        // Loops through the playerHand to show the cards they've drawn.
        for (int n = 0; n < i; ++n) {
            cout << *playerHand[n] << " ";
        }

        // Check if the player initial hand is Black Jack for an instant win!
        if (playerValue == 21 && dealerValue != 21){
            cout << "\nBLACK JACK!\n";
            cout << "You win! You've won $" << bet << "!\n";
            newBal = player.getBalance() + bet;
            player.setBalance(newBal); // Updates the player balance.
            stopRound = true;
            break;
        } else if (playerValue == 21 && dealerValue == 21) { // This checks the dealers initial hand to see if they have 21 - if so its a tie.
            cout << "\nThe dealer has " << *dealerHand[0] << " " << *dealerHand[1] << endl;
            cout << "\nYou both have 21! Thats a tie. You get your money back." << endl;
            newBal = player.getBalance();
            player.setBalance(newBal);
            stopRound = true;
            break;
        }

        //cout << "Your hand is showing: " << *playerHand[0] << " and " << *playerHand[1] << endl;
        cout << "\nThis gives you a total of: " << playerValue << endl;
        cout << "The dealer is showing: " << *dealerHand[0] << endl;

        cout << "Do you want to hit or stay? (h/s)\n";
        cin >> response;
        cin.ignore();

        // If the user chooses to hit, this does the dealCard() function again and adds it to the array of playerHand.
        // The else stamement handles any other choice other than H which defaults to 'stay' logic.
        if(response == "h"){
            playerHand[i] = new string;
            *playerHand[i] = deck.dealCard();
            playerValue += cardValue(playerHand[i]);
            cout << "------NEXT ROUND------\n";
            cout << "----------------------\n";
            cout << "You drew a " << *playerHand[i] << endl;
            cout << "This brings your total to: " << playerValue << endl;

        } else {
            cout << "------NEXT ROUND------\n";
            cout << "----------------------\n";
            cont = false;
        }

        // Calculates if the player got 21 or not. If so triggers a win response.
        if (playerValue == 21){
            cout << "BLACK JACK!\n";
            cout << "You win! You've won $" << bet << "!\n";
            newBal = player.getBalance() + bet;
            player.setBalance(newBal); // Updates the player balance.
            stopRound = true;
            break;
        } else if (playerValue > 21){ // Bust logic and player loses. 
            cout << "You bust!\n";
            cout << "The dealer wins! You've lost $" << bet << "!\n";
            newBal = player.getBalance() - bet;
            player.setBalance(newBal);
            stopRound = true;
            break;
        }

        ++i;
    }

    // Dealers turn and will draw cards until they reach 17 (Default dealer logic).
    if (!stopRound){
        while(dealerValue < 17){
            int i = 2;
            dealerHand[i] = new string;
            *dealerHand[i] = deck.dealCard();
            cout << "The dealer hits and drew a: " << *dealerHand[i] << endl;
            dealerValue += cardValue(dealerHand[i]);
        }

        cout << "The dealer filps their cards and shows: " << dealerValue << endl;

        // This handles all the logic for if you dealers busts, if the player has higher than the dealer
        // without busting or if the player loses to the dealer. 
        if (playerValue < 21 && dealerValue > 21){
            cout << "You win! The dealer busted! You've won $" << bet << "!\n";
            newBal = player.getBalance() + bet;
            player.setBalance(newBal);
        } else if (playerValue > dealerValue && playerValue < 22 ){
            cout << "You win! You've won $" << bet << "!\n";
            newBal = player.getBalance() + bet;
            player.setBalance(newBal);

        } else if (playerValue == dealerValue) {
            cout << "Its a tie! You get your money back!\n";
            newBal = player.getBalance();
            player.setBalance(newBal);
        } else {
            cout << "The dealer wins! You've lost $" << bet << "!\n";
            newBal = player.getBalance() - bet;
            player.setBalance(newBal);
        }
    }
    

    // This saves all the player data back to the save file.
    player.saveToFile();

}

// Calculates the card values by interperting the string values to integers. 
int Game::cardValue(string* currentCards){
    int cardValue;
     if (*currentCards == "Q" || *currentCards == "K" || *currentCards == "J") {
            cardValue = 10;
        } else if (*currentCards == "A"){
            cardValue = 11;
        } else {
            cardValue = stoi(*currentCards);
    }

    return cardValue;
}

