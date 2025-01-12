
#ifndef PLAYER_H
#define PLAYER_H

#include "config.h"


void UpdatePlayer(char map[][COLUNS], PLAYER *player, ENEMIES enemy[MAXENEMY], int *countKeys, bool *exitGame, bool *showMenu, Sound gameOverSound, Sound rewardSound);

#endif // PLAYER
