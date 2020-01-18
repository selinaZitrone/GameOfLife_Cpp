#include "gamewindow.h"
#include "ui_gamewindow.h"
#include <QDebug>
#include "twoplayers.h"

extern TwoPlayers * twoPlay;

GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);

    // instantiate the scenes and add them to the views
    scenes[0] = new MyGraphicScene(this);
    ui->graphicsView_1->setScene(scenes[0]);

    scenes[1] = new MyGraphicScene(this);
    ui->graphicsView_2->setScene(scenes[1]);

    // set the pixel resolution to the scenes (it is used in the paint function)
    scenes[0]->myPixelResolution = 320;
    scenes[1]->myPixelResolution = 320;
}

GameWindow::~GameWindow()
{
    delete ui;
}

/*!
 * It gets x and y coordinates of the click on the referenced scene, changes the actual step and trigger GUI update
 */
void GameWindow::toggleCells(int x, int y, MyGraphicScene * theScene)
{
    // check which scene has been clicked
    int tableIndex = 3;
    if(theScene == scenes[0]){
        tableIndex = 0;
    } else if (theScene == scenes[1]){

        tableIndex = 1;
    }

    // check if the move is still available
    if(twoPlay->makeAMove(tableIndex)){
        // chec it is actually one of the two scenes
        if(theScene == scenes[0] || theScene == scenes[1]){
            int cellsPerLine = twoPlay->cellsPerSide;
            int viewDim = 320;
            // calculate the index of the clicked cell
            int index = (y/(viewDim/cellsPerLine)) * cellsPerLine + (x/(viewDim/cellsPerLine));
            // toggle it
            twoPlay->tables[tableIndex][index] ? twoPlay->tables[tableIndex][index] = false : twoPlay->tables[tableIndex][index] = true;
            // update scenes
            scenes[tableIndex]->paintLife(twoPlay->tables[tableIndex], cellsPerLine);
        }
    }
    // update the gui
    updateGUI();
}


// connected to the UI Button for Next Round
void GameWindow::on_nextRound_Button_clicked()
{
    // trigger the changes in game mechanic
    twoPlay->letLifeGrow();
    twoPlay->nextTurn();

    // update the scenes
    scenes[0]->paintLife(twoPlay->tables[0], twoPlay->cellsPerSide);
    scenes[1]->paintLife(twoPlay->tables[1], twoPlay->cellsPerSide);

    // update gui
    updateGUI();
}


/*!
 * Updates the Gui based on the variables of twoplayers class
 */
void GameWindow::updateGUI()
{
    // if it's the last round, check who won
    int playerWhoWon = 3;
    if(twoPlay->actualRound == twoPlay->numberOfRounds){
        playerWhoWon = twoPlay->checkWhoWon();
    } else {
        playerWhoWon = 3;
    }

    // change font dimension of the player names based on who is next
    QFont small(ui->playerOne_label->font().family(), 10);
    QFont big(small.family(), 26);
    if(twoPlay->actualPlayer == 0){
        ui->playerOne_label->setFont(small);
        ui->playerTwo_label->setFont(big);
    } else {
        ui->playerOne_label->setFont(big);
        ui->playerTwo_label->setFont(small);
    }

    // shows how many moves are available on each field
    string moves_1 = " ";
    string moves_2 = " ";
    for(int i = 0; i < twoPlay->movesLeft[0]; i++){
        moves_1 += "O ";
    }
    for(int i = 0; i < twoPlay->movesLeft[1]; i++){
        moves_2 += "O ";
    }
    ui->Moves_1->setText (QString::fromStdString(moves_1));
    ui->Moves_2->setText (QString::fromStdString(moves_2));

    // set the rounds label
    string rounds = "Rounds: ";
    rounds += to_string(twoPlay->actualRound);
    rounds += " / ";
    rounds += to_string(twoPlay->numberOfRounds);
    ui->roundsLabel->setText(QString::fromStdString(rounds));

    // if someone won, show the label with the result
    if(playerWhoWon < 2){
        string wonText = "Player ";
        wonText += to_string(playerWhoWon + 1);
        wonText += " won!!! ";
        wonText += to_string(twoPlay->scores[0]);
        wonText += " to ";
        wonText += to_string(twoPlay->scores[1]);
        ui->wonLabel->setText(QString::fromStdString(wonText));
        ui->wonLabel->setVisible(true);
    } else {
        ui->wonLabel->setVisible(false);
    }
}


