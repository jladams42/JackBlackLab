#include "deck.h"
#include <iostream>
#include <fstream>
#include <ctime>


using namespace std;

Deck::Deck (string filename) : cards(nullptr), size(0) {
    getDeck(filename);
    dealCard();
}

Deck::~Deck(){
    for (int i = 0; i < size; ++i){
        delete cards[i];
    }
    delete[] cards;
}

void Deck::getDeck(string filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Failed to open file.";
        return;
    }

    file >> size;
    cards = new string*[size];

    for (int i = 0; i < size; ++i) {
        cards[i] = new string;
        file >> *cards[i];
    }

    // for (int i = 0; i < size-1; ++i) {
    //     cout << "This is the " << i-1 << " card: " << *cards[i] << "\n";
    // }

    file.close();
}

void Deck::dealCard() {
    srand(std::time(0));
    int randomNum = ( rand() % 52 + 1 );
    cout << *cards[randomNum];
}