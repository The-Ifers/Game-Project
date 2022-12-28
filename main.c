#include "C:\raylib\raylib\src\raylib.h"
#include "resources/code/functions.c"


int main(void){
    float screenWidth = 1280, screenHeight = 720;

    //Chão
    Rectangle chao;
    chao.width = screenWidth;
    chao.height = 100;
    chao.y = screenHeight - chao.height;
    chao.x = 0;

    //Bordas
    Rectangle Border1;
    Border1.width = 1;
    Border1.height = screenHeight;
    Border1.y = 0;
    
    Rectangle Border2 = Border1;
    Border1.x = 0;
    Border2.x = screenWidth - Border2.width;

    //Player
    Player player;
    player.moves.Yspeed = 5;
    player.moves.Xspeed = 10;
    player.moves.boost = 0;
    player.moves.airTime = 0;

    player.hitbox.width = 50;
    player.hitbox.height = 100;
    player.hitbox.y = chao.y - player.hitbox.height - 50;
    player.hitbox.x = screenWidth/2 - player.hitbox.width/2;


    //TestVars:
    float initBoost = 10;

    InitWindow(screenWidth, screenHeight, "Teste");
    SetTargetFPS(60);

    //------------------------------------------------</> Inicniando o Game-Loop </>------------------------------------------------//
    while (!WindowShouldClose())
    {
        // Atualização de valores:
        player.moves.dirY = 0;
        player.moves.dirX = 0;

        if(CheckCollisionRecs(player.hitbox, chao)){
            player.moves.boost = initBoost;
            player.moves.airTime = 0;
        }
        
        // Movimentação (controles):
        // Lados (A e D):
        if(IsKeyDown(KEY_A) && !CheckCollisionRecs(player.hitbox, Border1)){
            player.moves.dirX = -1;
        }
        if(IsKeyDown(KEY_D) && !CheckCollisionRecs(player.hitbox, Border2)){
            player.moves.dirX = 1;
        }

        // Cima/Baixo (W e S):
        if(IsKeyDown(KEY_S) && !CheckCollisionRecs(chao, player.hitbox)){
            player.moves.dirY = 1;
        }

        if(IsKeyDown(KEY_W) && player.moves.boost!=0){
            player.moves.dirY = -1;
            player.moves.boost --;
            player.moves.airTime  = 0;

        }else if(player.moves.boost!=initBoost && IsKeyUp(KEY_W)){
            player.moves.boost = 0;
        }

        // Gravidade: (com aceleração ainda XD)
        if(!CheckCollisionRecs(player.hitbox, chao)){
            player.moves.airTime++;
            Gravity(&player.hitbox, player.moves.Yspeed, player.moves.airTime);
        }else{
            player.moves.airTime = 0;
            player.hitbox.y = chao.y - player.hitbox.height+1;
        }

        player.hitbox.x += player.moves.dirX * player.moves.Xspeed;
        player.hitbox.y += player.moves.dirY * player.moves.Yspeed*5;

        // Representação
        ClearBackground((Color){ 0, 0, 0,255});

            //Player
            DrawRectangle(player.hitbox.x, player.hitbox.y, player.hitbox.width, player.hitbox.height, (Color){150, 150, 150, 255});
            
            //Chão
            DrawRectangle(chao.x, chao.y, chao.width, chao.height, (Color){255, 255, 255, 255});

            //Bordas:
            DrawRectangle(Border1.x, Border1.y,Border1.width, Border1.height, (Color){ 0, 0, 0,0});
            DrawRectangle(Border2.x, Border2.y,Border2.width, Border2.height, (Color){ 0, 0, 0,0});


            // Debug:
            DrawText(TextFormat("Teste"), 10, 10, 20, WHITE);
            DrawText(TextFormat("Boost: %.1f\nAirTime: %1.f", player.moves.boost, player.moves.airTime), screenWidth - 120, 10, 20, WHITE);
        EndDrawing();
    }

    // Fechando a tela.
    CloseWindow();
    return 0;
}