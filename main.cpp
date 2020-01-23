#include "mainwindow.h"
#include "Game.h"
#include <QtDebug>
#include <QApplication>
#include "gamewindow.h"
#include "twoplayers.h"

// declare the pointers to the class instances which have to be accessible

MainWindow * mainWin; //!< instance of the Main Window

GameWindow * gameWin; //!< instance of the Two Players Game Window

Game * game; //!< instance of Logic of Game of Life class

TwoPlayers * twoPlay; //!< instance of the Logic of Two Players game class

int main(int argc, char *argv[])
{
    qputenv("QT_AUTO_SCREEN_SCALE_FACTOR", "1"); //with the autoscreen scaling factor it also works on high dpi displays
    QApplication a(argc, argv);

    // make instances of the classes whose pointer has been declared before
    game = new Game();
    mainWin = new MainWindow();
    twoPlay = new TwoPlayers();
    gameWin = new GameWindow();

    // show main window
    mainWin->show();

    return a.exec();
}
