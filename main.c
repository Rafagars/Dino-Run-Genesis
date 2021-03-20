#include <genesis.h>
#include "functions.h"

const int scrollspeed = 2;

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
    obstacle.sprite = SPR_addSprite(&cactus, obstacle.x, obstacle.y, TILE_ATTR(PAL1, 0, FALSE, FALSE));

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
        //Move the obstacle
        obstacle.vel_x = -scrollspeed;
        obstacle.x += obstacle.vel_x;
        if(obstacle.x < -8){
            obstacle.x = randomize(200) + 120;
        }

       if(player.x < obstacle.x + 16 && player.x + 16 > obstacle.x){
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
                SPR_setAnim(player.sprite, ANIM_RUN);
                score_added = FALSE;
            }
        }
        SPR_setPosition(player.sprite, player.x, fix16ToInt(player.y));
        SPR_setPosition(obstacle.sprite, obstacle.x, fix16ToInt(obstacle.y));
        SPR_update();
        SYS_doVBlankProcess();
    }
    MEM_free(&player);
    MEM_free(&obstacle);
    return 0;
}