
#ifndef ENEMY_H
#define ENEMY_H

#include "config.h"


void MoveEnemy(char map[LINES][COLUNS], ENEMIES *enemy);
void CheckCollisionWithPlayer(char map[LINES][COLUNS], PLAYER *player, ENEMIES *enemy);
void UpdateEnemies(char map[LINES][COLUNS], PLAYER *player, ENEMIES enemy[MAXENEMY], int *frames);

#endif // ENEMY_H
