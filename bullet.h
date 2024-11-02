#ifndef BULLET_H
#define BULLET_H

#include <QRect>
#include <QPixmap>
#include "bomb.h"

class Bullet {
public:
    Bullet();
    virtual void updatePosition() = 0;

    int posX, posY, speed;
    bool free;

    QRect m_Rect;
    QPixmap bullet;
};

class EnemyBullet: public Bullet {
public:
    EnemyBullet();
    void updateLeft();
    void updateRight();
    void updatePosition();
};

class PlayerBullet: public Bullet {
public:
    PlayerBullet();
    void updatePosition();
};

class BossBullet1: public Bullet {
public:
    BossBullet1();
    void updatePosition();
};

class BossBullet2: public Bullet {
public:
    BossBullet2();
    void updatePosition();
};

class BossMine1: public Bullet {
public:
    int time_c;
    BossMine1();
    void updatePosition();
    void explode();
    Boss1MineExplosion mineExplosion;
};

#endif // BULLET_H
