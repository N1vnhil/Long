#ifndef BULLET_H
#define BULLET_H

#include <QRect>
#include <QPixmap>

class Bullet {
public:
    Bullet();
    void updatePosition();

    int posX, posY, speed;
    bool free;

    QRect m_Rect;
    QPixmap bullet;
};

#endif // BULLET_H
