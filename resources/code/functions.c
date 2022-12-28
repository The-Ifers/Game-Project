#include "structs.c"

void Gravity(Rectangle *hitbox, float g, float a){
    hitbox->y += g + (a*a)/2;
}