#include "playerPlane.h"
#include "config.h"

PlayerPlane::PlayerPlane() {
    plane.load(PLANE_PATH);
    posX = (GAME_WIDTH - plane.width()) / 2; posY = GAME_HEIGHT - plane.height();

    m_Rect.setWidth(plane.width() * 0.9);
    m_Rect.setHeight(plane.height() * 0.9);
    m_Rect.moveTo(posX, posY);

    c = 0; hp = PLAYER_HP; kill_c = 0; score = 0;
    hit_c = HIT_INTERVAL;
}

void PlayerPlane::shoot() {
    c++;
    if(c < BULLET_INTERVAL) return;

    c = 0;

    for(int i=0; i<BULLET_NUMBER; i++) {
        if(bullets[i].free) {
            bullets[i].free = false;
            bullets[i].posX = posX - 9;
            bullets[i].posY = posY - 25;
            break;
        }
    }
}

void PlayerPlane::setPos(int x, int y) {
    posX = x; posY = y;
    m_Rect.moveTo(posX, posY);
}

