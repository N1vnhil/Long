#include "bullet.h"
#include "config.h"

PlayerBullet::PlayerBullet() {
    bullet.load(PLAYER_BULLET_PATH);
    posX = GAME_WIDTH / 2 - bullet.width(); posY = GAME_HEIGHT;
    free = true;
    speed = PLAYER_BULLET_SPEED;

    m_Rect.setWidth(bullet.width());
    m_Rect.setHeight(bullet.height());
    m_Rect.moveTo(posX, posY);
}

EnemyBullet::EnemyBullet() {
    bullet.load(ENEMY_BULLET_PATH);
    free = true;
    posX = GAME_WIDTH / 2 - bullet.width(); posY = 0;
    speed = ENEMY_BULLET_SPEED;

    m_Rect.setWidth(bullet.width() * 0.5);
    m_Rect.setHeight(bullet.height() * 0.5);
    m_Rect.moveTo(posX, posY);
}

void PlayerBullet::updatePosition() {
    if(free) return;

    posY -= PLAYER_BULLET_SPEED;
    m_Rect.moveTo(posX, posY);

    if(posY < -m_Rect.height()) free = true;
}

void EnemyBullet::updatePosition() {
    if(free) return;
    posY += ENEMY_BULLET_SPEED;
    m_Rect.moveTo(posX, posY);
    if(posY > GAME_HEIGHT) free = true;
}

void EnemyBullet::updateLeft() {
    if(free) return;
    posY += ENEMY_BULLET_SPEED;
    posX -= ENEMY_BULLET_SPEED * 0.6;
    m_Rect.moveTo(posX, posY);
    if(posY > GAME_HEIGHT || posX < 0 || posX > GAME_WIDTH) free = true;
}

void EnemyBullet::updateRight() {
    if(free) return;
    posY += ENEMY_BULLET_SPEED;
    posX += ENEMY_BULLET_SPEED * 0.6;
    m_Rect.moveTo(posX, posY);
    if(posY > GAME_HEIGHT || posX < 0 || posX > GAME_WIDTH) free = true;
}

Bullet::Bullet() {}
