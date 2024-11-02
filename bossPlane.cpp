#include "bossPlane.h"
#include "config.h"
#include "bullet.h"

BossPlane::BossPlane() {
    boss1.load(BOSS1_PATH);
    posX = 20; posY = -50;
    free = true;
    m_Rect.setWidth(GAME_WIDTH);
    m_Rect.setHeight(boss1.height());
    m_Rect.moveTo(posX, posY);

    hp = BOSS1_HP;
    collide_c = 0;

    b2c = 0;
}

void BossPlane::shoot() {
    c++;
    if(c < BOSS_BULLET1_INTERVAL) return;

    c = 0;

    if(hp < BOSS1_HP * 0.8) {
        for(int i=0; i<BOSS_BULLET1_NUMBER; i++) {
            if(bullets1_c1[i].free) {
                bullets1_c1[i].free = false;
                bullets1_c1[i].posX = 50;
                bullets1_c1[i].posY = 200;
                break;
            }
        }

        for(int i=0; i<BOSS_BULLET1_NUMBER; i++) {
            if(bullets1_c2[i].free) {
                bullets1_c2[i].free = false;
                bullets1_c2[i].posX = 100;
                bullets1_c2[i].posY = 200;
                break;
            }
        }

        for(int i=0; i<BOSS_BULLET1_NUMBER; i++) {
            if(bullets1_c3[i].free) {
                bullets1_c3[i].free = false;
                bullets1_c3[i].posX = GAME_WIDTH - 50;
                bullets1_c3[i].posY = 200;
                break;
            }
        }

        for(int i=0; i<BOSS_BULLET1_NUMBER; i++) {
            if(bullets1_c4[i].free) {
                bullets1_c4[i].free = false;
                bullets1_c4[i].posX = GAME_WIDTH - 100;
                bullets1_c4[i].posY = 200;
                break;
            }
        }
    }


    for(int i=0; i<BOSS_BULLET2_NUMBER; i++) {
        if(bullets2[i].free) {
            bullets2[i].free = false;
            bullets2[i].posX = GAME_WIDTH / 2 - 50 + 50 * (b2c++ % 3);
            bullets2[i].posY = 200;
            break;
        }
    }

    if(hp < BOSS1_HP * 0.6) {
        for(int i=0; i<BOSS1_MINE_NUMBER; i++) {
            if(mines[i].free) {
                mines[i].free = false;
                mines[i].posX = rand() % GAME_WIDTH - mines[i].bullet.width();
                mines[i].posY = rand() % 200 + 500;
                break;
            }
        }
    }
}
