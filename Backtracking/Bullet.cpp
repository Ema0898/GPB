#include "Bullet.h"
#include <QTimer>
using namespace std;

Bullet::Bullet(vector<int> path_){
    path = path_;
    // drew the rect

    //setRect(0,0,50,50);
    // connect
    QTimer * timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));

    timer->start(5);
}

void Bullet::move(){
    // move bullet up
    if(path.size() > 0){
        if(path.back() == 0){
            setPixmap(QPixmap(":/images/img/naveAR.png"));
            setPos(x(),y()-1);
        }
        else if(path.back() == 1){
            setPixmap(QPixmap(":/images/img/naveDE.png"));
            setPos(x()+1,y());
        }
        else if(path.back() == 2){
            setPixmap(QPixmap(":/images/img/naveIZ.png"));
            setPos(x()-1,y());
        }
        else{
            setPixmap(QPixmap(":/images/img/naveAB.png"));
            setPos(x(),y()+1);
        }

        if(contador == 49){
            path.pop_back();
            contador = 0;
        }else{
            contador+=1;
        }
    }
}
