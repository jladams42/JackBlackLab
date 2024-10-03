#include "deck.h"
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>


using namespace std;

Deck::Deck (string filename) : cards(nullptr), size(0) {
    getDeck(filename);
    srand(time(NULL));
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

    file.close();
}

string Deck::dealCard() {
    string newCard;
    int randomNum = ( rand() % 52 + 1 );
    newCard = *cards[randomNum];

    return newCard;
}

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