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
    hitSound = new QSoundEffect;
    hitSound->setSource(QUrl::fromLocalFile(SOUND_HIT));
}

void PlayerPlane::shoot() {
    c++;
    if(c < PLAYER_BULLET_INTERVAL) return;

    c = 0;

    for(int i=0; i<PLAYER_BULLET_NUMBER; i++) {
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

void PlayerPlane::getHit() {
    hp--;
    hitSound->play();
    explosion.free = false;
    explosion.posX = posX;
    explosion.posY = posY;
}
