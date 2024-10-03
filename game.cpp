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
    const int size = 2;
    int playerValue = 0;
    int dealerValue = 0;
    playerHand = new string*[size];
    dealerHand = new string*[size];
    
    for (int i = 0; i < size; ++i) {
        playerHand[i] = new string;
        *playerHand[i] = deck.dealCard();
        dealerHand[i] = new string;
        *dealerHand[i] = deck.dealCard();
    }

    // Gets the value of the player and dealers cars as integers.
    for (int i = 0; i < size; ++i) {
        playerValue += cardValue(playerHand[i]);
        dealerValue += cardValue(dealerHand[i]);
    }
    

    cout << "You have a total of: " << playerValue << endl;
    cout << "The dealer has a total of: " << dealerValue << endl;

    if (playerValue > dealerValue && playerValue < 22){
        cout << "You win! You've won $" << bet << "!\n";
        newBal = player.getBalance() + bet;
        player.setBalance(newBal);

    } else {
        cout << "The dealer wins! You've lost $" << bet << "!\n";
        newBal = player.getBalance() - bet;
        player.setBalance(newBal);
    }

    player.saveToFile();

}

int Game::cardValue(string* currentCards){
    int cardValue, totalValue;
    const int size = 2;
     if (*currentCards == "Q" || *currentCards == "K" || *currentCards == "J") {
            cardValue = 10;
        } else if (*currentCards == "A"){
            cardValue = 11;
        } else {
            cardValue = stoi(*currentCards);
    }

    return cardValue;
}
