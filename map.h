#ifndef MAP_H
#define MAP_H
#include <QPixmap>

class Map {
public:
    QPixmap m_map1, m_map2;
    int m_map1_posY, m_map2_posY;
    int m_scroll_speed;
    Map();

    void mapPosition();
};

#endif // MAP_H
