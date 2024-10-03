#include "player.h"
#include <iostream>
#include <fstream>


Player :: Player ()
{
    username = new string;
    balance = new double;
    currentBet = new double;
    *currentBet = 0;
    
    //ask for username
    cout << "\nEnter your username:\t";
    getline (cin, *username);

    *balance = 1500;

    playerData = new string*[2];
    playerData[0] = username;
    playerData[1] = new string (to_string(*balance)); // to_string used to convert balance into a string representation - referenced from GeeksforGeeks

}

void Player:: saveToFile()
{
    ofstream outFile(*username + "playerInfo.txt");//this adds the username to the title of the text file, so each player gets their own text file
    if (outFile.is_open())
    {
        outFile << "Username: " << *username << endl;
        outFile << "Balance: $" << *balance << endl;
        outFile.close();
        cout << "Player data saved to file." <<endl;
    }
    else 
    {
        cout << "\nUnable to open file for writing." << endl;
    }
}

void Player:: loadFromFile()
{
    string filename = *username + "playerInfo.txt";
    ifstream inFile(filename);
    if (inFile.is_open())
    {
        string line;
        //Skip "Username: " and read the actual username
        getline(inFile, line);
        *username = line.substr(10); //substr() used to extract part of the string which in this case is "Username: " - referenced from GeeksforGeeks
        //Skip  "Balance: $" and read the actual balance
        getline(inFile, line);
        *balance = stod(line.substr(10));// stod() used to convert string into double - - referenced from GeeksforGeeks
        inFile.close();
        cout << "Player information loaded from file." << endl;
    }
    else
    {
        cout << "Error! Could not open file. " << endl;
    }
}

void Player:: displayInfo()
{
    cout << "Player: " << *username << "\n";
    cout << "Balance: $" << *balance << "\n";
}

int Player::getBalance() {
    return *balance;
}

int Player::setBalance(int newBal) {
    *balance = newBal;
    return *balance;
}

