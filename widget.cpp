#include "widget.h"
#include "config.h"
#include <QIcon>
#include <QPainter>
#include <QMouseEvent>
#include <QSoundEffect>
#include <QMediaPlayer>
#include <QAudioOutput>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    bombSound = new QSoundEffect;
    bgSound = new QSoundEffect;
    hitSound = new QSoundEffect;

    initScene();
    playGame();

    bombSound->setSource(QUrl::fromLocalFile(SOUND_BOMB));
    bgSound->setSource(QUrl::fromLocalFile(SOUND_BG));
    hitSound->setSource(QUrl::fromLocalFile(SOUND_HIT));
    bgSound->play();
}

Widget::~Widget() {}

void Widget::initScene()
{
    setFixedSize(GAME_WIDTH, GAME_HEIGHT);
    setWindowTitle(GAME_TITLE);
    setWindowIcon(QIcon(GAME_ICON));
    timer.setInterval(GAME_RATE);
    srand((unsigned int)time(NULL));
    enemy_c = 0;
}

void Widget::playGame() {
    timer.start(); bgSound->play();
    connect(&timer, &QTimer::timeout, [=](){
        enemyToScene();
        collisionDetection();
        updatePosition();
        update();
        if(!bgSound->isPlaying()) bgSound->play();
    });
}

void Widget::updatePosition() {
    m_map.mapPosition();

    m_plane.shoot(); m_plane.score++;

    for(int i=0; i<BULLET_NUMBER; i++) {
        if(!m_plane.bullets[i].free) m_plane.bullets[i].updatePosition();
    }

    for(int i=0; i<ENEMY_NUMBER; i++) {
        if(!enemies[i].free) enemies[i].updatePosition();
    }

    for(int i=0; i<BOMB_NUMBER; i++) {
        if(!bombs[i].free) bombs[i].updateInfo();
    }

}

void Widget::paintEvent(QPaintEvent*) {
    QPainter painter(this);

    painter.drawPixmap(0, m_map.m_map1_posY, m_map.m_map1);
    painter.drawPixmap(0, m_map.m_map2_posY, m_map.m_map2);

    painter.drawPixmap(m_plane.posX, m_plane.posY, m_plane.plane);

    painter.drawPixmap(10, 10, QPixmap(HEART_PATH));

    t_rect.setRect(28, 7, GAME_WIDTH, 50);
    painter.setFont(QFont("Arial", 15, 5));
    painter.drawText(t_rect, Qt::AlignLeft, QString::number(m_plane.hp), 0);

    for(int i=0; i<BULLET_NUMBER; i++) {
        if(!m_plane.bullets[i].free) painter.drawPixmap(m_plane.bullets[i].posX, m_plane.bullets[i].posY, m_plane.bullets[i].bullet);
    }

    for(int i=0; i<ENEMY_NUMBER; i++) {
        if(!enemies[i].free) painter.drawPixmap(enemies[i].posX, enemies[i].posY, enemies[i].enemy);
    }

    for(int i=0; i<BOMB_NUMBER; i++) {
        if(!bombs[i].free) painter.drawPixmap(bombs[i].posX, bombs[i].posY, bombs[i].pics[bombs[i].idx]);
    }

    if(m_plane.hp == 0) {
        painter.setFont(QFont("Constantia", 40, 5));
        t_rect.setRect(0, 0, GAME_WIDTH, GAME_HEIGHT);

        painter.setPen(QColor(Qt::darkRed));
        painter.drawText(t_rect, Qt::AlignCenter, "score: " + QString::number(m_plane.score), 0);
    }
}

void Widget::mouseMoveEvent(QMouseEvent* event) {

    int x = event->position().x() - m_plane.plane.width() / 2, y = event->position().y() - m_plane.plane.height() / 2;

    if(x < 0) x = 0;
    if(y < 0) y = 0;
    if(x > GAME_WIDTH - m_plane.m_Rect.width()) x = GAME_WIDTH - m_plane.m_Rect.width();
    if(y > GAME_HEIGHT - m_plane.m_Rect.height()) y = GAME_HEIGHT - m_plane.m_Rect.height();

    m_plane.setPos(x, y);
}

void Widget::enemyToScene() {
    enemy_c++;
    if(enemy_c < ENEMY_INTERVAL) return;

    enemy_c = 0;

    for(int i=0; i<ENEMY_NUMBER; i++) {
        if(enemies[i].free) {
            enemies[i].free = false;
            enemies[i].hp = ENEMY_HP;
            enemies[i].posX = rand() % (GAME_WIDTH - enemies[i].m_Rect.width());
            enemies[i].posY = -enemies[i].m_Rect.height();
            break;
        }
    }
}

void Widget::collisionDetection() {
    for(int i=0; i<ENEMY_NUMBER; i++) {
        if(enemies[i].free) continue;

        for(int j=0; j<BULLET_NUMBER; j++) {
            if(m_plane.bullets[j].free) continue;

            if(enemies[i].m_Rect.intersects(m_plane.bullets[j].m_Rect)) {
                enemies[i].hp--;
                if(enemies[i].hp <= 0) {
                    kill(&enemies[i]);
                }
                m_plane.bullets[j].free = true;

            }
        }

        if(enemies[i].m_Rect.intersects(m_plane.m_Rect)) {

            m_plane.hit_c++;
            if(m_plane.hit_c < HIT_INTERVAL) return;

            m_plane.hit_c = 0;
            m_plane.hp--;
            hitSound->play();

            kill(&enemies[i]);

            if(m_plane.hp == 0) endEvent();
        }
    }
}

void Widget::endEvent() {
    timer.stop();
}

void Widget::kill(EnemyPlane* enemy) {
    enemy->free = true; m_plane.kill_c++;
    m_plane.score += 1000;

    bombSound->play();

    for(int k=0; k<BOMB_NUMBER; k++) {
        if(bombs[k].free) {
            bombs[k].free = false;
            bombs[k].posX = enemy->posX;
            bombs[k].posY = enemy->posY;
            break;
        }
    }
}


