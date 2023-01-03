#include "structs.c"


// Iniciando objetos (player, inimigo, armas, etc.):
// Player:
void startPlayer(Player *player, float height, float width, float posX, float posY, float speedX, float speedY){
    player->hitbox.height = height;
    player->hitbox.width = width;
    player->hitbox.x = posX;
    player->hitbox.y = posY;

    player->moves.dirX = 0;
    player->moves.dirY =0;
    player->moves.Xspeed = speedX;
    player->moves.Yspeed = speedY;

    player->jumpTimer = 0;
    player->airTime = 0;
}

// Inimigos:
void startEnemy(Inimigo *enemy, float height, float width, float posX, float posY, float speedX, float speedY){
    enemy->hitbox.height = height;
    enemy->hitbox.width = width;
    enemy->hitbox.x = posX;
    enemy->hitbox.y = posY;
    
    enemy->moves.Xspeed = speedX;
    enemy->moves.Yspeed = speedY;
    enemy->moves.dirX = 0;
    enemy->moves.dirY = 0;

    enemy->cor = (Color){(rand() % 255), (rand() % 255), (rand() % 255), 255};
}

// PlayField:
void startPlayField(Playfield *playfield, float Width, float Height, float floorWidth, float floorHeight, float floorX, float floorY){
    playfield->screenWidth = Width;
    playfield->screenHeight = Height;

    playfield->chao.width = floorWidth;
    playfield->chao.height = floorHeight;
    playfield->chao.x = floorX;
    playfield->chao.y = floorY;

    playfield->Border1.width = 1;
    playfield->Border1.height = Height;
    playfield->Border1.y = 0;

    playfield->Border2 = playfield->Border1;
    playfield->Border1.x = 0;
    playfield->Border2.x = Width-playfield->Border2.width;
}


// Movimentação (Player, Inimigo, etc);

void Gravity(Rectangle *hitbox, Rectangle collider, float gForce, float *acceleration){
    if(!CheckCollisionRecs(*hitbox, collider) && !(hitbox->y>collider.y+5)){
        *acceleration = *acceleration + 1;
        hitbox->y += gForce + (*acceleration**acceleration)/2;
    }else{
        acceleration = 0;
        hitbox->y = collider.y - hitbox->height+1;
    }
}

void playerMoves(Player *player, Playfield cenario, KeyboardKey up, KeyboardKey down, KeyboardKey left, KeyboardKey right){

    // Reset da direção do player:
    player->moves.dirY = 0;
    player->moves.dirX = 0;

    // Testando colisão para resetar o pulo:
    if(CheckCollisionRecs(player->hitbox, cenario.chao)) player->airTime = 0;

    // Decrementando o timer para o próximo pulo (caso ele seja maior que zero):
    if(player->jumpTimer>0) player->jumpTimer--;
    
    // Movimentação (controles):
    // Key A: (Esquerda):
    if(IsKeyDown(left) && !CheckCollisionRecs(player->hitbox, cenario.Border1)) player->moves.dirX = -1;
    
    // Key D: (Direita):
    if(IsKeyDown(right) && !CheckCollisionRecs(player->hitbox, cenario.Border2)) player->moves.dirX = 1;

    // Key S: (Baixo): (debug)
    if(IsKeyDown(down) && !CheckCollisionRecs(cenario.chao, player->hitbox)) player->moves.dirY = 1;

    // Key S: (Cima/Pulo): 
    if((IsKeyDown(up)  && player->jumpTimer==0) || player->airTime!=0){
        if(CheckCollisionRecs(player->hitbox, cenario.chao)) player->jumpTimer = 30;
        player->moves.dirY = -1;
    }
    
    player->hitbox.x += player->moves.dirX * player->moves.Xspeed;
    player->hitbox.y += player->moves.dirY * player->moves.Yspeed*10;

    Gravity(&player->hitbox, cenario.chao, player->moves.Yspeed, &player->airTime);
}

// Movimentos do inimigo:
// Inimigo Voador
void enemyMoves(Inimigo *seeker, float posX, float posY){
    seeker->moves.dirX = 0;
    seeker->moves.dirY = 0;

    // X moves
    if(seeker->hitbox.x+seeker->hitbox.width/2>posX+5){
        seeker->moves.dirX = -1;
    }else if(seeker->hitbox.x+seeker->hitbox.width/2<posX-5){
        seeker->moves.dirX = 1;
    }
    seeker->hitbox.x += seeker->moves.dirX * seeker->moves.Xspeed;

    // Y moves
    if(seeker->hitbox.y+seeker->hitbox.height/2>posY+5){
        seeker->moves.dirY = -1;
    }else if(seeker->hitbox.y+seeker->hitbox.height/2<posY-5){
        seeker->moves.dirY = 1;
    }
    seeker->hitbox.y += seeker->moves.dirY * seeker->moves.Yspeed;
}