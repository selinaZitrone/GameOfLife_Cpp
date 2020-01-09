#include "mainwindow.h"
#include "Game.h"
#include <QtDebug>
#include <QApplication>
#include "gamewindow.h"
#include "twoplayers.h"

MainWindow * mainWin;

GameWindow * gameWin;

Game * game;

TwoPlayers * twoPlay;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    game = new Game();
    mainWin = new MainWindow();
    twoPlay = new TwoPlayers();

    mainWin->show();

    gameWin = new GameWindow();

    return a.exec();
}
