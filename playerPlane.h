#ifndef PLAYERPLANE_H
#define PLAYERPLANE_H

#include <QRect>
#include <QPixmap>
#include "bullet.h"
#include "config.h"

class PlayerPlane {
public:
    PlayerPlane();
    void setPos(int x, int y);
    void shoot();

    int posX, posY;
    QRect m_Rect;
    QPixmap plane;

    Bullet bullets[BULLET_NUMBER];
    int c;

    int hp, kill_c, score, hit_c;
};

#endif // PLAYERPLANE_H
