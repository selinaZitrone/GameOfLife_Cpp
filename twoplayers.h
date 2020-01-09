#ifndef TWOPLAYERS_H
#define TWOPLAYERS_H

using namespace std;
#include <vector>

class TwoPlayers{

public:
    vector<bool> tables[2];
    void initializeGame();
    void nextTurn();
    void letLifeGrow();
    int tableDim;
    int actualPlayer;
    int numberOfRounds;
    int actualRound;
    int movesLeft[2];
    int scores[2];
    bool makeAMove(int player);
    int checkWhoWon();
};

#endif // TWOPLAYERS_H
