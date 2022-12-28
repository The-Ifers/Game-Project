#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include "C:\raylib\raylib\src\raylib.h"

typedef struct Player{

    Rectangle hitbox;
    int dirY;
    int dirX;
    float Yspeed;
    float Xspeed;
    float boost;
    float airTime;
}Player;


