#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QtDebug>
#include <QGraphicsSceneMouseEvent>
#include "MyGraphicScene.h"
#include "Game.h"

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

    scene = new MyGraphicScene(this);
    ui->graphicsView->setScene(scene);

    // start a loop for n times (set timer to 0), refreshloop takes milliseconds for pace
    timer = 0;
    times = 0;
    refreshLoop(500);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// TO DO: this should came from "Game"
int heart[] = {
    0,0,1,0,0,0,0,1,0,0,
    0,1,1,1,0,0,1,1,1,0,
    1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,
    0,1,1,1,1,1,1,1,1,0,
    0,1,1,1,1,1,1,1,1,0,
    0,0,1,1,1,1,1,1,0,0,
    0,0,0,1,1,1,1,0,0,0,
    0,0,0,0,1,1,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0};

void MainWindow::toggleCells(int x, int y)
{
    qDebug() << "yeah";
    int index = (y/40) * 10 + (x/40);
    qDebug() << index;

    heart[index] == 0 ? heart[index] = 1 : heart[index] = 0;
    scene->paintLife(heart, 10);
}

void MainWindow::refreshLoop(int ms)
{
    // things to do
    scene->paintLife(heart, 10);

    //
    timer++;
    if(timer < times){
        update();
        timer++;
        QTimer::singleShot(ms,this,SLOT(refreshLoop(ms)));
    }
}



