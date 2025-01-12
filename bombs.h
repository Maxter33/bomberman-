
#ifndef BOMBS_H
#define BOMBS_H

#include "config.h"


void SetBombs(int *bombs, char map[][COLUNS], PLAYER *player, BOMBS bomb[MAXBOMB]);
void DetonateBombs(BOMBS bomb[MAXBOMB], char map[][COLUNS], PLAYER *player, ENEMIES enemy[MAXENEMY], int *bombs);
void HandleExplosion(char map[][COLUNS], PLAYER *player, ENEMIES enemy[MAXENEMY], int x, int y);


#endif // BOMBS_H
