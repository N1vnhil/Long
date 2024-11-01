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
}

void EnemyPlane::updatePosition() {
    if(free) return;

    posY += speed;

    if(posX <= 0) {dx *= -1; posX = 0;}
    if(posX + enemy.width() > GAME_WIDTH) {dx *= -1; posX = GAME_WIDTH - enemy.width();}

    m_Rect.moveTo(posX + 20, posY);

    if(posY >= GAME_HEIGHT + enemy.height()) free = true;
}
