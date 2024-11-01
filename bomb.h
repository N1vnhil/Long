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

#endif // BOMB_H
