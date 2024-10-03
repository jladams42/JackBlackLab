#include "game.h"
#include "deck.h"
#include "player.h"
#include <string>
#include <iostream>
#include <ctime>


using namespace std;

Game::Game(string filename, bool newGame) : playerHand(nullptr), dealerHand(nullptr) {
    playHand(filename, newGame);
}

Game::~Game(){
}

void Game::playHand(string filename, bool newGame){
    Player player;
    int bet, newBal;
    if (newGame) {
        player.saveToFile();
        player.displayInfo();
    } else {
        player.loadFromFile();
        player.displayInfo();
    }

    int bal = player.getBalance();
    if (bal <= 0){
        cout << "You have no more money to bet! Please start a new game!\n";
        return;
    } else {
        cout << "Enter how much you would like to bet: ";
        cin >> bet;
        cin.ignore();

        while(bet > bal){
            cout << "You can't bet more than your available balance. Please choose another amount: ";
            cin >> bet;
            cin.ignore();
        }
    }

    Deck deck(filename);
    const int size = 10;
    int playerValue = 0;
    int dealerValue = 0;
    string response;
    bool cont = true;
    bool isBust = false;
    playerHand = new string*[size];
    dealerHand = new string*[size];
    
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
    
    while(cont && !isBust){
        if (playerValue > 21){
            cout << "You bust!\n";
            isBust = true;
            break;
        }
        cout << "You have a total of: " << playerValue << endl;
        cout << "The dealer is showing: " << *dealerHand[0] << endl;

        int i = 2;
        cout << "Do you want to hit or stay? (h/s)\n";
        cin >> response;
        cin.ignore();

        if(response == "h"){
            playerHand[i] = new string;
            *playerHand[i] = deck.dealCard();
            playerValue += cardValue(playerHand[i]);
        } else {
            cont = false;
        }
        ++i;
    }

    // Dealers turn
    while(dealerValue < 17){
        int i = 2;
        dealerHand[i] = new string;
        *dealerHand[i] = deck.dealCard();
        dealerValue += cardValue(dealerHand[i]);
    }

    cout << "The dealer filps their cards and shows: " << dealerValue << endl;

    if (playerValue > dealerValue && playerValue < 22){
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

    player.saveToFile();

}

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
