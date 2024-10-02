#ifndef MONEY_H
#define MONEY_H

#include <string>
using namespace std;

class Money {
private:
    int** funds;
    int size;
    int amount;

public:
    Money(string filename);
    ~Money();

    int getMoney(string filename);
    int getFunds();
    void saveMoney();
};

#endif