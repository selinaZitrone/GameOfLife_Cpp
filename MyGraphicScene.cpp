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
