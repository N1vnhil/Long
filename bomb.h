#ifndef BOMB_H
#define BOMB_H

#include <QPixmap>
#include <QVector>
class Bomb {
public:
    Bomb();
    void updateInfo();

    QVector<QPixmap> pics;
    int posX, posY;
    bool free;
    int c;
    int idx;
};

class PlayerExplosion {
public:
    PlayerExplosion();
    void updateInfo();
    QVector<QPixmap> pics;
    int posX, posY;
    int c, idx; bool free;
};

class Boss1MineExplosion {
public:
    Boss1MineExplosion();
    int posX, posY;
    QVector<QPixmap> pics;
    int c, idx; bool free;
    void updateInfo();
};

#endif // BOMB_H
