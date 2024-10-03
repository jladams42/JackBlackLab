#ifndef DECK_H
#define DECK_H

#include "deck.h"
#include <string>

using namespace std;

class Deck {
private:
    string** cards; //A pointer to a dynamically allocated array of strings.
    int size; // Size of the deck.

public:
    Deck(string filename); // Contructor to intialize the deck based on a text file.
    ~Deck(); // Destructor to the clean up the deck.
    void getDeck(string filename);
    string dealCard();
    int getValue(string newCard);
};

#endif