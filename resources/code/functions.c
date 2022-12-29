#include "structs.c"

Inimigo startEnemy(int Y, int X){
    Inimigo newEnemy;
    int posX;
    int posY;
    newEnemy.moves.Yspeed = 1+(rand()%10);
    newEnemy.moves.Xspeed = 1+(rand()%10);
    newEnemy.moves.boost = 0;
    newEnemy.moves.airTime = 0;
    
    newEnemy.hitbox.width = 50;
    newEnemy.hitbox.height = 50;
    
    posX = -(rand()%10);
    if(posX%2==0){
        newEnemy.hitbox.x=-60;
    }else{
        newEnemy.hitbox.x = X+60;
    }

    posY = -(rand()% (Y - 200));
    newEnemy.hitbox.y = (float)posY;

    newEnemy.cor = (Color){(rand()%255),(rand()%255),(rand()%255), 255};

    return newEnemy;
}

void Gravity(Rectangle *hitbox, float g, float a){
    hitbox->y += g + (a*a)/2;
}

void playerMoves(Player *player, Playfield cenario){
    // Atualização de valores:
    player->moves.dirY = 0;
    player->moves.dirX = 0;

    if(CheckCollisionRecs(player->hitbox, cenario.chao)){
        player->moves.boost = 10;
        player->moves.airTime = 0;
    }
    
    // Movimentação (controles):
    // Lados (A e D):
    if(IsKeyDown(KEY_A) && !CheckCollisionRecs(player->hitbox, cenario.Border1)){
        player->moves.dirX = -1;
    }
    if(IsKeyDown(KEY_D) && !CheckCollisionRecs(player->hitbox, cenario.Border2)){
        player->moves.dirX = 1;
    }
    player->hitbox.x += player->moves.dirX * player->moves.Xspeed;

    // Cima/Baixo (W e S):
    if(IsKeyDown(KEY_S) && !CheckCollisionRecs(cenario.chao, player->hitbox)){
        player->moves.dirY = 1;
    }

    if((IsKeyDown(KEY_W) || IsKeyDown(KEY_SPACE)) && player->moves.boost!=0){
        player->moves.dirY = -1;
        player->moves.boost --;
        player->moves.airTime  = 0;

    }else if(player->moves.boost!=10 && IsKeyUp(KEY_W)){
        player->moves.boost = 0;
    }

    // Gravidade: (com aceleração ainda XD)
    if(!CheckCollisionRecs(player->hitbox, cenario.chao)){
        player->moves.airTime++;
        Gravity(&player->hitbox, player->moves.Yspeed, player->moves.airTime);
    }else{
        player->moves.airTime = 0;
        player->hitbox.y = cenario.chao.y - player->hitbox.height+1;
    }
    player->hitbox.y += player->moves.dirY * player->moves.Yspeed*5;
}


Inimigo enemyMoves(Inimigo seeker, float posX, float posY){
    seeker.moves.dirX = 0;
    seeker.moves.dirY = 0;

    // X moves
    if(seeker.hitbox.x+seeker.hitbox.width/2>posX+10){
        seeker.moves.dirX = -1;
    }else if(seeker.hitbox.x+seeker.hitbox.width/2<posX-10){
        seeker.moves.dirX = 1;
    }
    seeker.hitbox.x += seeker.moves.dirX * seeker.moves.Xspeed;

    
    // Y moves
    if(seeker.hitbox.y+seeker.hitbox.height/2>posY+10){
        seeker.moves.dirY = -1;
    }else if(seeker.hitbox.y+seeker.hitbox.height/2<posY-10){
        seeker.moves.dirY = 1;
    }
    seeker.hitbox.y += seeker.moves.dirY * seeker.moves.Yspeed;

    return seeker;
}