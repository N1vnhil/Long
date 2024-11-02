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
#include "bossPlane.h"

class Widget : public QWidget
{
    Q_OBJECT
    QTimer timer;
    Map m_map;
    PlayerPlane m_plane;
    BossPlane boss1;
    int survive_label;

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

    void bossToScene();

    EnemyPlane enemies[ENEMY_NUMBER];

    Bomb bombs[BOMB_NUMBER];

    int enemy_c;

    QSoundEffect* bombSound;
    QSoundEffect* bgSound;
    QSoundEffect* bg2Sound;
    QSoundEffect* bulletSound;
    QSoundEffect* winSound;

    QRect t_rect;

    void kill(EnemyPlane* enemy);

    void kill(BossPlane* boss);

    bool flag;
};
#endif // WIDGET_H
