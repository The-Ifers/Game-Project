#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include "C:\raylib\raylib\src\raylib.h"

typedef struct Playfield{
    float screenWidth;
    float screenHeight;
    Rectangle chao;
    Rectangle Border1;
    Rectangle Border2;
}Playfield;

typedef struct Movimentation{
    int dirY;
    int dirX;
    float Yspeed;
    float Xspeed;
}Movimentation;

typedef struct Player{
    Rectangle hitbox;
    Movimentation moves;
    float jumpTimer;
    float airTime;
}Player;


typedef struct Inimigo{
    Rectangle hitbox;
    Movimentation moves;

    Color cor; // só para debug.
}Inimigo;
