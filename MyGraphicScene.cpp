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
    myPixelResolution = 0;
}

MyGraphicScene::MyGraphicScene(QGraphicsItem *parent)
{
    myPixelResolution = 0;
}

/*!
 * overrides a member function fo QGraphicsScene and uses it to inform main window and game window about clicks on the scenes
 */
void MyGraphicScene::mousePressEvent(QGraphicsSceneMouseEvent *event){
    mainWin->toggleCells(event->scenePos().x(), event->scenePos().y(), this);
    gameWin->toggleCells(event->scenePos().x(), event->scenePos().y(), this);
}

/*!
 * \brief Paints a cellfield on the scene (colors defined inside the function)
 * \param cellField is the vector describing the cells status
 * \param len is the length of one side of the field, aka: how many cells per line
 */
void MyGraphicScene::paintLife(vector<bool> cellField, int len)
{
    // the cell is painted top left... therefore there could be an unused border bottom right...
    // if you change it, remember to change the function to toggle cells to account for it!

    // dimension in pixel of the View
    int viewDim = 500; // if I use "mainWin->get_ViewResolution()" then it crashes by the first setting... unknown reason
    if(myPixelResolution != 0) viewDim = myPixelResolution; // override the dimension of the view, if it has been set (used in two player game)

    // calculate the dimension of a cell
    int cellDim = viewDim/len;

    // create a new image of the necessary dimension
    QImage image(viewDim, viewDim, QImage::Format_RGB32);

    QRgb value; // this will be the color of the cell - switching between live and grey value

    QRgb livevalue = qRgb(50, 205, 50); // THE COLOR OF LIVING CELLS - actual: green
    QRgb greyvalue = qRgb(220, 220, 220); // the color of the field - actual: grey

    for(int i = 0; i < len; i++){
        for(int e = 0; e < len; e++){

            if(cellField[(i*len) + e]){ // check if true or false to determine the color
                 value = livevalue;
            } else {
                 value = greyvalue;
            }

             // paint a whole cell (a square of cellDim pixels)
            for(int x = 0; x < cellDim; x++){
                for(int y = 0; y < cellDim; y++){
                    image.setPixel(e*cellDim + x, i*cellDim + y, value);
                }
            }
        }
    }

    // set the dimension of the scene
    setSceneRect(0,0,viewDim,viewDim);
    // add the generated image to the scene (after trasforming it in a Pixmap)
    addPixmap(QPixmap::fromImage(image));
}
