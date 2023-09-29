#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include "MyGraphicScene.h"
#include "Game.h"
#include "gamewindow.h"
#include "twoplayers.h"
#include <QFile>
#include <QDataStream>
#include <QFileDialog>
#include <QMessageBox>
#include <QtMath>

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


// ---- START CONDITION ---

// clicked on the UI - New Button
void MainWindow::on_newButton_clicked()
{
    // reinitialize the game, passing how many cells per line has been chosen by the user
    game->initializeEmptyGame(get_CellsPerLine());

    // adapt view
    int res = viewResolution/get_CellsPerLine();
    set_ViewResolution(res*get_CellsPerLine());

    // if slider "cells alive" != 0% then make some cells alive
    if(ui->sliderCellsAlive->value() != 0){
        game->turnSomeRandomCellsAlive(ui->sliderCellsAlive->value());
    }

    // if not too small...
    if(game->actualCellsPerLine >= 2){
        // paint the scene
        scene->paintLife(game->gameSteps[game->bufferIndex], game->actualCellsPerLine);
    } else {
        qDebug() << "cells < 2";
    }

    updateUI();
}

void MainWindow::on_sliderCellsAlive_sliderMoved(int position)
{
    ui->labelCellsAlive->setText(QStringLiteral("alive: %1%").arg(position));
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



// ---- LOOP ----

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

/*!
 * It changes the color of the start button, based on loopPause and loopActive (grey / yellow / green)
 */
void MainWindow::setStartLoopButtonColor()
{
    QString qss;
    if(loopPause && loopActive){
        qss = QString("background-color: %1").arg("yellow");

    } else if(!loopPause && loopActive){
        qss = QString("background-color: %1").arg("lightgreen");
    } else {
        qss = QString("background-color: %1").arg("none");
    }
    ui->playButton->setStyleSheet(qss);
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

    setStartLoopButtonColor();
}

// clicked on the UI - Pause Button
void MainWindow::on_pauseButton_clicked()
{
    loopPause = !loopPause;
    setStartLoopButtonColor();

}



// reset the loop
void MainWindow::on_resetButton_clicked()
{
    loopActive = false;
    times = 0;
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
    setStartLoopButtonColor();
}


void MainWindow::updateUI()
{
    ui->actualStepLabel->setText(QStringLiteral("Actual step: %1").arg(game->actualStep));
}


// ----------------------


// when click on the save Button
void MainWindow::on_saveButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,
            tr("Save Cells Pattern"), "",
            tr("Pattern (*.gol);;All Files (*)"));
    if (fileName.isEmpty())
            return;
        else {
            QFile file(fileName);
            if (!file.open(QIODevice::WriteOnly)) {
                QMessageBox::information(this, tr("Unable to open file"),
                    file.errorString());
                return;
            }
            QDataStream out(&file);
               out.setVersion(QDataStream::Qt_4_5);
               // Date: 2023-09-29
               // Auther: Ar Gas
               // Change fromStdVector to the container method used since Qt6.3
               //QVector<bool> toSerialize = QVector<bool>::fromStdVector(game->gameSteps[game->bufferIndex]);
               QVector<bool> toSerialize = QVector<bool>(game->gameSteps[game->bufferIndex].begin(), game->gameSteps[game->bufferIndex].end());
               out << toSerialize;
         }
}

// when click on the Load button
void MainWindow::on_loadButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
           tr("Load Cells Pattern"), "",
           tr("Pattern (*.gol);;All Files (*)"));
    if (fileName.isEmpty())
            return;
        else {

            QFile file(fileName);

            if (!file.open(QIODevice::ReadOnly)) {
                QMessageBox::information(this, tr("Unable to open file"),
                    file.errorString());
                return;
            }

            QDataStream in(&file);
            in.setVersion(QDataStream::Qt_4_5);

            QVector<bool> toDeserialize;
            in >> toDeserialize;
            if (toDeserialize.isEmpty()) {
                        QMessageBox::information(this, tr("Empty pattern"),
                            tr("The file you are attempting to open is empty."));
                    } else {
                        // calculate the square size based on the size of the QVector
                        int sqSize = qSqrt( toDeserialize.size() );
                        // initialize the empty game of the correct dimension
                        game->initializeEmptyGame( sqSize );
                        // set the deserialized vector as first step
                        // Date: 2023-09-29
                        // Auther: Ar Gas
                        // Change toStdVector to the container method used after Qt6.3
                        // game->firstStep = toDeserialize.toStdVector();
                        std::vector <bool> stdvector(toDeserialize.begin(), toDeserialize.end());
                        game->firstStep = stdvector;
                        game->gameSteps[0] = game->firstStep;
                        // paint field
                        scene->paintLife(game->gameSteps[game->bufferIndex], game->actualCellsPerLine);
                        // adapt view
                        int res = viewResolution/sqSize;
                        set_ViewResolution(res*sqSize);
                    }
                }
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
    ui->loopMsLabel->setText(QStringLiteral("%1 ms").arg(position));
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
 * changes the dimesion of the view, to accomodate the scene (otherwise: black border)
 */
void MainWindow::set_ViewResolution(int res)
{
    ui->graphicsView->resize(res, res);
}

// goes back to the first step
void MainWindow::on_backToStartStep_clicked()
{
    game->backToStartStep();
    scene->paintLife(game->gameSteps[game->bufferIndex], game->actualCellsPerLine);
}
