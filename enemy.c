
#include "config.h"


void MoveEnemy(char map[LINES][COLUNS], ENEMIES *enemy) // Logica da movimentação dos inimigos
{
    int new_line_enemy = enemy->x;
    int new_cols_enemy = enemy->y;

    int randNumber = GetRandomValue(1, 4); // Logica para movimentação randomica

    if (randNumber == 1 && map[enemy->x - 1][enemy->y] == ' ') { // Move para cima
        new_line_enemy--;
    } else if (randNumber == 2 && map[enemy->x + 1][enemy->y] == ' ') { // Move para baixo
        new_line_enemy++;
    } else if (randNumber == 3 && map[enemy->x][enemy->y - 1] == ' ') { // Move para esquerda
        new_cols_enemy--;
    } else if (randNumber == 4 && map[enemy->x][enemy->y + 1] == ' ') { // Move para direita
        new_cols_enemy++;
    }


    if (new_line_enemy != enemy->x || new_cols_enemy != enemy->y) {
        map[enemy->x][enemy->y] = ' ';
        enemy->x = new_line_enemy;
        enemy->y = new_cols_enemy;
        map[enemy->x][enemy->y] = 'E';
    }
}


void CheckCollisionWithPlayer(char map[LINES][COLUNS], PLAYER *player, ENEMIES *enemy) // Confere a colisão do jogador com inimigos
{

    if (( enemy->x == player->x - 1 && enemy->y == player->y ) || // Cima
        ( enemy->x == player->x + 1 && enemy->y == player->y ) || // Baixo
        ( enemy->x == player->x && enemy->y - 1 == player->y ) || // Esquerda
        ( enemy->x == player->x && enemy->y + 1 == player->y ) ) { // Direita

        map[player->x][player->y] = ' ';
        player->lives--;
        player->x = player->xOriginal;
        player->y = player->yOriginal;

    }

}


void UpdateEnemies(char map[LINES][COLUNS], PLAYER *player, ENEMIES enemy[MAXENEMY], int *frames)
{
    if (((*frames) * 2) % FPS == 0) // Logica para um delay da movimentação
        {
        for (int k = 0; k < MAXENEMY; k++)
        {
            if (!enemy[k].actived) continue; // Confere se o inimigo esta desativado

            MoveEnemy(map, &enemy[k]);
            CheckCollisionWithPlayer(map, player, &enemy[k]);
        }

        *frames = 0;
    }
}
