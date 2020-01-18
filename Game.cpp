#include "Game.h"
using namespace std;
#include <vector>
#include "mainwindow.h"
#include <QDebug>

extern MainWindow * mainWin;

Game::Game()
{
    //! it sets how many steps are saved (how many steps back you can go)
    stepsBuffer = 100;
}

/*!
 * Initialize an empty field with a certain amount of cells per line
 */
void Game::initializeEmptyGame(int cellsPerLine)
{
    gameSteps = {vector<bool>(cellsPerLine*cellsPerLine, false)};
    actualStep = 0;
    bufferIndex = 0;
    actualCellsPerLine = cellsPerLine;
}

/*!
 * Moves the logic of the game one step further and then triggers the UI to update
 */
void Game::oneStepFurther()
{
    //first calculates the new steps and adds it to the vector
    gameSteps.push_back(calculateLogicOfLife(gameSteps[bufferIndex], actualCellsPerLine));

    if(bufferIndex < stepsBuffer){
        // if there is space in the buffer, then it just increases the index
        bufferIndex++;
    } else {
        // otherwise it erases the oldest entry
        gameSteps.erase(gameSteps.begin());
    }
    // it is nevertheless a further step in the development
    actualStep++;
    // update the UI
    mainWin->updateUI();
}

/*!
 * Moves the logic of the game one step back in time and then triggers the UI to update
 */
void Game::oneStepBack()
{
    if(bufferIndex < 1) return;
    bufferIndex--;
    actualStep--;
    gameSteps.pop_back();
    mainWin->updateUI();
}

/*!
 * Applies the algorithm of Game of Life and returns a vector with the next configuration
 */
vector<bool> Game::calculateLogicOfLife(vector<bool> & status, int cellsPerLine)
{
    vector<bool> toReturn(cellsPerLine*cellsPerLine, false);
    int len = cellsPerLine;

    for(int i = 0; i < status.size() ; i++){
            int sumOfNeigbors = 0;

            // calculate number of alive neighbors
            // check in which position in the array they are and calculate all neighbors
            // corner cells have 3, other border cells 5 and centre cells 8 neighbors
            if(i==0){
                // topleft corner
                sumOfNeigbors += status[1] + status[len] + status[len+1];
            }else if (i == len -1){
                // topright corner
                sumOfNeigbors += status[i-1] +  status[i+len-1] +status[i+len];
            }else if(i == status.size() - len){
                // bottomleft corner
                sumOfNeigbors += status[i+1] + status[i-len] + status[i-len+1];
            }else if(i == status.size() - 1){
                //bottomright corner
                sumOfNeigbors += status[i-1] + status[i-len] + status[i-len-1];
            }else if(i < len){
                // top row
                sumOfNeigbors += status[i-1] + status[i+1] + status[i+len-1] + status[i+len] + status[i+len+1];
            }else if(i>(status.size()-len)){
                // bottom row
                sumOfNeigbors += status[i-1] + status[i+1] + status[i-len-1] + status[i-len] + status[i-len+1];
            }else if(i % len == 0){
                // left column
                sumOfNeigbors += status[i+1] + status[i+len] + status[i+len+1] + status[i-len] + status[i-len+1];
            }else if ((i + 1) % len == 0){
                // right column
                sumOfNeigbors += status[i-1] + status[i+len] + status[i+len-1] + status[i-len] + status[i-len-1];
            }else{
                // in the middle
                sumOfNeigbors += status[i-1] + status[i+len] + status[i+len-1] + status[i-len] + status[i-len-1] +
                 status[i+1] + status[i-len+1] + status[i+len+1];
            }

            // update the toRender vector depending on the number of neighbors of the cell
            int currentState = status[i];
            switch (currentState){
                        case 1:
                            switch (sumOfNeigbors)
                            {
                                case 2:
                                    toReturn[i] = true;
                                    break;
                                case 3:
                                    toReturn[i] = true;
                                    break;
                                default:
                                    toReturn[i] = false;
                                    break;
                            }
                            break;
                        case 0:
                            switch (sumOfNeigbors)
                            {
                                case 3:
                                    toReturn[i] = true;
                                    break;
                                default:
                                    toReturn[i] = false;
                                    break;
                            }
                            break;
                        default:
                            break;
            }
        }

    return toReturn;
}
