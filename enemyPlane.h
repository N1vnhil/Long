#ifndef ENEMYPLANE_H
#define ENEMYPLANE_H

#include <QPIXmap>
#include <QRect>
#include "config.h"

class EnemyPlane {
public:
    EnemyPlane();
    void updatePosition();

    QPixmap enemy;
    int posX, posY;

    QRect m_Rect;

    bool free;
    int speed;

    int hp; int dx;
};

#endif // ENEMYPLANE_H
