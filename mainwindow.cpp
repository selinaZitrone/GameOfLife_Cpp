#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QtDebug>
#include <QGraphicsSceneMouseEvent>
#include "MyGraphicScene.h"
#include "Game.h"
#include "gamewindow.h"
#include "twoplayers.h"

using namespace std;
#include <vector>

extern Game * game;

extern GameWindow * gameWin;

extern TwoPlayers * twoPlay;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    viewResolution = 500; // resolution of the view - depends on GraphicScene!

    scene = new MyGraphicScene(this);
    ui->graphicsView->setScene(scene);

    ui->loopMsLabel->setText(QStringLiteral("%1 ms").arg(ui->loopMs->value()));

    // it creates a basic empty "new"
    game->initializeEmptyGame(get_CellsPerLine());
    scene->paintLife(game->gameSteps[game->bufferIndex], game->actualCellsPerLine);
}

MainWindow::~MainWindow()
{
    delete ui;
}


/*!
 * gets the coordinates of a click on the referenced scene and changes the corresponding cells
 */
void MainWindow::toggleCells(int x, int y, MyGraphicScene * theScene)
{
    // stop here if it's not the right scene
    if(theScene != scene) return;

    // check if the click happened inside the part of the view populated by cells (it can be smaller than the whole scene)
    if(x > game->actualCellsPerLine * (viewResolution / game->actualCellsPerLine)
            || y > game->actualCellsPerLine * (viewResolution / game->actualCellsPerLine) ) return;

    int cellDimension = viewResolution / game->actualCellsPerLine;
    // calculate the index of the clicked cell
    int index = (y/cellDimension) * game->actualCellsPerLine + (x/cellDimension);
    // change the actual step and update the scene
    if(index < game->gameSteps[game->bufferIndex].size()){
        game->gameSteps[game->bufferIndex][index] == 0 ? game->gameSteps[game->bufferIndex][index] = true : game->gameSteps[game->bufferIndex][index] = false;
        scene->paintLife(game->gameSteps[game->bufferIndex], game->actualCellsPerLine);
    }
}


/*!
 * Returns the cells per line defined in the GUI by the user
 */
int MainWindow::get_CellsPerLine()
{
    return ui->cellsPerLine->value();
}


/*!
 * returns number of pixel of one side of the view (view is square)
 */
int MainWindow::get_ViewResolution()
{
    return viewResolution;
}


/*!
 * Starts a loop of Game of Life - setting times to the value choosen in the UI
 */
void MainWindow::startLoop()
{
        // start a loop for n times (set timer to 0), refreshloop takes milliseconds for pace
        loopActive = true;
        timer = 0;
        times = ui->loopTimes->value();
        refreshLoop();
}

void MainWindow::updateUI()
{
    ui->actualStepLabel->setText(QStringLiteral("Actual step: %1").arg(game->actualStep));
}


/*!
 * It's a looping function, calling itself with a pace defined in milliseconds
 */
void MainWindow::refreshLoop()
{
    // if it's not over and it is not in pause
    if(timer < times && !loopPause){

        // *** beginning of the things to do in the loop ***
        //**************************************************
        game->oneStepFurther();
        scene->paintLife(game->gameSteps[game->bufferIndex], game->actualCellsPerLine);
        qDebug() << "step: " << game->actualStep << " - buffer: " << game->bufferIndex;
        //**************************************************
        // *** end of the things to do in the loop *********

        update(); // calls the update function from QT - in a member function of QWidget

        // we did one more run
        timer++;

        // set the loop for another shot, args: (in x milliseconds, this class is the receiver, the slot to trigger is this same function)
        QTimer::singleShot(ui->loopMs->value(),this,SLOT(refreshLoop()));

    } else if(timer < times && loopPause){

        update(); // calls the update function from QT - in a member function of QWidget

        // set the loop for another shot, args: (in x milliseconds, this class is the receiver, the slot to trigger is this same function)
        QTimer::singleShot(ui->loopMs->value(),this,SLOT(refreshLoop()));

    } else {
        // if timer is not smaller then times, then stop and set loop to !active
        loopActive = false;
    }
}



// clicked on the UI - New Button
void MainWindow::on_newButton_clicked()
{
    // reinitialize the game, passing how many cells per line has been chosen by the user
    game->initializeEmptyGame(get_CellsPerLine());
    // if not too small...
    if(game->actualCellsPerLine >= 2){
        // paint the scene
        scene->paintLife(game->gameSteps[game->bufferIndex], game->actualCellsPerLine);
    } else {
        qDebug() << "cells < 2";
    }

}

// TO IMPLEMENT
void MainWindow::on_saveButton_clicked()
{

}

// TO IMPLEMENT
void MainWindow::on_loadButton_clicked()
{

}

// clicked on the UI - Play Button
void MainWindow::on_playButton_clicked()
{
    if(loopPause){
        // if it was just in pause... continue it
        loopPause = false;
    } else {
        if(!loopActive){
        // if it was off.. stat it
            startLoop();
        }
    }
}

// clicked on the UI - Pause Button
void MainWindow::on_pauseButton_clicked()
{
    loopPause = !loopPause;
}

// CHANGE IT TO "RANDOM"???
void MainWindow::on_resetButton_clicked()
{

}

// clicked on the UI - Forward Button
void MainWindow::on_forwardStepButton_clicked()
{
    game->oneStepFurther();
    scene->paintLife(game->gameSteps[game->bufferIndex], game->actualCellsPerLine);
}

// clicked on the UI - Back Button
void MainWindow::on_backStepButton_clicked()
{
    game->oneStepBack();
    scene->paintLife(game->gameSteps[game->bufferIndex], game->actualCellsPerLine);
}

// on UI: slider that defines how often the loop should tick (in ms)
void MainWindow::on_loopMs_sliderMoved(int position)
{
    // just update the UI (the value is read automatically by the looping function)
    ui->loopMsLabel->setText(QStringLiteral("%1 ms").arg(ui->loopMs->value()));
}

// on UI: starts the two players game
void MainWindow::on_twoPlayersOpenButton_clicked()
{
    // show the gamewindow (it is initialized in main)
    gameWin->show();
    // initialize the game (the class has been initialized in main)
    twoPlay->initializeGame();

    // paint the two scenes
    gameWin->scenes[0]->paintLife(twoPlay->tables[0],twoPlay->cellsPerSide);
    gameWin->scenes[1]->paintLife(twoPlay->tables[1],twoPlay->cellsPerSide);

    // update the GUI
    gameWin->updateGUI();
}
