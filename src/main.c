#include <genesis.h>
#include <resources.h>
#include "..\inc\tankc.h"

typedef enum {
    TITLE_SCREEN,
    GAME_SCENE
} GameState;


u16 ind;
float time = 0;
float tstart_pos = -55;
bool started_scene = FALSE;

Sprite* select_arrow;

void allInit();

void initializeTitleScreen();
void updateTitleScreen();

void initializeGameScene();
void updateGameScene();

void updateScene();
void checkPauseState();
void handleInput();



GameState currentState = TITLE_SCREEN;


int lifes1 = 3;
int lifes2 = 0;
char lifes1s[2];
char lifes2s[2];

bool player2mode = TRUE;
bool game_running = TRUE;
bool btnpressed = FALSE;
bool btnpressedA = FALSE;


int main()
{
    allInit();
    while (1)
    {

        switch (currentState)
        {
            case TITLE_SCREEN:
                initializeTitleScreen();
                updateTitleScreen();
                break;

            case GAME_SCENE:
                initializeGameScene();
                updateGameScene();
                break;

            default:
                break;
        }

        VDP_waitVSync();
        SYS_doVBlankProcess();
    }

    return 0;
}

void allInit()
{
    VDP_setScreenWidth320();
    VDP_setScreenHeight224();

    VDP_init();
    SPR_init();

    SYS_enableInts();
}


void initializeTitleScreen()
{
    if (started_scene == FALSE)
    {
        XGM_startPlay(title_music);
        PAL_setPalette(PAL0, title.palette->data, DMA);
        PAL_setPalette(PAL1, select_tank.palette->data, DMA);
        PAL_setPalette(PAL2, side.palette->data, DMA);
        PAL_setPalette(PAL3, palette_black, DMA);
        VDP_drawImageEx(BG_A, &title, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, ind), 0, 0, FALSE, TRUE);
        ind += title.tileset->numTile;
        select_arrow = SPR_addSprite(&select_tank, screenWidth/2-58, screenHeight/2+11, TILE_ATTR(PAL1, FALSE, FALSE, FALSE));
        started_scene = TRUE;
    }
}

void updateTitleScreen()
{
    u16 joy = JOY_readJoypad(JOY_1);
    time += 0.01;
    handleInput();

    if (!(joy & BUTTON_A) && !player2mode && btnpressedA)
    {
        SPR_update();
        SPR_setPosition(select_arrow, screenWidth/2-58, screenHeight/2+27);
        player2mode = TRUE;
        btnpressedA = FALSE;
    }
    else if (!(joy & BUTTON_A) && player2mode && btnpressedA)
    {
        SPR_update();
        SPR_setPosition(select_arrow, screenWidth/2-58, screenHeight/2+11);
        player2mode = FALSE;
        btnpressedA = FALSE;
    }

    if (btnpressed == TRUE && !(joy & BUTTON_START))
    {
        updateScene();
        started_scene = FALSE;
        currentState = GAME_SCENE;
        SPR_releaseSprite(select_arrow);
        btnpressed = FALSE;
    }
    if (tstart_pos < 0)
    {
        tstart_pos += time;
        VDP_setVerticalScroll(BG_A, tstart_pos);
    }
}



void initializeGameScene()
{
    if (started_scene == FALSE)
    {
        time = 0;
        sprintf(lifes1s, "%d", lifes1);
        sprintf(lifes2s, "%d", lifes2);
        PAL_setPalette(PAL1, stage01.palette->data, DMA);
        VDP_drawImageEx(BG_A, &stage01, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, ind), 0, 0, FALSE, TRUE);
        waitMs(3000);
        VDP_fillTileMapRect(BG_A, TILE_ATTR(PAL3, FALSE, FALSE, FALSE), 0, 13, 50, 1);
        initPlayer();
        started_scene = TRUE;
    }
}

void updateGameScene() 
{
    checkPauseState();
    if (game_running == TRUE)
    {

        // Scene start effect
        if (time < 14)
        {
            time +=1;
            VDP_fillTileMapRect(BG_A, TILE_ATTR(PAL2, FALSE, FALSE, FALSE), 0, 13 - time, 50, 1);
            VDP_fillTileMapRect(BG_A, TILE_ATTR(PAL2, FALSE, FALSE, FALSE), 0, 13 + time, 50, 1);
        }
        else
        {
            SPR_update();
            VDP_drawText(lifes1s, 38, 17);
            VDP_drawImageEx(BG_B, &side, TILE_ATTR_FULL(PAL2, FALSE, FALSE, FALSE, ind), 36, 0, FALSE, TRUE);
            updatePlayer();        
        }
    }
}


void updateScene()
{
    VDP_clearPlane(BG_A, 1);
    VDP_clearPlane(BG_B, 1);
    SPR_update();
    VDP_clearSprites();
    
    started_scene = FALSE;
}


void checkPauseState()
{
    u16 joy = JOY_readJoypad(JOY_1);

    if (joy & BUTTON_START) {
        btnpressed = TRUE;
    } 

    if (btnpressed == TRUE && !(joy & BUTTON_START) && game_running == FALSE)
    {
        game_running = TRUE;
        btnpressed = FALSE;
    }
    else if (btnpressed == TRUE && !(joy & BUTTON_START) && game_running == TRUE)
    {
        game_running = FALSE;
        XGM_stopPlay();
        btnpressed = FALSE;
    }
}

void handleInput()
{
    u16 joy = JOY_readJoypad(JOY_1);
    if (joy & BUTTON_START) {
        btnpressed = TRUE;
    } 
    if (joy & BUTTON_A)
    {
        btnpressedA = TRUE;
    }
}