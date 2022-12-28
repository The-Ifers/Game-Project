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
    player.Yspeed = 5;
    player.Xspeed = 10;
    player.boost = 0;
    player.airTime = 0;
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
        // Atualização
        player.dirY = 0;
        player.dirX = 0;

        if(CheckCollisionRecs(player.hitbox, chao)){
            player.boost = initBoost;
            player.airTime = 0;
        }
        
        

        // Movimentação (controles):

        // Lados (A e D)
        if(IsKeyDown(KEY_A) && !CheckCollisionRecs(player.hitbox, Border1)){
            player.dirX = -1;
        }
        if(IsKeyDown(KEY_D) && !CheckCollisionRecs(player.hitbox, Border2)){
            player.dirX = 1;
        }

        // Cima/Baixo (W e S)
        if(IsKeyDown(KEY_S) && !CheckCollisionRecs(chao, player.hitbox)){
            player.dirY = 1;
        }

        if(IsKeyDown(KEY_W) && player.boost!=0){
            player.dirY = -1;
            player.boost --;
            player.airTime  = 0;

        }else if(player.boost!=initBoost && IsKeyUp(KEY_W)){
            player.boost = 0;
        }

            // Gravidade: (com aceleração ainda XD)
        if(!CheckCollisionRecs(player.hitbox, chao)){
            player.airTime++;
            Gravity(&player.hitbox, player.Yspeed, player.airTime);
        }else{
            player.airTime = 0;
            player.hitbox.y = chao.y - player.hitbox.height+1;
        }

       
        player.hitbox.x += player.dirX * player.Xspeed;
        player.hitbox.y += player.dirY * player.Yspeed*5;

          
        

        // Representação
        ClearBackground((Color){ 0, 0, 0,255});

            
            //Player
            DrawRectangle(player.hitbox.x, player.hitbox.y, player.hitbox.width, player.hitbox.height, (Color){150, 150, 150, 255});
            
            //Chão
            DrawRectangle(chao.x, chao.y, chao.width, chao.height, (Color){255, 255, 255, 255});

            //Bordas:
            DrawRectangle(Border1.x, Border1.y,Border1.width, Border1.height, (Color){5, 232, 65, 255});
            DrawRectangle(Border2.x, Border2.y,Border2.width, Border2.height, (Color){5, 232, 65, 255});


            // Debug:
            DrawText(TextFormat("Teste"), 10, 10, 20, WHITE);
            DrawText(TextFormat("Boost: %.1f\nAirTime: %1.f", player.boost, player.airTime), screenWidth - 120, 10, 20, WHITE);
        EndDrawing();
    }

    // Fechando a tela.
    CloseWindow();
    return 0;
}