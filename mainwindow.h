#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void toggleCells(int x, int y);


private slots:
    void paintLife(int[], int);
    void refreshLoop(int);

//protected:
//    void mousePressEvent(QMouseEvent *event);

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QPixmap image;
    int timer;
    int times;
};
#endif // MAINWINDOW_H
