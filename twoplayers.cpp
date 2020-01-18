#include "twoplayers.h"
#include "Game.h"
#include <QDebug>

extern Game * game;

/*!
 * Set all the necessary variables for the game to be played
 */
void TwoPlayers::initializeGame()
{
    cellsPerSide = 32;
    vector<bool> empty (cellsPerSide*cellsPerSide, false);
    tables[0] = empty;
    tables[1] = empty;
    actualPlayer = 0;
    ownFieldMoves = 6;
    adversaryFieldMoves = 2;
    movesLeft[0] = ownFieldMoves;
    movesLeft[1] = adversaryFieldMoves;
    numberOfRounds = 20;
    actualRound = 1;
}

/*!
 * Moves the game to the next turn
 */
void TwoPlayers::nextTurn()
{
    // only if it is not the actual round
    if(actualRound == numberOfRounds) return;

    // set the moves for the other field
    movesLeft[actualPlayer] = adversaryFieldMoves;
    // switch player
    actualPlayer = actualPlayer == 0 ? 1 : 0;
    // set the moves for the own field
    movesLeft[actualPlayer] = ownFieldMoves;
    // increase round count
    actualRound++;
}

/*!
 * Let bot fields changed based on the GoL algorithm
 */
void TwoPlayers::letLifeGrow()
{
    vector<bool> newTable = game->calculateLogicOfLife(tables[0], cellsPerSide);
    tables[0] = newTable;
    newTable = game->calculateLogicOfLife(tables[1], cellsPerSide);
    tables[1] = newTable;
}

/*!
 * Tries to make a move, returns true if the move is available and updates the moves count
 */
bool TwoPlayers::makeAMove(int player)
{
    if(movesLeft[player] > 0){
        movesLeft[player]--;
        return true;
    } else {
        return false;
    }
    return false;
}

/*!
 * Counts the cells in each field and returns the index of the player who won (0 for 1, 1 for 2). In case of a tie, player 2 wins.
 */
int TwoPlayers::checkWhoWon()
{
    scores[0] = 0;
    scores[1] = 0;
    for(int a: tables[0]){
        scores[0] += a;
    }
    for(int a: tables[1]){
        scores[1] += a;
    }

    return scores[0] > scores[1];
}
