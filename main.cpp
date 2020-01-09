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
    mainWin = new MainWindow();
    game = new Game();
    mainWin->show();

    vector<int> arrayOne = {0, 1, 2, 3};
    vector<int>&secondArrayOne = arrayOne;
    vector<int> &ThirdArrayTwo = arrayOne;
    qDebug() << &arrayOne << " " << &secondArrayOne << " " << &ThirdArrayTwo;


    return a.exec();
}
