#ifndef TWOPLAYERS_H
#define TWOPLAYERS_H

using namespace std;
#include <vector>

/*!
 * Class with the logic for the two players game of life
 */
class TwoPlayers{

public:
    // member functions
    void initializeGame();
    void nextTurn();
    void letLifeGrow();
    bool makeAMove(int player);
    int checkWhoWon();

    // variables
    vector<bool> tables[2]; //!< vectors containing the actual state of the cells in the two fields
    int cellsPerSide; //!< number of cells per side, aka line, in each of the two tables
    int actualPlayer;
    int numberOfRounds; //!< number of rounds for a match
    int actualRound;
    int movesLeft[2]; //!< how many moves are left on each table (aka field)
    int scores[2]; //!< how many cells are alive on a field
    int ownFieldMoves; //!< how many cells the player can toggle on the own field
    int adversaryFieldMoves; //!< how many cells the player can toggle on the adversary field

};

#endif // TWOPLAYERS_H
