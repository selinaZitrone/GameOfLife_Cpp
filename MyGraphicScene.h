#ifndef MYGRAPHICSCENE_H
#define MYGRAPHICSCENE_H

#include <QGraphicsScene>
#include <QMainWindow>
using namespace std;
#include <vector>

/*!
 * Class inerithed from QGraphicsScene - contains functions "paintLife" and "mousePressEvent", which allow repainting and click tracking
 */
class MyGraphicScene : public QGraphicsScene
{
    Q_OBJECT

public:
    // constructors
    MyGraphicScene(QMainWindow * parent = 0);
    MyGraphicScene(QGraphicsItem * parent = 0);

    // member fucntions
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void paintLife(vector<bool>, int len);

    // variables
    int myPixelResolution; //<! the pixel resolution of one side of this scene (it is a square)


};

#endif // MYGRAPHICSCENE_H
