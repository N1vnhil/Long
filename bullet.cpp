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

Bullet::Bullet() {

}

// boss bullet 1 is common bullet

BossBullet1::BossBullet1() {
    bullet.load(BOSS_BULLET1_PATH);
    posX =0; posY = 0;
    free = true;
    speed = BOSS_BULLET1_SPEED;

    m_Rect.setWidth(bullet.width() * 0.8);
    m_Rect.setHeight(bullet.height());
    m_Rect.moveTo(posX, posY);
}

void BossBullet1::updatePosition() {
    if(free) return;
    posY += BOSS_BULLET1_SPEED;
    m_Rect.moveTo(posX, posY);
    if(posY > GAME_HEIGHT || posX < 0 || posX > GAME_WIDTH) free = true;
}

BossBullet2::BossBullet2() {
    bullet.load(BOSS_BULLET2_PATH);
    posX =0; posY = 0;
    free = true;
    speed = BOSS_BULLET2_SPEED;

    m_Rect.setWidth(bullet.width() * 0.8);
    m_Rect.setHeight(bullet.height() * 0.8);
    m_Rect.moveTo(posX, posY);
}

void BossBullet2::updatePosition() {
    if(free) return;
    posY += BOSS_BULLET2_SPEED;
    m_Rect.moveTo(posX, posY);
    if(posY > GAME_HEIGHT || posX < 0 || posX > GAME_WIDTH) free = true;
}

BossMine1::BossMine1() {
    bullet.load(QString(BOSS1_MINE_PATH).arg(1));
    posX = 0; posY = 0;
    free = true;
    speed = 0;

    time_c = 0;
    m_Rect.setWidth(bullet.width() * 0.8);
    m_Rect.setHeight(bullet.height() * 0.8);
    time_c++; m_Rect.moveTo(posX + bullet.width() * 0.1, posY + bullet.height() * 0.1);
}

void BossMine1::updatePosition() {
    if(free) return;
    time_c++; m_Rect.moveTo(posX + bullet.width() * 0.1, posY + bullet.height() * 0.1);
    if(time_c > BOSS1_MINE_TIME) {free = true; time_c = 0;}
}

void BossMine1::explode() {
    free = true;
    mineExplosion.free = false;
    mineExplosion.posX = posX;
    mineExplosion.posY = posY;
}
