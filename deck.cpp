#include "deck.h"
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>


using namespace std;

// Initalize the deck base on the filename passed in 'deck.txt' while setting the cards to a nullptr and setting intial size to 0.
// This also seeds a random number for the shuffling of the deck later on. 
Deck::Deck (string filename) : cards(nullptr), size(0) {
    getDeck(filename);
    srand(time(NULL));
}

// Destructor of the deck object later by removing all the cards added to the cards array.
Deck::~Deck(){
    for (int i = 0; i < size; ++i){
        delete cards[i];
    }
    delete[] cards;
}

// This grabs the deck from a .txt file.
void Deck::getDeck(string filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Failed to open file.";
        return;
    }

    size = 53; // Sets the size of the array to 53 to accommadate the 52 card deck.
    cards = new string*[size]; // Dynamic allocation of string array to hold deck.

    for (int i = 0; i < size; ++i) {
        cards[i] = new string;
        file >> *cards[i]; // Reads from the file to grab the strings to assign to the array.
    }

    file.close(); // Closes the file.
}

// Function to grab a random number from 0 - 52 and grab the value from that index and
// assigning it to the newCard string. 
string Deck::dealCard() {
    string newCard;
    int randomNum = ( rand() % 52 );

    newCard = *cards[randomNum];

    return newCard;
}

// This determines the value of the cards by evaluating face cards to either 10 or 11 and also converts
// non-face cards to their respecive integer values and returns it to cardValue. 
int Deck::getValue(string newCard){
    int cardValue;
    if (newCard == "Q" || newCard == "K" || newCard == "J") {
        cardValue = 10;
    } else if (newCard == "A"){
        cardValue = 11;
    } else {
        cardValue = stoi(newCard);
    }

    return cardValue;
}