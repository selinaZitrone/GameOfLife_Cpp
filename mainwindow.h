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

    int get_CellsPerLine();
    int get_ViewResolution();
    void startLoop();
    void updateGUI();


private slots:
    void refreshLoop();

    void on_newButton_clicked();

    void on_saveButton_clicked();

    void on_loadButton_clicked();

    void on_playButton_clicked();

    void on_pauseButton_clicked();

    void on_resetButton_clicked();

    void on_backStepButton_clicked();

    void on_forwardStepButton_clicked();

    void on_loopMs_sliderMoved(int position);

private:
    Ui::MainWindow *ui;
    MyGraphicScene *scene;
    QPixmap image;
    int timer;
    int times;
    int vieWresolution;
    bool loopActive = false;
    bool loopPause = false;
};
#endif // MAINWINDOW_H
