#ifndef MYGRAPHICSCENE_H
#define MYGRAPHICSCENE_H

#include <QGraphicsScene>
#include <QMainWindow>

class MyGraphicScene : public QGraphicsScene
{
    Q_OBJECT

public:
    MyGraphicScene(QMainWindow * parent = 0);
    MyGraphicScene(QGraphicsItem * parent = 0);
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void paintLife(int array[], int len);


};

#endif // MYGRAPHICSCENE_H
