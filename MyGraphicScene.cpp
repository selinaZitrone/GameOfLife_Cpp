#include "MyGraphicScene.h"
#include <QGraphicsSceneMouseEvent>
#include <QtDebug>
#include "mainwindow.h"
#include "gamewindow.h"

using namespace std;
#include <vector>

extern MainWindow * mainWin;
extern GameWindow * gameWin;


MyGraphicScene::MyGraphicScene(QMainWindow *parent)
{
    myDimension = 0;
}

MyGraphicScene::MyGraphicScene(QGraphicsItem *parent)
{
    myDimension = 0;
}



void MyGraphicScene::mousePressEvent(QGraphicsSceneMouseEvent *event){
    // qDebug() << event->scenePos().x() << " " << event->scenePos().y();

    mainWin->toggleCells(event->scenePos().x(), event->scenePos().y(), this);
    gameWin->toggleCells(event->scenePos().x(), event->scenePos().y(), this);

}

void MyGraphicScene::paintLife(vector<bool> array, int len)
{
    // the border stays right bottom
    // if you change it, remember to change the function to toggle cells to account for it!

    // dimension in pixel of the View
    int viewDim = 500; // if I use "mainWin->get_ViewResolution()" then it crashes by the first setting... WHY?
    if(myDimension != 0) viewDim = myDimension;
    //calculate the biggest area

    int cellDim = viewDim/len;
    // int bigDim = len * cellDim;
    //scene->setSceneRect(scene.)

    QImage image(viewDim, viewDim, QImage::Format_RGB32);
    QRgb value;

    QRgb livevalue = qRgb(50, 205, 50); // THE COLOR OF LIVING CELLS
    QRgb greyvalue = qRgb(220, 220, 220);

    for(int i = 0; i < len; i++){
        for(int e = 0; e < len; e++){

             if(array[(i*len) + e]){ // check if true or false
                 value = livevalue;
             } else {
                 value = greyvalue;
             }
            for(int x = 0; x < cellDim; x++){
                for(int y = 0; y < cellDim; y++){
                    image.setPixel(e*cellDim + x, i*cellDim + y, value);
            }

             }
        }
    }

    // Print it
    setSceneRect(0,0,viewDim,viewDim);
    addPixmap(QPixmap::fromImage(image));
}
