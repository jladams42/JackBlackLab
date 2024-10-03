#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
#include <fstream>
using namespace std; 

class Player
{
    private:
        string* username;
        double* balance;
        double* currentBet;

        string** playerData;
    public:
        //constructor
        Player ();
        //function to save info to file
        void saveToFile();
        //load player info from a file
        void loadFromFile();
        //display player's info
        void displayInfo();
        int getBalance();
        int setBalance(int newBal);

};


#endif
