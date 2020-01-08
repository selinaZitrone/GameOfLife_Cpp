#include "mainwindow.h"

#include <QApplication>

MainWindow * mainWin;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    mainWin = new MainWindow();
    mainWin->show();
    return a.exec();
}
