
#include "config.h"



void SetMap( int level , char map[][COLUNS], PLAYER *player, ENEMIES enemy[MAXENEMY], int *countKey)
{
    char filename[50];
    snprintf(filename, sizeof(filename), "maps/mapa%d.txt", level);

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Erro ao carregar o mapa");
        exit(1);
    }

    *countKey = 0;
    int enemyIndex = 0;
    for (int i = 0; i < LINES; i++) {
        for (int j = 0; j < COLUNS; j++) {
            fscanf(file, "%c", &map[i][j]); // Pega o mapa

            // Configuração do jogador
            if (map[i][j] == 'J') {
                player->x = i;
                player->y = j;
                player->xOriginal = i;
                player->yOriginal = j;
            }

            // Configuração de inimigos
            if (map[i][j] == 'E' && enemyIndex < MAXENEMY) {
                enemy[enemyIndex].x = i;
                enemy[enemyIndex].y = j;
                enemy[enemyIndex].actived = true;
                enemyIndex++;
            }

            // Contagem de chaves
            if (map[i][j] == 'K') {
                (*countKey)++;
            }
        }
        fgetc(file);
    }

    fclose(file);

    // Configurações iniciais do jogador
    player->lives = 3;
    player->keys = 0;
    player->score = 0;
    player->currentLevel = level; // Define o nível atual
}


void UpdateMap( char map[ ][ COLUNS ] , PLAYER *player , ENEMIES enemy[ MAXENEMY ] , BOMBS bomb[ MAXBOMB ] , int *frames , int *bombs , int *countKey, bool *exitGame, bool *showMenu , Sound gameOverSound , Sound rewardSound )
{

    // ======================= JOGADOR ========================

    UpdatePlayer(map, player, enemy, countKey, &exitGame, &showMenu, gameOverSound, rewardSound);



    // ====================== BOMBAS ======================

    //CONFIGURAR BOMBAS
    SetBombs(bombs, map, player, bomb);


    //DETONAR BOMBAS
    DetonateBombs(bomb, map, player, enemy, bombs);


    // ======================== INIMIGOS ========================

    UpdateEnemies(map, player, enemy, frames);


}


void DrawingMap(  char map[ ][ COLUNS ] , PLAYER *player , BOMBS bomb[ MAXBOMB ] , int *bombs , bool showMenu )
{

    char txt[ MAXCHAR ] ;
    char menu[ MAXCHAR ] ;

    for( int i = 0 ; i < LINES ; i++ )
    {
        for( int j = 0 ; j < COLUNS ; j++ )
        {

            Rectangle tile = { j * LIT_SIZE, i * LIT_SIZE , LIT_SIZE , LIT_SIZE };

            switch( map[i][j] )
            {

                case ' ': DrawRectangleRec( tile , LIGHTGRAY ) ; break ; // VAZIO
                case 'J': DrawRectangleRec( tile , BLUE ) ; break ; // JOGADOR
                case 'W': DrawRectangleRec( tile , DARKGRAY ) ; break ; // PAREDE INDESTRUTIVEL
                case 'D': DrawRectangleRec( tile , ORANGE ) ; break ; // PAREDE DESTRUTIVEL
                case 'K': // BAU COM CHAVE
                case 'B': DrawRectangleRec( tile , BROWN ) ; break ; // BAU SEM CHAVE
                case 'E': DrawRectangleRec( tile , RED ) ; break ; // INIMIGO
                case 'S': DrawRectangleRec( tile, GREEN ) ; break ; // BOMBA
                case 'H': DrawRectangleRec( tile, PURPLE ) ; break ; // CHAVE
                case 'G': DrawRectangleRec( tile, GOLD ) ; break ; // PORTÃO
                default: DrawRectangleRec( tile , WHITE ) ; break ;

            }
        }
    }



    //INFORMAÇÕES

    if( showMenu )
    { // MENU

        snprintf( menu , sizeof( menu ) , "(N) New Game  |  (C) Load Game  |  (S) Save Game  |  (Q) Quit Game  |  (V) Back"  ) ;

        int mapHeight = LINES * LIT_SIZE;

        int textHeight = 30;
        Rectangle textArea = {0, mapHeight + 40, SCREENWIDTH, textHeight};
        DrawRectangleRec(textArea, BLACK);

        DrawText(
            menu,
            (SCREENWIDTH - MeasureText(menu, 20)) / 2,
            mapHeight + 40,
            20,
            RAYWHITE
        );

    }else
    { // INTERFACE

        snprintf( txt , sizeof( txt ) , "LIVES: %d\t\tBOMBS: %d\t\tSCORE: %d\t\tKEYS: %d" , player->lives , *bombs , player->score , player->keys ) ;

        int mapHeight = LINES * LIT_SIZE;

        int textHeight = 30;
        Rectangle textArea = {0, mapHeight + 40, SCREENWIDTH, textHeight};
        DrawRectangleRec(textArea, BLACK);

        DrawText(
            txt,
            (SCREENWIDTH - MeasureText(txt, 20)) / 2,
            mapHeight + 40,
            20,
            RAYWHITE
        );

    }


}


void SaveMap(char map[][COLUNS], PLAYER *player, ENEMIES enemy[MAXENEMY], BOMBS bomb[MAXBOMB], int *frames, int *bombs, int *countKey)
{

    FILE *file = fopen("saves/save.bin", "wb");
    if (file == NULL) {
        exit(1);
    }

    fwrite(map, sizeof(char), LINES * COLUNS, file);
    fwrite(player, sizeof(PLAYER), 1, file);
    fwrite(enemy, sizeof(ENEMIES), MAXENEMY, file);
    fwrite(bomb, sizeof(BOMBS), MAXBOMB, file);
    fwrite(frames, sizeof(int), 1, file);
    fwrite(bombs, sizeof(int), 1, file);
    fwrite(countKey, sizeof(int), 1, file);

    fclose(file);
}


void LoadMap(char map[][COLUNS], PLAYER *player, ENEMIES enemy[MAXENEMY], BOMBS bomb[MAXBOMB], int *frames, int *bombs, int *countKey)
{
    FILE *file = fopen("saves/save.bin", "rb");
    if (file == NULL) {
        exit(1);
    }

    fread(map, sizeof(char), LINES * COLUNS, file);
    fread(player, sizeof(PLAYER), 1, file);
    fread(enemy, sizeof(ENEMIES), MAXENEMY, file);
    fread(bomb, sizeof(BOMBS), MAXBOMB, file);
    fread(frames, sizeof(int), 1, file);
    fread(bombs, sizeof(int), 1, file);
    fread(countKey, sizeof(int), 1, file);

    fclose(file);

    // Recarrega o mapa com base no nível salvo
    SetMap(player->currentLevel, map, player, enemy, countKey);

    // Atualiza o mapa com as bombas carregadas
    for (int i = 0; i < MAXBOMB; i++) {
        if (bomb[i].actived) { // Verifica se a bomba está ativa
            map[bomb[i].x][bomb[i].y] = 'S'; // Adiciona a bomba ao mapa (use o caractere correto)
        }
    }
}
