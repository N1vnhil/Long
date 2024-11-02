#ifndef BOSSPLANE_H
#define BOSSPLANE_H

#include <QPixmap>
#include "bullet.h"
#include "config.h"

class BossPlane {
public:
    BossPlane();
    QPixmap boss1;
    int posX, posY;
    bool free;
    int speed, hp, c, collide_c, b2c;
    QRect m_Rect;

    void shoot();

    BossBullet1 bullets1_c1[BOSS_BULLET1_NUMBER];
    BossBullet1 bullets1_c2[BOSS_BULLET1_NUMBER];
    BossBullet1 bullets1_c3[BOSS_BULLET1_NUMBER];
    BossBullet1 bullets1_c4[BOSS_BULLET1_NUMBER];

    BossBullet2 bullets2[BOSS_BULLET2_NUMBER];

    BossMine1 mines[BOSS1_MINE_NUMBER];
};

#endif // BOSSPLANE_H
