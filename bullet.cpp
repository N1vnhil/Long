#include "bullet.h"
#include "config.h"

Bullet::Bullet() {
    bullet.load(BULLET_PATH);
    posX = GAME_WIDTH / 2 - bullet.width(); posY = GAME_HEIGHT;
    free = true;
    speed = BULLET_SPEED;

    m_Rect.setWidth(bullet.width());
    m_Rect.setHeight(bullet.height());
    m_Rect.moveTo(posX, posY);
}

void Bullet::updatePosition() {
    if(free) return;

    posY -= BULLET_SPEED;
    m_Rect.moveTo(posX, posY);

    if(posY < -m_Rect.height()) free = true;
}
