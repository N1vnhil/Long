#ifndef CONFIG_H
#define CONFIG_H

#define GAME_WIDTH 400
#define GAME_HEIGHT 800
#define GAME_TITLE  "LONG"
#define RES_PATH "D:/projects/qt_demo/PlaneWar/plane.rcc"
#define GAME_ICON ":/res/photo_32x32.ico"
#define GAME_MAP ":/res/map.png"
#define MAP_SCROLL_SPEED 2
#define GAME_RATE 10
#define PLANE_PATH ":/res/nailong.png"

#define PLAYER_BULLET_PATH ":/res/bullet.png"
#define PLAYER_BULLET_SPEED 5
#define PLAYER_BULLET_NUMBER 20
#define PLAYER_BULLET_INTERVAL 20

#define PLAYER_EXPLOSION_PATH ":/res/pe%1.png"
#define PLAYER_EXPLOSION_MAX 7
#define PLAYER_EXPLOSION_INTERVAL 15

#define ENEMY_BULLET_PATH ":/res/eb1.png"
#define ENEMY_BULLET_SPEED 3
#define ENEMY_BULLET_NUMBER 20
#define ENEMY_BULLET_INTERVAL 200

#define ENEMY_PATH ":/res/enemy.png"
#define ENEMY_SPEED 1
#define ENEMY_NUMBER 100
#define ENEMY_INTERVAL 100
#define ENEMY_HP 5

#define BOMB_PATH ":/res/b%1.png"
#define BOMB_MAX 6
#define BOMB_NUMBER 20
#define BOMB_INTERVAL 15

#define SOUND_BOMB ":/res/explosion.wav"
#define SOUND_BG1 ":/res/bg1.wav"
#define SOUND_BG2 ":/res/bg2.wav"
#define SOUND_WIN ":/res/win.wav"
#define SOUND_HIT ":/res/hit.wav"
#define SOUND_BULLET ":/res/playerBullet.wav"

#define PLAYER_HP 10


#define HEART_PATH ":/res/heart.png"

#define HIT_INTERVAL 5

#define BOSS1_PATH ":/res/boss1.png"
#define BOSS1_HP 500

#define BOSS_COLLIDE_INTERVAL 50

#define BOSS_BULLET1_PATH ":/res/bb1.png"
#define BOSS_BULLET1_SPEED 5
#define BOSS_BULLET1_NUMBER 20
#define BOSS_BULLET1_INTERVAL 100

#define BOSS_BULLET2_PATH ":/res/bb2.png"
#define BOSS_BULLET2_SPEED 10
#define BOSS_BULLET2_NUMBER 50
#define BOSS_BULLET2_INTERVAL 40

#define BOSS1_TIME 30000

#define BOSS1_MINE_PATH ":/res/bm%1.png"
#define BOSS1_MINE_INTERVAL 100
#define BOSS1_MINE_NUMBER 50
#define BOSS1_MINE_TIME 250

#define BOSS_MINE_EXPLOSION_MAX 7
#define BOSS_MINE_EXPLOSION_NUMBER 20
#define BOSS_MINE_EXPLOSION_INTERVAL 15

#endif // CONFIG_H
