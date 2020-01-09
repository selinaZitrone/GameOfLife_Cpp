#include "Game.h"
using namespace std;
#include <vector>
#include "mainwindow.h"

extern MainWindow * mainWin;

Game::Game()
{
    // it sets how many steps are saved (how many steps back you can go)
    stepsBuffer = 10; // change it eventually
}

void Game::initializeEmptyGame(int cellsPerLine)
{
    gameSteps = {vector<bool>(cellsPerLine*cellsPerLine, false)};
    actualStep = 0;
    bufferIndex = 0;
    actualCellsPerLine = cellsPerLine;
}

void Game::oneStepFurther()
{
    gameSteps.push_back(calculateLogicOfLife(gameSteps[bufferIndex]));
    if(bufferIndex < stepsBuffer){
        bufferIndex++;
    } else {
        gameSteps.erase(gameSteps.begin());
    }
    actualStep++;
    mainWin->updateGUI();
}

void Game::oneStepBack()
{
    if(bufferIndex < 1) return;
    bufferIndex--;
    actualStep--;
    gameSteps.pop_back();
    mainWin->updateGUI();
}

vector<bool> Game::calculateLogicOfLife(vector<bool> & oldOne)
{
    vector<bool> toReturn;

    for(bool a : oldOne){
        toReturn.push_back(!a);
    }
    return toReturn;
}
