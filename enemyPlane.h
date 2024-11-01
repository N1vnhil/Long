#ifndef ENEMYPLANE_H
#define ENEMYPLANE_H

#include <QPIXmap>
#include <QRect>
#include "config.h"
#include "bullet.h"

class EnemyPlane {
public:
    EnemyPlane();
    void updatePosition();

    QPixmap enemy;
    int posX, posY;



    bool free;
    int speed, hp, c;

    QRect m_Rect;
    EnemyBullet bullets[ENEMY_BULLET_NUMBER];
    EnemyBullet bulletLeft[ENEMY_BULLET_NUMBER];
    EnemyBullet bulletRight[ENEMY_BULLET_NUMBER];

    void shoot();
};

#endif // ENEMYPLANE_H
