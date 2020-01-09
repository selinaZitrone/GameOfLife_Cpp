#include "MyGraphicScene.h"
#include <QGraphicsSceneMouseEvent>
#include <QtDebug>
#include "mainwindow.h"

extern MainWindow * mainWin;

MyGraphicScene::MyGraphicScene(QMainWindow *parent)
{

}

MyGraphicScene::MyGraphicScene(QGraphicsItem *parent)
{

}



void MyGraphicScene::mousePressEvent(QGraphicsSceneMouseEvent *event){
    qDebug() << event->scenePos().x() << " " << event->scenePos().y();
    mainWin->toggleCells(event->scenePos().x(), event->scenePos().y());

}

void MyGraphicScene::paintLife(int array[], int len)
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
    setSceneRect(0,0,viewDim,viewDim);
    addPixmap(QPixmap::fromImage(image));
}
