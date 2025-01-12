
#include "config.h"

void SetBombs( int *bombs , char map[][COLUNS] , PLAYER *player , BOMBS bomb[MAXBOMB] )
{
    if (IsKeyPressed(KEY_B) && player->y + 1 < COLUNS && map[player->x][player->y + 1] == ' ' && (*bombs) > 0) { // Confere se a bomba pode ser colocada
        for ( int i = 0 ; i < MAXBOMB ; i++ ) {
            if ( !bomb[i].actived ) {
                bomb[i].x = player->x ;
                bomb[i].y = player->y + 1 ;
                bomb[i].timer = 3 * FPS ;
                bomb[i].actived = true ;

                map[ bomb[i].x ][ bomb[i].y ] = 'S' ;
                (*bombs)-- ;
                break ;
            }
        }
    }
}

void DetonateBombs( BOMBS bomb[MAXBOMB], char map[][COLUNS], PLAYER *player, ENEMIES enemy[MAXENEMY], int *bombs )
{

    for (int i = 0; i < MAXBOMB; i++)
    {

        if (bomb[i].actived) // Confere se a bomba esta ativa
        {

            bomb[i].timer--; // Decrementa o timer da bomba

            if (bomb[i].timer <= 0) // Checa se o timer da bomba chega no 0
            {

                for (int j = -2; j <= 2; j++) // Logica da explosão
                {

                    if (bomb[i].x + j >= 0 && bomb[i].x + j < LINES && map[bomb[i].x + j][bomb[i].y] != 'W') // Destroi os blocos na horizontal
                    {
                        HandleExplosion(map, player, enemy, bomb[i].x + j, bomb[i].y);
                    }

                    if (bomb[i].y + j >= 0 && bomb[i].y + j < COLUNS && map[bomb[i].x][bomb[i].y + j] != 'W') // Destroi os blocos na vertical
                    {
                        HandleExplosion(map, player, enemy, bomb[i].x, bomb[i].y + j);
                    }

                }

                bomb[i].actived = false;
                map[bomb[i].x][bomb[i].y] = ' ' ;
                ( *bombs )++ ;
                if ( *bombs > MAXBOMB ) *bombs = MAXBOMB ;
            }
        }
    }
}

void HandleExplosion( char map[][COLUNS] , PLAYER *player , ENEMIES enemy[MAXENEMY] , int x , int y )
{

    Sound blockDestroySound = LoadSound("audios/Explosion.wav");

    if (map[x][y] == 'K' || map[x][y] == 'B' || map[x][y] == 'D') {
        player->score += 10;
        PlaySound(blockDestroySound);
    }

    for (int k = 0; k < MAXENEMY; k++) { // Inimigos no raio da explosão
        if (enemy[k].actived && enemy[k].x == x && enemy[k].y == y) {
            enemy[k].actived = false;
            player->score += 20;
            PlaySound(blockDestroySound);
        }
    }

    if (player->x == x && player->y == y) { // Jogador no raio da explosão
        player->lives--;
        player->x = player->xOriginal;
        player->y = player->yOriginal;
        player->score -= 100;
        if (player->score < 0) player->score = 0;
    }

    if (map[x][y] == 'K') { // Bau com chave no raio da explosão
        map[x][y] = 'H';
    } else {
        map[x][y] = ' ';
    }

}
