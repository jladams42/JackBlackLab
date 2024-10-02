#ifndef DECK_H
#define DECK_H

#include "deck.h"
#include <vector>
#include <string>
using namespace std;

class Deck {
private:
    string** cards;
    int size;

public:
    Deck(string filename);
    ~Deck();
    void getDeck(string filename);
    void dealCard();
};

#endif