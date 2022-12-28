#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include "C:\raylib\raylib\src\raylib.h"

typedef struct Movimentation{
    int dirY;
    int dirX;
    float Yspeed;
    float Xspeed;
    float boost;
    float airTime;
}Movimentation;

typedef struct Player{
    Rectangle hitbox;
    Movimentation moves;
}Player;


