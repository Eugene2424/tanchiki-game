#include "..\inc\tankc.h"
#include "genesis.h"
#include "resources.h"


typedef enum {
    TOP,
    DOWN,
    RIGHT,
    LEFT
} Animka;


Sprite* stank;
Animka anim;
int posX, posY;
int movX, movY;

void initPlayer()
{
    posX = 20;
    posY = 20;
    movX = 0;
    movY = 0;

    anim = TOP;

    PAL_setPalette(PAL0, tank1.palette->data, DMA);
    stank = SPR_addSprite(&tank1, 4, 5, TILE_ATTR(PAL0, FALSE, FALSE, FALSE));
}

void updatePlayer()
{
    handlePlayerInput();
    posX += movX;
    posY += movY;
    SPR_setPosition(stank, posX, posY);
}
void handlePlayerInput()
{
    u16 joy = JOY_readJoypad(JOY_1);
    if (joy & BUTTON_UP)
    {
        movY = -PLAYER_SPEED;
        SPR_setAnim(stank, 0);
        anim = TOP;
    }
    else if (joy & BUTTON_DOWN)
    {
        movY = PLAYER_SPEED;
        SPR_setAnim(stank, 2);
        anim = DOWN;
    }
    else
    {
        movY = 0;
    }
    if (joy & BUTTON_RIGHT)
    {
        movX = PLAYER_SPEED;
        SPR_setAnim(stank, 1);
        anim = RIGHT;
    }

    else if (joy & BUTTON_LEFT)
    {
        movX = -PLAYER_SPEED;
        SPR_setAnim(stank, 3);
        anim = LEFT;
    }
    else
    {
        movX = 0;
    }

    if (anim == TOP && !(joy & BUTTON_UP))
    {
        SPR_setAnim(stank, 4);
    }
    else if (anim == DOWN && !(joy & BUTTON_DOWN))
    {
        SPR_setAnim(stank, 6);
    }
    else if (anim == RIGHT && !(joy & BUTTON_RIGHT))
    {
        SPR_setAnim(stank, 5);
    }
    else if (anim == LEFT && !(joy & BUTTON_LEFT))
    {
        SPR_setAnim(stank, 7);
    }
}