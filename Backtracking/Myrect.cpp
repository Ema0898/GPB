#include "Myrect.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include "Bullet.h"
#include "Maze.h"
#include <QDebug>
#include <QGraphicsPixmapItem>
bool space= true;
void MyRect::keyPressEvent(QKeyEvent *event){


    if ((event->key() == Qt::Key_Space)& space){
        space = false;
        int row = 5;
        int col = 0;

        Maze maze1;
        maze1.setStart( row, col );
        maze1.printMaze();
        for(int i = 0; i < 24; i++){
            for(int j = 0; j < 11; j++){
                /*QGraphicsRectItem * rect = new QGraphicsRectItem();
                rect->setRect(i*50,j*50,50,50);
                if(maze1.getCell(j,i) == '+'){
                    rect->setBrush(QColor(45,45,45));
                }
                if(maze1.getCell(j,i) == 'E'){
                    rect->setBrush(QColor(255,255,0));

                }
                if(maze1.getCell(j,i) == 'S'){
                    rect->setBrush(QColor(0,255,0));
                }
                scene()->addItem(rect);*/
                QGraphicsPixmapItem *elemento = new QGraphicsPixmapItem;
                elemento->setPos(i*50,j*50);

                if(maze1.getCell(j,i) == '+'){
                    elemento->setPixmap(QPixmap(":/images/img/asteroid.png"));
                }
                if(maze1.getCell(j,i) == 'B'){
                    elemento->setPixmap(QPixmap(":/images/img/Base.png"));


                }
                if(maze1.getCell(j,i) == 'S'){
                }
                scene()->addItem(elemento);
            }

        }
        if ( maze1.backTrack( row, col ) == true )
        {
            cout << "Congratulations!" << endl;
        }
        else
        {
            cout << "Sorry, you didn't find the exit." << endl;
        }

        vector<int> path = maze1.getpath();
        // create a bullet
        Bullet * bullet = new Bullet(path);
        bullet->setPos(x(),y()+250);
        scene()->addItem(bullet);
    }
}
