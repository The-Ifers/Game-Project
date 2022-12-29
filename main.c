#include "C:\raylib\raylib\src\raylib.h"
#include "resources/code/functions.c"


int main(void){
    srand(time(NULL));
    //Cenário (Tela):
    Playfield cenario;
    cenario.screenWidth = 1280;
    cenario.screenHeight = 720;

    //Chão
    cenario.chao.width = cenario.screenWidth;
    cenario.chao.height = 100;
    cenario.chao.y = cenario.screenHeight - cenario.chao.height;
    cenario.chao.x = 0;

    //Bordas
    cenario.Border1.width = 1;
    cenario.Border1.height = cenario.screenHeight;
    cenario.Border1.y = 0;
    
    cenario.Border2 = cenario.Border1;
    cenario.Border1.x = 0;
    cenario.Border2.x = cenario.screenWidth - cenario.Border2.width;

    //Player:
    Player player;
    player.moves.Yspeed = 5;
    player.moves.Xspeed = 15;
    player.moves.boost = 0;
    player.moves.airTime = 0;

    player.hitbox.width = 50;
    player.hitbox.height = 100;
    player.hitbox.y = cenario.chao.y - player.hitbox.height - 50;
    player.hitbox.x = cenario.screenWidth/2 - player.hitbox.width/2;

    //Inimigo (debug):
    Inimigo inimigo[10];
    for(int I=0; I<10; I++){
        inimigo[I] = startEnemy((int)cenario.screenHeight, (int)cenario.screenWidth);
    }


    InitWindow(cenario.screenWidth, cenario.screenHeight, "Teste");
    SetTargetFPS(60);

    //------------------------------------------------</> Inicniando o Game-Loop </>------------------------------------------------//
    while (!WindowShouldClose()){   

        // --- Movimentação do player ---
        playerMoves(&player, cenario);


        // --- Movimentação do inimigo ---
        for(int I=0; I<10; I++){
            inimigo[I] = enemyMoves(inimigo[I], player.hitbox.x+player.hitbox.width/2, player.hitbox.y+player.hitbox.height/2);
        }
        


        // Representação
        ClearBackground((Color){ 0, 0, 0,255});

            // Player
            DrawRectangle(player.hitbox.x, player.hitbox.y, player.hitbox.width, player.hitbox.height, (Color){150, 150, 150, 255});
            /* DrawCircle(player.hitbox.x, player.hitbox.y, 50, WHITE); */
            // Inimigo (teste)
            for(int I=0; I<10; I++){
                DrawRectangle(inimigo[I].hitbox.x, inimigo[I].hitbox.y, inimigo[I].hitbox.width, inimigo[I].hitbox.height, inimigo[I].cor);
            }
            
            // Chão
            DrawRectangle(cenario.chao.x, cenario.chao.y, cenario.chao.width, cenario.chao.height, (Color){255, 255, 255, 255});
            
            // Bordas:
            DrawRectangle(cenario.Border1.x, cenario.Border1.y, cenario.Border1.width, cenario.Border1.height, (Color){ 0, 0, 0,0});
            DrawRectangle(cenario.Border2.x, cenario.Border2.y, cenario.Border2.width, cenario.Border2.height, (Color){ 0, 0, 0,0});

            // Debug:
            DrawText(TextFormat("Teste"), 10, 10, 20, WHITE);
            DrawText(TextFormat("Boost: %.1f\nAirTime: %1.f\n\nPlayer (x|y): (X = %.1f) (Y = %.1f)\n", player.moves.boost, player.moves.airTime, player.hitbox.x, player.hitbox.y), 10, 30, 10, WHITE);
        EndDrawing();
    }

    // Fechando a tela.
    CloseWindow();
    return 0;
}