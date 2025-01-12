
#include "config.h"


void UpdatePlayer(char map[][COLUNS], PLAYER *player, ENEMIES enemy[MAXENEMY], int *countKeys, bool *exitGame, bool *showMenu, Sound gameOverSound, Sound rewardSound) {
    int new_line = player->x;
    int new_cols = player->y;

    // Atualiza o movimento com IsKeyDown para movimento contínuo
    if (IsKeyPressed(KEY_W)) new_line--;
    else if (IsKeyPressed(KEY_S)) new_line++;
    else if (IsKeyPressed(KEY_A)) new_cols--;
    else if (IsKeyPressed(KEY_D)) new_cols++;

    // Confere se a nova posição é válida
    if (new_line >= 0 && new_line < LINES && new_cols >= 0 && new_cols < COLUNS) {
        if (map[new_line][new_cols] == ' ') { // Caminho livre
            map[player->x][player->y] = ' ';
            player->x = new_line;
            player->y = new_cols;
            map[player->x][player->y] = 'J';
        } else if (map[new_line][new_cols] == 'H') { // Pegou chave
            map[player->x][player->y] = ' ';
            player->x = new_line;
            player->y = new_cols;
            map[player->x][player->y] = 'J';
            player->keys++;
        }else if (map[new_line][new_cols] == 'G') { // Porta para o proximo nível
            player->currentLevel++;
            *countKeys = 0;
            SetMap(player->currentLevel, map, player, enemy, countKeys);
        }
    }

    if (player->keys == (*countKeys)) {
        map[player->xOriginal][player->yOriginal] = 'G'; // Abre o portão
    }

    // Fim de jogo se as vidas chegarem a zero
    if (player->lives <= 0) {
        PlaySound(gameOverSound);
        *exitGame = true;
    }
}
