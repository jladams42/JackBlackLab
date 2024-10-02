#include "money.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

Money::Money(string filename) : funds(nullptr), size(0), amount(0){
    getMoney(filename);
}

// Destructor for the HighScores to clean up the object.
Money::~Money() {
    saveMoney();
    for (int i = 0; i < size; ++i){
        delete funds[i];
    }
    delete[] funds;
    
}

int Money::getMoney(string filename) {
    ifstream file(filename);
    if (file.is_open()) {
        file >> amount;
        funds = new int*[1];
        funds[0] = new int;
        file >> *funds[0];
        file.close();
    } else{
        cout << "You have no money left!\n";
    }

    return amount;
}

int Money::getFunds(){
    int value = *funds[0];
    return value;
}

void Money::saveMoney() {
    ofstream file("money.txt");
    if (file.is_open()) {
        file << *funds[0];
        file.close();
        cout << "Money has been updated.\n";
    } else {
        cout << "Error! Could not load the file!\n";
    }
}
