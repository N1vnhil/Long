#ifndef BULLET_H
#define BULLET_H

#include <QRect>
#include <QPixmap>

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

#endif // BULLET_H
