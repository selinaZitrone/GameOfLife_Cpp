#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include "MyGraphicScene.h"

namespace Ui {
class GameWindow;
}

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr);
    ~GameWindow();
    MyGraphicScene * scenes[2];
    void toggleCells(int x, int y, MyGraphicScene * theScene);
    void updateGUI();

private slots:
    void on_nextRound_Button_clicked();

private:
    Ui::GameWindow *ui;

};

#endif // GAMEWINDOW_H
