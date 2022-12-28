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
    player.speed = 5;
    player.hitbox.width = 50;
    player.hitbox.height = 100;
    player.hitbox.y = chao.y - player.hitbox.height - 50;
    player.hitbox.x = screenWidth/2 - player.hitbox.width/2;

    InitWindow(screenWidth, screenHeight, "Teste");
    SetTargetFPS(60);

    //------------------------------------------------</> Inicniando o Game-Loop </>------------------------------------------------//
    while (!WindowShouldClose())
    {
        // Atualização
        player.dirY = 0;
        player.dirX = 0;
        if(CheckCollisionRecs(player.hitbox, chao)){
            player.boost = 5;
        }
        

        // Movimentação
        if(IsKeyDown(KEY_A) && !CheckCollisionRecs(player.hitbox, Border1)){
            player.dirX = -1;
        }
        if(IsKeyDown(KEY_D) && !CheckCollisionRecs(player.hitbox, Border2)){
            player.dirX = 1;
        }

        //pulo
        if(IsKeyDown(KEY_W) && player.boost!=0){
            player.dirY = -1;
            player.boost--;
        }else if(!CheckCollisionRecs(player.hitbox, chao)){
            Gravity(&player.hitbox, player.speed*1.5);

        }
        
        if(IsKeyDown(KEY_S) && !CheckCollisionRecs(chao, player.hitbox)){
            player.dirY = 1;
        }
        

        player.hitbox.x += player.dirX * player.speed;
        player.hitbox.y += player.dirY*5 * player.speed;

          
        

        // Representação
        ClearBackground((Color){ 0, 0, 0,255});

            
                //Player
            DrawRectangle(player.hitbox.x, player.hitbox.y, player.hitbox.width, player.hitbox.height, (Color){150, 150, 150, 255});
            
                //Chão
            DrawRectangle(chao.x, chao.y, chao.width, chao.height, (Color){255, 255, 255, 255});

                //Bordas
            DrawRectangle(Border1.x, Border1.y,Border1.width, Border1.height, (Color){5, 232, 65, 255});
            DrawRectangle(Border2.x, Border2.y,Border2.width, Border2.height, (Color){5, 232, 65, 255});

            DrawText(TextFormat("Teste"), 10, 10, 20, WHITE);
            DrawText(TextFormat("%f", player.boost), screenWidth - 100, 10, 20, WHITE);

        EndDrawing();
    }

    // Fechando a tela.
    CloseWindow();
    return 0;
}