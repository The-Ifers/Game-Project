#include "C:\raylib\raylib\src\raylib.h"
#include "resources/code/functions.c"

bool pause_game = false;
bool game_menu = true;

int main(void){
    srand(time(NULL));
    
    //Cenário (Tela):
    Playfield cenario;
    startPlayField(&cenario, 1280, 720, 1280, 100, 0, 620);
    
    //Player:
    Player player, player2;
    startPlayer(&player, 100, 50, (cenario.screenWidth/2-25), (cenario.chao.y - 50), 10, 5);

    startPlayer(&player2, 60, 65, 100, 555, 10, 5);

    //Inimigo (debug): 
    //Inimigo (debug):
    Inimigo inimigo;
    startEnemy(&inimigo, 50, 50, (rand()%(int)cenario.screenWidth), -55, (rand()%9)+1, (rand()%9)+1);

    InitWindow(cenario.screenWidth, cenario.screenHeight, "PlayField game test.");
    SetTargetFPS(60);

    Texture2D teste = LoadTexture("./resources/frames/morcego.png");
    float imgW = (teste.width/6), imgH = (teste.height/2);
    float timer = 0;
    int frameCounter;
    int maxFrames = (int)(teste.width/imgW)-1;
    //------------------------------------------------</> Inicniando o Game-Loop </>------------------------------------------------//
    while (!WindowShouldClose()){   

        // --- Tela Inicial ---
        if(game_menu){
            if(!initial_screen(cenario)) break;
            game_menu = !game_menu;
        }

        // --- Testa se o jogo está pausado ---
        if(IsKeyPressed(KEY_TAB)) pause_game = !pause_game;
        
        // --- Retornar tela inicial ---
        if(IsKeyPressed(KEY_X) && pause_game) game_menu = !game_menu;

        // Caso não esteja pausado, executa a rotina normal
        if(!pause_game){
            //(TESTE): rodando textura (frames):
            timer += GetFrameTime();

            if(timer>0.2){
                timer = 0.0;
                frameCounter += 1;
            }
            frameCounter = frameCounter % maxFrames;

            // --- Movimentação do player ---
            playerMoves(&player, cenario, KEY_W, KEY_S, KEY_A, KEY_D);
            playerMoves(&player2, cenario, KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT);

            // --- Movimentação do inimigo ---
            enemyMoves(&inimigo, player.hitbox.x+player.hitbox.width/2, player.hitbox.y+player.hitbox.height/2);
        }

        // Representação
        ClearBackground((Color){ 0, 0, 0,255});
        {

            // Player
            DrawRectangle(player.hitbox.x, player.hitbox.y, player.hitbox.width, player.hitbox.height, (Color){255, 150, 150, 255});
            DrawRectangle(player2.hitbox.x, player2.hitbox.y, player2.hitbox.width, player2.hitbox.height, (Color){150, 150, 255, 255});
            
            // Inimigo (debug)
            DrawRectangle(inimigo.hitbox.x, inimigo.hitbox.y, inimigo.hitbox.width, inimigo.hitbox.height, inimigo.cor);
            DrawTextureRec(teste,(Rectangle){imgW*frameCounter, imgH*0, imgW, imgH}, (Vector2){inimigo.hitbox.x, inimigo.hitbox.y}, WHITE);
            
            // Chão
            DrawRectangle(cenario.chao.x, cenario.chao.y, cenario.chao.width, cenario.chao.height, (Color){255, 255, 255, 255});
            
            // Pause Screen
            DrawText("Press TAB to pause", 10, 700, 15, BLACK);
            if(pause_game){
                DrawText("THE GAME IS PAUSED!", cenario.screenWidth/2-190, 660, 30, GREEN);
                DrawText("X -> Go to menu", cenario.screenWidth/2+190, 660, 15, GREEN);
                DrawText("ESC -> Close Game", cenario.screenWidth/2+190, 690, 15, GREEN);
            }

            // Debug:
            DrawText(TextFormat("Jump Timer: %.1f\nAirTime: %1.f\n\nPlayer (x|y): (X = %.1f) (Y = %.1f)\n", player.jumpTimer, player.airTime, player.hitbox.x, player.hitbox.y), 5, 10, 15, WHITE);
        }
        EndDrawing();
    }

    // Fechando a tela.
    CloseWindow();
    return 0;
}