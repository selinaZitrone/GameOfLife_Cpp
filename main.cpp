#include "mainwindow.h"
#include "Game.h"
#include <QtDebug>


#include <QApplication>

MainWindow * mainWin;
Game * game;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    game = new Game();

    mainWin = new MainWindow();
    mainWin->show();

    return a.exec();
}
