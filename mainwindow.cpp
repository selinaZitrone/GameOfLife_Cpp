#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QtDebug>
#include <QGraphicsSceneMouseEvent>
#include "MyGraphicScene.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new MyGraphicScene(this);

    qDebug() << "s";
    timer = 0;
    times = 1;
    refreshLoop(500);


}

MainWindow::~MainWindow()
{
    delete ui;
}

// TO DO
int heart[] = {
    0,0,1,0,0,0,0,1,0,0,
    0,1,1,1,0,0,1,1,1,0,
    1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,
    0,1,1,1,1,1,1,1,1,0,
    0,1,1,1,1,1,1,1,1,0,
    0,0,1,1,1,1,1,1,0,0,
    0,0,0,1,1,1,1,0,0,0,
    0,0,0,0,1,1,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0};

void MainWindow::toggleCells(int x, int y)
{
    qDebug() << "yeah";
    int index = (y/40) * 10 + (x/40);
    qDebug() << index;

    heart[index] == 0 ? heart[index] = 1 : heart[index] = 0;
    paintLife(heart, 10);
}

void MainWindow::paintLife(int array[], int len)
{
    // dimension in pixel of the View
    int viewDim = 400;
    //calculate the biggest area

    int cellDim = viewDim/len;
    // int bigDim = len * cellDim;
    //scene->setSceneRect(scene.)

    QImage image(viewDim, viewDim, QImage::Format_RGB32);
    QRgb value;

    value = qRgb(240, 100, 2); // 0xffbd9527

    for(int i = 0; i < len; i++){
        for(int e = 0; e < len; e++){
             if(array[(i*len) + e]){
                for(int x = 0; x < cellDim; x++){
                    for(int y = 0; y < cellDim; y++){
                        image.setPixel(e*cellDim + x, i*cellDim + y, value);
                    }
                }
             }
        }
    }

    // Print it
    scene->setSceneRect(0,0,viewDim,viewDim);
    scene->addPixmap(QPixmap::fromImage(image));
    ui->graphicsView->setScene(scene);

}


void MainWindow::refreshLoop(int ms)
{
    // things to do
    paintLife(heart, 10);

    //
    timer++;
    if(timer < times){
        update();
        timer++;
        QTimer::singleShot(ms,this,SLOT(refreshLoop(ms)));
    }
}

