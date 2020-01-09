#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"
#include "MyGraphicScene.h"

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
    void refreshLoop(int);

//protected:
//    void mousePressEvent(QMouseEvent *event);

private:
    Ui::MainWindow *ui;
    MyGraphicScene *scene;
    QPixmap image;
    int timer;
    int times;
};
#endif // MAINWINDOW_H
