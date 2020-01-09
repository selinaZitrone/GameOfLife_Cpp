#ifndef MYGRAPHICSCENE_H
#define MYGRAPHICSCENE_H

#include <QGraphicsScene>
#include <QMainWindow>
using namespace std;
#include <vector>

class MyGraphicScene : public QGraphicsScene
{
    Q_OBJECT

public:
    MyGraphicScene(QMainWindow * parent = 0);
    MyGraphicScene(QGraphicsItem * parent = 0);
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void paintLife(vector<bool>, int len);


};

#endif // MYGRAPHICSCENE_H
