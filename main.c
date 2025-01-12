#include "config.h"

int main()
{

    char map[LINES][COLUNS];
    PLAYER player;
    ENEMIES enemy[MAXENEMY];
    BOMBS bomb[MAXBOMB];

    int frames = 0;
    int bombs = 3;
    int countKey = 0;


    bool showMenu = false;
    bool exitGame = false;

    InitWindow(SCREENWIDTH, SCREENHEIGHT, "Mr. BOMBASTIC");
    InitAudioDevice();
    Sound gameOverSound = LoadSound("audios/GameOver.wav");
    Sound rewardSound = LoadSound("audios/Reward.wav");

    SetTargetFPS(FPS);

    // Inicializa o jogo na fase 1
    SetMap(1, map, &player, enemy, &countKey);

    while (!WindowShouldClose() && !exitGame)
    {

        BeginDrawing();
        frames++;

        // Alternar menu
        if (IsKeyPressed(KEY_TAB)) showMenu = !showMenu;

        if (showMenu)
        {
            if (IsKeyPressed(KEY_N))
            { // Novo Jogo
                SetMap(1, map, &player, enemy, &countKey); // Reinicia no nível 1
                showMenu = false;
            } else if (IsKeyPressed(KEY_C))
            { // Carregar Jogo
                LoadMap(map, &player, enemy, bomb, &frames, &bombs, &countKey);
                showMenu = false;
            } else if (IsKeyPressed(KEY_S))
            { // Salvar Jogo
                SaveMap(map, &player, enemy, bomb, &frames, &bombs, &countKey);
                showMenu = false;
            } else if (IsKeyPressed(KEY_Q))
            { // Sair do Jogo
                exitGame = true;
            } else if (IsKeyPressed(KEY_V))
            { // Voltar
                showMenu = false;
            }
        } else
        {
            // Atualiza o jogo
            UpdateMap(map, &player, enemy, bomb, &frames, &bombs, &countKey, &exitGame, &showMenu , gameOverSound , rewardSound );
        }

        // Desenho da tela
        DrawingMap(map, &player, bomb, &bombs, showMenu);
        EndDrawing();
    }

    CloseWindow();
    UnloadSound(gameOverSound);
    UnloadSound(rewardSound);
    CloseAudioDevice();

    return 0;
}
