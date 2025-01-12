
#ifndef MAP_H
#define MAP_H

#include "config.h"


typedef struct
{

    int x;
    int y;
    bool actived;

} ENEMIES;


typedef struct
{

    int x;
    int y;
    int timer;
    bool actived;

} BOMBS;

typedef struct
{

    int x;
    int y;
    int xOriginal;
    int yOriginal;
    int score;
    int lives;
    int keys;
    BOMBS bombs;
    int currentLevel;

} PLAYER;



void SetMap(int level, char map[LINES][COLUNS], PLAYER *player, ENEMIES *enemy, int *countKeys);
void UpdateMap( char map[ ][ COLUNS ] , PLAYER *player , ENEMIES enemy[ MAXENEMY ] , BOMBS bomb[ MAXBOMB ] , int *frames , int *bombs , int *countKey, bool *exitGame, bool *showMenu , Sound gameOverSound , Sound rewardSound );
void DrawingMap( char map[ ][ COLUNS ] , PLAYER *player ,  BOMBS bomb[ MAXBOMB ] , int *bombs , bool showMenu  ) ;

void SaveMap ( char map[ ][ COLUNS ] , PLAYER *player , ENEMIES enemy[ MAXENEMY ] , BOMBS bomb[ MAXBOMB ] , int *frames , int *bombs , int *countKey ) ;
void LoadMap ( char map[ ][ COLUNS ] , PLAYER *player , ENEMIES enemy[ MAXENEMY ] , BOMBS bomb[ MAXBOMB ] , int *frames , int *bombs , int *countKey ) ;



#endif // MAP
