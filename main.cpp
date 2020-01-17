#include "mainwindow.h"
#include "Game.h"
#include <QtDebug>
#include <QApplication>

MainWindow * mainWin;

Game * game;

int main(int argc, char *argv[])
{
    qputenv("QT_AUTO_SCREEN_SCALE_FACTOR", "1"); //with the autoscreen scaling factor it also works on high dpi displays
    //qputenv("QT_SCALE_FACTOR", "1.5");
    QApplication a(argc, argv);

    game = new Game();
    mainWin = new MainWindow();
    mainWin->show();
    return a.exec();
}
