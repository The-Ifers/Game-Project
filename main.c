#include "C:\raylib\raylib\src\raylib.h"
#include "resources/code/functions.c"


int main(void){
    srand(time(NULL));
    
    //Cenário (Tela):
    Playfield cenario;
    startPlayField(&cenario, 1280, 720, 1280, 100, 0, 620);
    
    //Player:
    Player player;
    startPlayer(&player, 100, 50, (cenario.screenWidth/2-25), (cenario.chao.y - 50), 10, 5);

    //Inimigo (debug):
    Inimigo inimigo[10];
    for(int I=0; I<10; I++){
        startEnemy(&inimigo[I], 50, 50, (rand()%(int)cenario.screenWidth), -55, (rand()%9)+1, (rand()%9)+1);
    }

    InitWindow(cenario.screenWidth, cenario.screenHeight, "PlayField game test.");
    SetTargetFPS(60);

    //------------------------------------------------</> Inicniando o Game-Loop </>------------------------------------------------//
    while (!WindowShouldClose()){   

        // --- Movimentação do player ---
        playerMoves(&player, cenario);


        // --- Movimentação do inimigo ---
        for(int I=0; I<10; I++){
            enemyMoves(&inimigo[I], player.hitbox.x+player.hitbox.width/2, player.hitbox.y+player.hitbox.height/2);
        }

        // Representação
        ClearBackground((Color){ 0, 0, 0,255});

            // Player
            DrawRectangle(player.hitbox.x, player.hitbox.y, player.hitbox.width, player.hitbox.height, (Color){150, 150, 150, 255});
            
            // Inimigo (debug)
            for(int I=0; I<10; I++){
                DrawRectangle(inimigo[I].hitbox.x, inimigo[I].hitbox.y, inimigo[I].hitbox.width, inimigo[I].hitbox.height, inimigo[I].cor);
            }
            
            // Chão
            DrawRectangle(cenario.chao.x, cenario.chao.y, cenario.chao.width, cenario.chao.height, (Color){255, 255, 255, 255});
            
            // Debug:
            DrawText(TextFormat("Jump Timer: %.1f\nAirTime: %1.f\n\nPlayer (x|y): (X = %.1f) (Y = %.1f)\n", player.jumpTimer, player.airTime, player.hitbox.x, player.hitbox.y), 5, 10, 15, WHITE);
        EndDrawing();
    }

    // Fechando a tela.
    CloseWindow();
    return 0;
}