#ifndef GAME_H
#define GAME_H

using namespace std;
#include <vector>

/*!
 * Class containing the logic of Game of Life and necessary functions
 */
class Game{

public:
    // constructor
    Game();

    // member functions
    void initializeEmptyGame(int cellsPerSide);
    void oneStepFurther();
    void oneStepBack();
    vector<bool> calculateLogicOfLife(vector<bool>&, int cellsPerLine);

    // variables
    vector<vector<bool>> gameSteps; //!< contains all the saved steps in the development of life, it's length depends on int stepsBuffer
    int actualStep; //!< the step from game start (not the index in the gameSteps array!) for UI purposes only
    int actualCellsPerLine; //!< how many cells per line is the game field
    int stepsBuffer; //!< how many steps are saved (to allow the user to go "back in time")
    int bufferIndex; //!< index of the actual step in the vector of saved steps (gameSteps)
};

#endif // GAME_H
