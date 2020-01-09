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

    scenes[0] = new MyGraphicScene(this);
    ui->graphicsView_1->setScene(scenes[0]);
    scenes[1] = new MyGraphicScene(this);
    ui->graphicsView_2->setScene(scenes[1]);
    scenes[0]->myDimension = 320;
    scenes[1]->myDimension = 320;
}

GameWindow::~GameWindow()
{
    delete ui;
}

void GameWindow::toggleCells(int x, int y, MyGraphicScene * theScene)
{

    int tableIndex = 3;
    if(theScene == scenes[0]){
        tableIndex = 0;
    } else if (theScene == scenes[1]){

        tableIndex = 1;
    }

    if(twoPlay->makeAMove(tableIndex)){
        if(theScene == scenes[0] || theScene == scenes[1]){
            int cellsPerLine = twoPlay->tableDim;

            int viewDim = 320;
            int index = (y/(viewDim/cellsPerLine)) * cellsPerLine + (x/(viewDim/cellsPerLine));

            twoPlay->tables[tableIndex][index] ? twoPlay->tables[tableIndex][index] = false : twoPlay->tables[tableIndex][index] = true;
            qDebug() << "got here, index: " << index << " size: " << cellsPerLine;
            scenes[tableIndex]->paintLife(twoPlay->tables[tableIndex], cellsPerLine);
        }
    }
    updateGUI();
}

int playerWhoWon = 3;

void GameWindow::on_nextRound_Button_clicked()
{
    twoPlay->letLifeGrow();
    twoPlay->nextTurn();
    scenes[0]->paintLife(twoPlay->tables[0], twoPlay->tableDim);
    scenes[1]->paintLife(twoPlay->tables[1], twoPlay->tableDim);

    if(twoPlay->actualRound == twoPlay->numberOfRounds){
        playerWhoWon = twoPlay->checkWhoWon();
    } else {
        playerWhoWon = 3;
    }
    updateGUI();
}

void GameWindow::updateGUI()
{
    QFont small(ui->playerOne_label->font().family(), 10);
    QFont big(small.family(), 26);
    if(twoPlay->actualPlayer == 0){
        ui->playerOne_label->setFont(small);
        ui->playerTwo_label->setFont(big);
    } else {
        ui->playerOne_label->setFont(big);
        ui->playerTwo_label->setFont(small);
    }

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

    string rounds = "Rounds: ";
    rounds += to_string(twoPlay->actualRound);
    rounds += " / ";
    rounds += to_string(twoPlay->numberOfRounds);

    ui->roundsLabel->setText(QString::fromStdString(rounds));

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


