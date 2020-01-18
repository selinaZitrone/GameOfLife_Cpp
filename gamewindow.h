#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include "MyGraphicScene.h"

namespace Ui {
class GameWindow;
}

/*!
 * Created by the Qt Creator, it is responsible for the UI
 */
class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    // constructor and destructor
    explicit GameWindow(QWidget *parent = nullptr);
    ~GameWindow();

    // member functions
    void toggleCells(int x, int y, MyGraphicScene * theScene);
    void updateGUI();

    // variables
    MyGraphicScene * scenes[2]; //!< two graphic scenes instantiated from class derived from QGraphicsscene

private slots:
    void on_nextRound_Button_clicked();

private:
    Ui::GameWindow *ui;

};

#endif // GAMEWINDOW_H
