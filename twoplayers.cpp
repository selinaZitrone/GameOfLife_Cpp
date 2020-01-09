#include "twoplayers.h"
#include "Game.h"
#include <QDebug>

extern Game * game;

void TwoPlayers::initializeGame()
{
    tableDim = 32;
    vector<bool> empty (tableDim*tableDim, false);
    tables[0] = empty;
    tables[1] = empty;
    actualPlayer = 0;
    movesLeft[0] = 5;
    movesLeft[1] = 1;
    numberOfRounds = 20;
    actualRound = 1;

    qDebug() << "twoplayers initializeGame";
}

void TwoPlayers::nextTurn()
{
    if(actualRound == numberOfRounds) return;

    movesLeft[actualPlayer] = 1;
    // switch player
    actualPlayer = actualPlayer == 0 ? 1 : 0;
    movesLeft[actualPlayer] = 5;
    actualRound++;
}

void TwoPlayers::letLifeGrow()
{
    vector<bool> newTable = game->calculateLogicOfLife(tables[0], tableDim);
    tables[0] = newTable;
    newTable = game->calculateLogicOfLife(tables[1], tableDim);
    tables[1] = newTable;
}

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
