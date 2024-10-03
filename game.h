#ifndef GAME_H
#define GAME_H

#include <string>

using namespace std;

// Defines the GameData class and its protoypes. 
class Game {
private:
    string** playerHand;
    string** dealerHand;


public:
    Game(string filename, bool newGame);
    ~Game();

    //int getBet(int bet);
    void playHand(string filename, bool newGame);
    int cardValue(string* currentCards);
    int handValue ();

};

#endif