#ifndef GAME_H
#define GAME_H

using namespace std;
#include <vector>

class Game{

public:
    Game();
    vector<vector<bool>> gameSteps;
    void initializeEmptyGame(int cellsPerSide);
    void oneStepFurther();
    void oneStepBack();
    vector<bool> calculateLogicOfLife(vector<bool>&, int cellsPerLine);

    int actualStep;
    int actualCellsPerLine;
    int stepsBuffer;
    int bufferIndex;


};

#endif // GAME_H
