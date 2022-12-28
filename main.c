#include "C:\raylib\raylib\src\raylib.h"
#include "resources/code/functions.c"


int main(void){
    float screenWidth = 1280, screenHeight = 720;
 
    InitWindow(screenWidth, screenHeight, "Teste");
    //------------------------------------------------</> Inicniando o Game-Loop </>------------------------------------------------//
    while (!WindowShouldClose())
    {
        // Atualização
        

        // Movimentação
        

        // Representação
        ClearBackground((Color){ 0, 0, 0,255});
        
        DrawText(TextFormat("Teste"), 10, 10, 20, WHITE);

        EndDrawing();
    }

    // Fechando a tela.
    CloseWindow();
    return 0;
}