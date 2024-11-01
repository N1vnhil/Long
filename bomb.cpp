#include "bomb.h"
#include "config.h"

Bomb::Bomb() {
    posX = 0; posY = 0;
    free = true;
    c = 0;
    idx = 0;

    for(int i=1; i<=BOMB_MAX; i++) {
        QString path  = QString(BOMB_PATH).arg(i);
        pics.push_back(QPixmap(path));
    }
}

void Bomb::updateInfo() {
    if(free) return;

    c++;
    if(c < BOMB_INTERVAL) return;

    c = 0;

    idx++;
    if(idx > BOMB_MAX - 1) {
        idx = 0;
        free = true;
    }
}

PlayerExplosion::PlayerExplosion() {
    posX = 0; posY = 0;
    c = 0; idx = 0;
    free = true;

    for(int i=1; i<=PLAYER_EXPLOSION_MAX; i++) {
        QString path = QString(PLAYER_EXPLOSION_PATH).arg(i);
        pics.push_back(QPixmap(path));
    }
}

void PlayerExplosion::updateInfo() {
    c++;
    if(c < PLAYER_EXPLOSION_INTERVAL) return;

    c = 0;
    idx++;
    if(idx > PLAYER_EXPLOSION_MAX - 1) {
        idx = 0; free = true;
    }
}
