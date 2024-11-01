#ifndef PLAYERPLANE_H
#define PLAYERPLANE_H

#include <QRect>
#include <QPixmap>
#include "bullet.h"
#include "config.h"
#include <QSoundEffect>
#include "bomb.h"

class PlayerPlane {
public:
    PlayerPlane();
    void setPos(int x, int y);
    void shoot();

    int posX, posY;
    QRect m_Rect;
    QPixmap plane;


    PlayerBullet bullets[PLAYER_BULLET_NUMBER];
    int c;

    int hp, kill_c, score, hit_c;

    void getHit();
    QSoundEffect* hitSound;

    PlayerExplosion explosion;

};

#endif // PLAYERPLANE_H
