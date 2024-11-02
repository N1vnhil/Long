#include "widget.h"
#include "config.h"
#include <QIcon>
#include <QPainter>
#include <QMouseEvent>
#include <QSoundEffect>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QPoint>
#include <QCursor>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    bombSound = new QSoundEffect;
    bgSound = new QSoundEffect;
    bg2Sound = new QSoundEffect;
    bulletSound = new QSoundEffect;
    winSound = new QSoundEffect;

    survive_label = 0;

    setCursor(Qt::BlankCursor);
    setMouseTracking(true);
    QCursor::setPos(this->pos().x() + m_plane.posX + m_plane.plane.width() / 2 + 760, this->pos().y() + m_plane.posY + 120);


    initScene();
    playGame();

    bombSound->setSource(QUrl::fromLocalFile(SOUND_BOMB));
    bgSound->setSource(QUrl::fromLocalFile(SOUND_BG1));
    bg2Sound->setSource(QUrl::fromLocalFile(SOUND_BG2));
    bulletSound->setSource(QUrl::fromLocalFile(SOUND_BULLET));
    winSound->setSource(QUrl::fromLocalFile(SOUND_WIN));

    bgSound->play(); flag = true;
}

Widget::~Widget() {
    delete bombSound;
    delete bgSound;
    delete bulletSound;
    delete winSound;
}

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
        if(boss1.free) enemyToScene();
        bossToScene();
        collisionDetection();
        updatePosition();
        update();
        survive_label++;
        if(!bgSound->isPlaying()) bgSound->play();
    });
}

void Widget::updatePosition() {

    m_map.mapPosition();

    m_plane.shoot(); m_plane.score++;

    for(int i=0; i<PLAYER_BULLET_NUMBER; i++) {
        if(!m_plane.bullets[i].free) m_plane.bullets[i].updatePosition();
    }

    // update boss
    if(!boss1.free) {
        boss1.shoot();

        // update boss bullet1
        for(int i=0; i<BOSS_BULLET1_NUMBER; i++) {
            if(!boss1.bullets1_c1[i].free) boss1.bullets1_c1[i].updatePosition();
            if(!boss1.bullets1_c2[i].free) boss1.bullets1_c2[i].updatePosition();
            if(!boss1.bullets1_c3[i].free) boss1.bullets1_c3[i].updatePosition();
            if(!boss1.bullets1_c4[i].free) boss1.bullets1_c4[i].updatePosition();
        }

        // update boss bullet2
        for(int i=0; i<BOSS_BULLET2_NUMBER; i++) {
            if(!boss1.bullets2[i].free) boss1.bullets2[i].updatePosition();
        }

        // update mine
        for(int i=0; i<BOSS1_MINE_NUMBER; i++) {
            if(!boss1.mines[i].free) boss1.mines[i].updatePosition();
            if(!boss1.mines[i].mineExplosion.free) boss1.mines[i].mineExplosion.updateInfo();
        }
    }

    // update enemy
    for(int i=0; i<ENEMY_NUMBER; i++) {
        if(!enemies[i].free) {

            enemies[i].updatePosition(); enemies[i].shoot();

            // update enemy bullet position
            for(int j=0; j<ENEMY_BULLET_NUMBER; j++) {
                if(!enemies[i].bullets[j].free) enemies[i].bullets[j].updatePosition();
                if(!enemies[i].bulletLeft[j].free) enemies[i].bulletLeft[j].updateLeft();
                if(!enemies[i].bulletRight[j].free) enemies[i].bulletRight[j].updateRight();
            }
        }
    }

    // update explosions
    for(int i=0; i<BOMB_NUMBER; i++) {
        if(!bombs[i].free) bombs[i].updateInfo();
    }

    if(!m_plane.explosion.free) m_plane.explosion.updateInfo();

}

void Widget::paintEvent(QPaintEvent*) {
    QPainter painter(this);

    painter.drawPixmap(0, m_map.m_map1_posY, m_map.m_map1);
    painter.drawPixmap(0, m_map.m_map2_posY, m_map.m_map2);

    painter.drawPixmap(m_plane.posX, m_plane.posY, m_plane.plane);

    painter.drawPixmap(10, 10, QPixmap(HEART_PATH));

    // paint "Survive"
    if(survive_label < 100) {
        painter.setFont(QFont("Constantia", 40, 5));
        t_rect.setRect(0, 0, GAME_WIDTH, GAME_HEIGHT);
        painter.setPen(QColor(Qt::darkRed));
        painter.drawText(t_rect, Qt::AlignCenter, "Survive!", 0);
    }

    // paint the boss
    if(!boss1.free) {painter.drawPixmap(boss1.posX, boss1.posY, boss1.boss1);

        for(int i=0; i<BOSS_BULLET1_NUMBER; i++) {
            if(!boss1.bullets1_c1[i].free) painter.drawPixmap(boss1.bullets1_c1[i].posX, boss1.bullets1_c1[i].posY, boss1.bullets1_c1[i].bullet);
            if(!boss1.bullets1_c2[i].free) painter.drawPixmap(boss1.bullets1_c2[i].posX, boss1.bullets1_c2[i].posY, boss1.bullets1_c2[i].bullet);
            if(!boss1.bullets1_c3[i].free) painter.drawPixmap(boss1.bullets1_c3[i].posX, boss1.bullets1_c3[i].posY, boss1.bullets1_c3[i].bullet);
            if(!boss1.bullets1_c4[i].free) painter.drawPixmap(boss1.bullets1_c4[i].posX, boss1.bullets1_c4[i].posY, boss1.bullets1_c4[i].bullet);
        }

        for(int i=0; i<BOSS_BULLET2_NUMBER; i++) {
            if(!boss1.bullets2[i].free) painter.drawPixmap(boss1.bullets2[i].posX, boss1.bullets2[i].posY, boss1.bullets2[i].bullet);
        }

        // paint boss mine
        for(int i=0; i<BOSS1_MINE_NUMBER; i++) {
            if(!boss1.mines[i].free && boss1.mines[i].time_c % 20 < 10) painter.drawPixmap(boss1.mines[i].posX, boss1.mines[i].posY, boss1.mines[i].bullet);
            else if(!boss1.mines[i].free) painter.drawPixmap(boss1.mines[i].posX, boss1.mines[i].posY, QPixmap(":/res/flash.png"));

            if(!boss1.mines[i].mineExplosion.free) painter.drawPixmap(boss1.mines[i].posX, boss1.mines[i].posY, boss1.mines[i].mineExplosion.pics[boss1.mines[i].mineExplosion.idx]);
        }
    }

    t_rect.setRect(28, 7, GAME_WIDTH, 50);
    painter.setFont(QFont("Arial", 15, 5));
    painter.drawText(t_rect, Qt::AlignLeft, QString::number(m_plane.hp), 0);

    for(int i=0; i<PLAYER_BULLET_NUMBER; i++) {
        if(!m_plane.bullets[i].free) painter.drawPixmap(m_plane.bullets[i].posX, m_plane.bullets[i].posY, m_plane.bullets[i].bullet);
    }

    for(int i=0; i<ENEMY_NUMBER; i++) {
        if(!enemies[i].free) painter.drawPixmap(enemies[i].posX, enemies[i].posY, enemies[i].enemy);
    }

    // paint explosions

    for(int i=0; i<BOMB_NUMBER; i++) {
        if(!bombs[i].free) painter.drawPixmap(bombs[i].posX, bombs[i].posY, bombs[i].pics[bombs[i].idx]);
    }

    if(!m_plane.explosion.free) painter.drawPixmap(m_plane.explosion.posX, m_plane.explosion.posY, m_plane.explosion.pics[m_plane.explosion.idx]);


    // paint end game

    if(m_plane.hp == 0 && boss1.hp > 0) {
        painter.setFont(QFont("Constantia", 25, 5));
        t_rect.setRect(0, 0, GAME_WIDTH, GAME_HEIGHT);

        painter.setPen(QColor(Qt::darkRed));
        painter.drawText(t_rect, Qt::AlignCenter, "Big Long is Watching you.\nscore: " + QString::number(m_plane.score), 0);
    }

    // pass game

    if(boss1.hp == 0) {
        painter.setFont(QFont("Constantia", 30, 5));
        t_rect.setRect(0, 0, GAME_WIDTH, GAME_HEIGHT);

        painter.setPen(QColor(Qt::darkRed));
        painter.drawText(t_rect, Qt::AlignCenter, "Congratulation\nTotal score: " + QString::number(m_plane.score), 0);
    }

    // paint enemy bullet

    for(int i=0; i<ENEMY_NUMBER; i++) {
        if(enemies[i].free) continue;

        for(int j=0; j<ENEMY_BULLET_NUMBER; j++) {
            if(!enemies[i].bullets[j].free) {
                painter.drawPixmap(enemies[i].bullets[j].posX, enemies[i].bullets[j].posY, enemies[i].bullets[j].bullet);
            }

            if(!enemies[i].bulletLeft[j].free) {
                painter.drawPixmap(enemies[i].bulletLeft[j].posX, enemies[i].bulletLeft[j].posY, enemies[i].bulletLeft[j].bullet);
            }

            if(!enemies[i].bulletRight[j].free) {
                painter.drawPixmap(enemies[i].bulletRight[j].posX, enemies[i].bulletRight[j].posY, enemies[i].bulletRight[j].bullet);
            }
        }
    }

    // paint mid game

    if(m_plane.score > BOSS1_TIME && m_plane.score < BOSS1_TIME + 1000) {
        painter.setFont(QFont("Constantia", 40, 5));
        t_rect.setRect(0, 0, GAME_WIDTH, GAME_HEIGHT);
        painter.setPen(QColor(Qt::darkRed));
        painter.drawText(t_rect, Qt::AlignCenter, "Time to End!", 0);

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

void Widget::bossToScene() {
    if(m_plane.score > BOSS1_TIME) {
        boss1.free = false;
        if(bgSound->isPlaying()) bgSound->stop();
        if(!bg2Sound->isPlaying()) bg2Sound->play();
    }
}

void Widget::collisionDetection() {

    // boss detection

    if(!boss1.free) {
        // boss collision detection

        if(boss1.m_Rect.intersects(m_plane.m_Rect)) {
            boss1.collide_c++;
            if(boss1.collide_c > BOSS_COLLIDE_INTERVAL) {
                boss1.collide_c = 0;
                m_plane.getHit();
                if(m_plane.hp <= 0) endEvent();
                m_plane.posX = (GAME_WIDTH - m_plane.plane.width()) / 2;
                m_plane.posY = GAME_HEIGHT - m_plane.plane.height();

                m_plane.setPos((GAME_WIDTH - m_plane.plane.width()) / 2, GAME_HEIGHT - m_plane.plane.height());
                QCursor::setPos(this->pos().x() + m_plane.posX + m_plane.plane.width() / 2, this->pos().y() + m_plane.posY);
            }
        }

        // hit boss detection

        for(int i=0; i<PLAYER_BULLET_NUMBER; i++) {
            if(m_plane.bullets[i].free) continue;

            if(m_plane.bullets[i].m_Rect.intersects(boss1.m_Rect)) {
                bulletSound->play();
                boss1.hp--;
                m_plane.bullets[i].free = true;
                if(boss1.hp <= 0) {kill(&boss1); endEvent();}

                for(int j=0; j<BOMB_NUMBER; j++) {
                    if(bombs[j].free) {
                        bombs[j].free = false;
                        bombs[j].posX = m_plane.bullets[i].posX;
                        bombs[j].posY = m_plane.bullets[i].posY - m_plane.bullets[i].bullet.height();
                        break;
                    }
                }

            }
        }

        // bullet1 hit player detection

        for(int i=0; i<BOSS_BULLET1_NUMBER; i++) {
            if(!boss1.bullets1_c1[i].free && boss1.bullets1_c1[i].m_Rect.intersects(m_plane.m_Rect)) {
                m_plane.getHit();
                if(m_plane.hp <= 0) {endEvent(); break;}
                boss1.bullets1_c1[i].free = true;
            }

            if(!boss1.bullets1_c2[i].free && boss1.bullets1_c2[i].m_Rect.intersects(m_plane.m_Rect)) {
                m_plane.getHit();
                if(m_plane.hp <= 0) {endEvent(); break;}
                boss1.bullets1_c2[i].free = true;
            }

            if(!boss1.bullets1_c3[i].free && boss1.bullets1_c3[i].m_Rect.intersects(m_plane.m_Rect)) {
                m_plane.getHit();
                if(m_plane.hp <= 0) {endEvent(); break;}
                boss1.bullets1_c3[i].free = true;
            }

            if(!boss1.bullets1_c4[i].free && boss1.bullets1_c4[i].m_Rect.intersects(m_plane.m_Rect)) {
                m_plane.getHit();
                if(m_plane.hp <= 0) {endEvent(); break;}
                boss1.bullets1_c4[i].free = true;
            }
        }

        // bullet2 hit player detection

        for(int i=0; i<BOSS_BULLET2_NUMBER; i++) {
            if(!boss1.bullets2[i].free && boss1.bullets2[i].m_Rect.intersects(m_plane.m_Rect)) {
                m_plane.getHit();
                if(m_plane.hp <= 0) {endEvent(); break;}
                boss1.bullets2[i].free = true;
            }
        }

        // mine hit player detection

        for(int i=0; i<BOSS1_MINE_NUMBER; i++) {
            if(!boss1.mines[i].free && boss1.mines[i].m_Rect.intersects(m_plane.m_Rect)) {
                m_plane.getHit();
                if(m_plane.hp <= 0) {endEvent(); break;}
                boss1.mines[i].free = true; boss1.mines[i].explode();
            }
        }
    }


    // enemy detection

    for(int i=0; i<ENEMY_NUMBER; i++) {
        if(enemies[i].free) continue;

        // enemy hit detection

        for(int j=0; j<PLAYER_BULLET_NUMBER; j++) {
            if(m_plane.bullets[j].free) continue;

            if(enemies[i].m_Rect.intersects(m_plane.bullets[j].m_Rect)) {
                bulletSound->play();
                enemies[i].hp--;
                if(enemies[i].hp <= 0) {
                    kill(&enemies[i]);
                }
                m_plane.bullets[j].free = true;

            }
        }

        // plane collision detection;
        if(enemies[i].m_Rect.intersects(m_plane.m_Rect)) {

            m_plane.getHit();

            kill(&enemies[i]);

            if(m_plane.hp <= 0) endEvent();
        }

        // enemy bullet collision detection
        for(int j=0; j<ENEMY_BULLET_NUMBER; j++) {

            if(!enemies[i].bullets[j].free && enemies[i].bullets[j].m_Rect.intersects(m_plane.m_Rect)) {
                m_plane.getHit();
                if(m_plane.hp <= 0) {endEvent(); break;}
                enemies[i].bullets[j].free = true;
            }

            if(!enemies[i].bulletLeft[j].free && enemies[i].bulletLeft[j].m_Rect.intersects(m_plane.m_Rect)) {
                m_plane.getHit();
                if(m_plane.hp <= 0) {endEvent(); break;}
                enemies[i].bulletLeft[j].free = true;
            }

            if(!enemies[i].bulletRight[j].free && enemies[i].bulletRight[j].m_Rect.intersects(m_plane.m_Rect)) {
                m_plane.getHit();
                if(m_plane.hp <= 0) {endEvent(); break;}
                enemies[i].bulletRight[j].free = true;
            }

        }
    }
}

void Widget::endEvent() {
    timer.stop();
    setCursor(Qt::ArrowCursor);
    setMouseTracking(false);
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

void Widget::kill(BossPlane* boss) {
    m_plane.score += 100000;
    bombSound->play();
    winSound->play();
    if(bg2Sound->isPlaying()) bg2Sound->stop();
    if(!bgSound->isPlaying()) bgSound->play();
}


