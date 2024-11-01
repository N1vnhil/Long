#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>
#include "map.h"
#include "playerPlane.h"
#include "enemyPlane.h"
#include "bomb.h"
#include <QSoundEffect>
#include <QMediaPlayer>

class Widget : public QWidget
{
    Q_OBJECT
    QTimer timer;
    Map m_map;
    PlayerPlane m_plane;

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void initScene();

    void playGame();

    void updatePosition();

    void paintEvent(QPaintEvent *);

    void mouseMoveEvent(QMouseEvent*);

    void enemyToScene();

    void collisionDetection();

    void endEvent();

    EnemyPlane enemies[ENEMY_NUMBER];

    Bomb bombs[BOMB_NUMBER];

    int enemy_c;

    QSoundEffect* bombSound;
    QSoundEffect* bgSound;

    QRect t_rect;

    void kill(EnemyPlane* enemy);
};
#endif // WIDGET_H
