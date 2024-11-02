#include "enemyPlane.h"
#include "config.h"

EnemyPlane::EnemyPlane() {
    enemy.load(ENEMY_PATH);
    posX = 0; posY = 0;
    free = true;
    speed = ENEMY_SPEED;
    m_Rect.setWidth(enemy.width() / 4);
    m_Rect.setHeight(enemy.height() / 2);
    m_Rect.moveTo(posX, posY);
    hp = ENEMY_HP;
    c = 0;
}

void EnemyPlane::updatePosition() {
    if(free) {return;}

    posY += speed;

    if(posX <= 0) {posX = 0;}
    if(posX + enemy.width() > GAME_WIDTH) {posX = GAME_WIDTH - enemy.width();}

    m_Rect.moveTo(posX + 20, posY);

    if(posY >= GAME_HEIGHT + enemy.height()) free = true;
}

void EnemyPlane::shoot() {
    c++;
    if(c < ENEMY_BULLET_INTERVAL) return;

    c = 0;

    for(int i=0; i<ENEMY_BULLET_NUMBER; i++) {
        if(bullets[i].free) {
            bullets[i].free = false;
            bullets[i].posX = posX + 5;
            bullets[i].posY = posY + 40;
            break;
        }
    }

    for(int i=0; i<ENEMY_BULLET_NUMBER; i++) {
        if(bulletLeft[i].free) {
            bulletLeft[i].free = false;
            bulletLeft[i].posX = posX + 5;
            bulletLeft[i].posY = posY + 40;
            break;
        }
    }

    for(int i=0; i<ENEMY_BULLET_NUMBER; i++) {
        if(bulletRight[i].free) {
            bulletRight[i].free = false;
            bulletRight[i].posX = posX + 5;
            bulletRight[i].posY = posY + 40;
            break;
        }
    }
}
