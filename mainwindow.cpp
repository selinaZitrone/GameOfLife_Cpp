#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QtDebug>
#include <QGraphicsSceneMouseEvent>
#include "MyGraphicScene.h"
#include "Game.h"

using namespace std;
#include <vector>

/*
Main Window takes care of GUI and connecting Game with Graphics
it also manages the loop logic necessary for the Game to be played

MyGraphicScene is derived from QGraphicsScene
    painLife gets the array to be painted on the scene
    mousePressEvent triggers toggleCells, which changes the array on the scene
*/

extern Game * game;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    vieWresolution = 500; // resolution of the view - depends on GraphicScene!

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

void MainWindow::toggleCells(int x, int y)
{
    if(x > game->actualCellsPerLine * (vieWresolution / game->actualCellsPerLine)
            || y > game->actualCellsPerLine * (vieWresolution / game->actualCellsPerLine) ) return;

    int cellDimension = vieWresolution / game->actualCellsPerLine;
    int index = (y/cellDimension) * game->actualCellsPerLine + (x/cellDimension);
    if(index < game->gameSteps[game->bufferIndex].size()){
        game->gameSteps[game->bufferIndex][index] == 0 ? game->gameSteps[game->bufferIndex][index] = true : game->gameSteps[game->bufferIndex][index] = false;
        scene->paintLife(game->gameSteps[game->bufferIndex], game->actualCellsPerLine);
    }
}

int MainWindow::get_CellsPerLine()
{
    return ui->cellsPerLine->value();
}

int MainWindow::get_ViewResolution()
{
    return vieWresolution;
}

void MainWindow::startLoop()
{

        // start a loop for n times (set timer to 0), refreshloop takes milliseconds for pace
        loopActive = true;
        timer = 0;
        times = ui->loopTimes->value();
        qDebug() << "tryin to start the first refresh";
        refreshLoop();

}

void MainWindow::updateGUI()
{
    ui->actualStepLabel->setText(QStringLiteral("Actual step: %1").arg(game->actualStep));
}

void MainWindow::refreshLoop()
{
    qDebug() << "refresh, time n. = " << timer << " of " << times;
    if(timer < times && !loopPause){

        // things to do
        game->oneStepFurther();
        scene->paintLife(game->gameSteps[game->bufferIndex], game->actualCellsPerLine);
        qDebug() << "step: " << game->actualStep << " - buffer: " << game->bufferIndex;

        // end thigs to do
        update();
        timer++;
        QTimer::singleShot(ui->loopMs->value(),this,SLOT(refreshLoop()));
    } else if(timer < times && loopPause){
        update();
        QTimer::singleShot(ui->loopMs->value(),this,SLOT(refreshLoop()));
    } else {
        loopActive = false;
    }
}




void MainWindow::on_newButton_clicked()
{
    qDebug() << "newButton clicked";
    game->initializeEmptyGame(get_CellsPerLine());
    if(game->actualCellsPerLine >= 2){
        scene->paintLife(game->gameSteps[game->bufferIndex], game->actualCellsPerLine);
    } else {
        qDebug() << "cells < 2";
    }

}

void MainWindow::on_saveButton_clicked()
{

}

void MainWindow::on_loadButton_clicked()
{

}

void MainWindow::on_playButton_clicked()
{
    qDebug() << "playLoop clicked";
    if(loopPause){
        loopPause = false;
    } else {
        if(!loopActive){
            qDebug() << "checked: loop not active";
            startLoop();
        }
    }
}

void MainWindow::on_pauseButton_clicked()
{
    loopPause = !loopPause;
}

void MainWindow::on_resetButton_clicked()
{

}

void MainWindow::on_backStepButton_clicked()
{
    game->oneStepBack();
    scene->paintLife(game->gameSteps[game->bufferIndex], game->actualCellsPerLine);
    qDebug() << "step: " << game->actualStep << " - buffer: " << game->bufferIndex;
}

void MainWindow::on_forwardStepButton_clicked()
{
    game->oneStepFurther();
    scene->paintLife(game->gameSteps[game->bufferIndex], game->actualCellsPerLine);
    qDebug() << "step: " << game->actualStep << " - buffer: " << game->bufferIndex;
}

void MainWindow::on_loopMs_sliderMoved(int position)
{
    ui->loopMsLabel->setText(QStringLiteral("%1 ms").arg(ui->loopMs->value()));
}
