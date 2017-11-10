#include "mainwindow.h"
#include <QApplication>

/*int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();


    return a.exec();
}*/

#include "Myrect.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <iostream>
#include "Maze.h"
#include <vector>

using namespace std;

int main(int argc, char *argv[]){
    QApplication a(argc, argv);

    // create a scene
    QGraphicsScene * scene = new QGraphicsScene();

    // create an item to add to the scene
    MyRect * rect = new MyRect();
    rect->setRect(0,0,0,0); // change the rect from 0x0 (default) to 100x100 pixels

    // add the item to the scene
    scene->addItem(rect);

    // make rect focusable
    rect->setFlag(QGraphicsItem::ItemIsFocusable);
    rect->setFocus();

    // create a view to visualize the scene
    QGraphicsView * view = new QGraphicsView(scene);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QGraphicsPixmapItem *fondo = new QGraphicsPixmapItem;
    fondo->setPos(0,0);
    fondo->setPixmap(QPixmap(":/images/img/space.jpg"));
    scene->addItem(fondo);
    // show the view
    view->show();
    view->setFixedSize(1200,550);
    scene->setSceneRect(0,0,1200,550);



    return a.exec();
}
