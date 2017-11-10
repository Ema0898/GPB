#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QObject>
#include <vector>

using namespace std;

class Bullet: public QObject,public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Bullet(vector<int>);
    vector<int> path;
    int contador = 0;
public slots:
    void move();
};

#endif // BULLET_H
