#include "gameStates.h"

int i;

void playState(){

    u16 index = TILE_USERINDEX;

    VDP_setPalette(PAL0, bg_a.palette->data);
    VDP_setPalette(PAL1, grass.palette->data);

    VDP_drawImageEx(BG_B, &bg_a, TILE_ATTR_FULL(PAL0, 0, FALSE, FALSE, index), 0, 0, TRUE, DMA);

    index += bg_a.tileset->numTile;

    VDP_setScrollingMode(HSCROLL_PLANE, VSCROLL_PLANE);

    VDP_loadTileSet(grass.tileset, 1, DMA);
    

    VDP_fillTileMapRect(BG_B, TILE_ATTR_FULL(PAL0, 1, FALSE, FALSE, 1), 0, 20, 32, 14);

    showText(msg_start);

    SPR_init(0, 0, 0);
    player.sprite = SPR_addSprite(&dino, player.x, player.y, TILE_ATTR(PAL0, 1, FALSE, FALSE));

    // Create all obstacles sprites
    Entity* obs = obstacles;

    for(i = 0; i < MAX_ENEMIES; i++){
        obs->x = 320 + randomize(200);
        obs->y = FIX16(145);
        obs->w = 16;
        obs->h = 16;
        obs->sprite = SPR_addSprite(&cactus, obs->x, obs->y, TILE_ATTR(PAL0, 0, FALSE, FALSE));
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
        if(game_on == TRUE){
            // Scroll Background
            VDP_setHorizontalScroll(BG_B, offset -= scrollspeed);
            // To avoid possible overflow
            if(offset <= -256){
                offset = 0;
            }

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
            
            moveObstacles();
        }
        SPR_setPosition(player.sprite, player.x, fix16ToInt(player.y));
        SPR_update();
        SYS_doVBlankProcess();
    }
    MEM_free(&player);
    MEM_free(&obstacles);
}