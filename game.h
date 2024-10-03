#ifndef GAME_H
#define GAME_H

#include <string>

using namespace std;

// Defines the Game class and its protoypes. 
class Game {
private:
    string** playerHand;
    string** dealerHand;


public:
    Game(string filename, bool newGame);
    ~Game();

    void playHand(string filename, bool newGame);
    int cardValue(string* currentCards);
    int handValue ();

};

#endif