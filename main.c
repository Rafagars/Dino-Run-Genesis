#include <genesis.h>
#include "functions.h"

const int scrollspeed = 2;
int i;

int main()
{   
    // Input
    JOY_init();
    JOY_setEventHandler( &myJoyHandler );

    VDP_setPaletteColor(0, RGB24_TO_VDPCOLOR(0x6dc2ca));
    VDP_setPlanSize(16, 16);

    VDP_setScrollingMode(HSCROLL_PLANE, VSCROLL_PLANE);

    VDP_loadTileSet(grass.tileset, 1, DMA);
    VDP_loadTileSet(cloud.tileset, 2, DMA);

    VDP_setPalette(PAL1, grass.palette->data);

    VDP_fillTileMapRect(BG_B, TILE_ATTR_FULL(PAL1, 0, FALSE, FALSE, 1), 0, 20, 32, 14);
    VDP_fillTileMapRectInc(BG_B, TILE_ATTR_FULL(PAL0, 0, FALSE, FALSE, 2), 4, 3, 4, 2);
    VDP_fillTileMapRectInc(BG_B, TILE_ATTR_FULL(PAL0, 0, FALSE, FALSE, 2), 15, 5, 4, 2);
    VDP_fillTileMapRectInc(BG_B, TILE_ATTR_FULL(PAL0, 0, FALSE, FALSE, 2), 26, 4, 4, 2);
    showText(msg_start);

    SPR_init(0, 0, 0);
    player.sprite = SPR_addSprite(&dino, player.x, player.y, TILE_ATTR(PAL1, 0, FALSE, FALSE));
    //obstacle.sprite = SPR_addSprite(&cactus, obstacle.x, obstacle.y, TILE_ATTR(PAL1, 0, FALSE, FALSE));

    // Create all obstacles sprites
    Entity* obs = obstacles;

    for(i = 0; i < MAX_ENEMIES; i++){
        obs->x = randomize(100) + 220;
        obs->y = FIX16(145);
        obs->w = 16;
        obs->h = 16;
        obs->sprite = SPR_addSprite(&cactus, obs->x, obs->y, TILE_ATTR(PAL1, 0, FALSE, FALSE));
        sprintf(obs->name, "Obs%d", i);
        obs++;
        Entity* obs = &obstacles[i];
    }
    // init SFX
    XGM_setPCM(SFX_JUMP, jump_sfx, sizeof(jump_sfx));
    XGM_setPCM(SFX_DIE, die_sfx, sizeof(die_sfx));

    int offset = 0;
    while(1)
    {
        VDP_setHorizontalScroll(BG_B, offset -= scrollspeed);
        // To avoid possible overflow
        if(offset <= -256){
            offset = 0;
        }
        for(i = 0; i < MAX_ENEMIES; i++){
            //Move the obstacle
            obstacles[i].vel_x = -scrollspeed;
            obstacles[i].x += obstacles[i].vel_x;
            if(obstacles[i].x < -8){
                obstacles[i].x = randomize(100) + 220;
            }
            if(player.x < obstacles[i].x + 16 && player.x + 16 > obstacles[i].x){
                    if(jumping == FALSE){
                        endGame();
                    } else {
                        if(score_added == FALSE){
                            score++;
                            updateScoreDisplay();
                            score_added = TRUE;
                        }
                    }
            }
        }



        if(game_on == TRUE){
            //Apply velocity
            player.y = fix16Add(player.y, player.vel_y);
            //Apply gravity
            if(jumping == TRUE){
                player.vel_y = fix16Add(player.vel_y, gravity);
            }
            if(jumping == TRUE && fix16ToInt(player.y) + player.h >= (floor_height)){
                jumping = FALSE;
                player.vel_y = FIX16(0);
                player.y = intToFix16(floor_height - player.h);
                score_added = FALSE;
            }
        }
        SPR_setPosition(player.sprite, player.x, fix16ToInt(player.y));
        //SPR_setPosition(obstacle.sprite, obstacle.x, fix16ToInt(obstacle.y));
        for(i = 0; i < MAX_ENEMIES; i++){
            SPR_setPosition(obstacles[i].sprite, obstacles[i].x, fix16ToInt(obstacles[i].y));
        }
        SPR_update();
        SYS_doVBlankProcess();
    }
    MEM_free(&player);
    MEM_free(&obstacles);
    return 0;
}