#include <genesis.h>
#include "functions.h"
#include "gameStates.h"

int main()
{   
    // Input
    JOY_init();
    JOY_setEventHandler( &myJoyHandler );
    
    VDP_setPlanSize(16, 16);

    // init SFX
    XGM_setPCM(SFX_JUMP, jump_sfx, sizeof(jump_sfx));
    XGM_setPCM(SFX_DIE, die_sfx, sizeof(die_sfx));

    titleState();

    SPR_init(0, 0, 0);
    player.sprite = SPR_addSprite(&dino, player.x, player.y, TILE_ATTR(PAL0, 1, FALSE, FALSE));

    // Create all obstacles sprites
    Entity* obs = obstacles;

    for(i = 0; i < MAX_ENEMIES; i++){
        obs->x = 350;
        obs->y = FIX16(145);
        obs->w = 16;
        obs->h = 16;
        obs->sprite = SPR_addSprite(&cactus, obs->x, obs->y, TILE_ATTR(PAL0, 0, FALSE, FALSE));
        sprintf(obs->name, "Obs%d", i);
        obs++;
        Entity* obs = &obstacles[i];
    }

    fix16 offsetA = FIX16(0);
    int offsetB = 0;
    while(1)
    {
        if(game_on == TRUE){
            // Scroll Background
            VDP_setHorizontalScroll(BG_A, offsetA = fix16Add(offsetA, -1.5));
            VDP_setHorizontalScroll(BG_B, offsetB -= scrollspeed);
            // To avoid possible overflow
            if(offsetA <= FIX16(-256)){
                offsetA = FIX16(0);
            }
            if(offsetB <= -256){
                offsetB = 0;
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
    
    return 0;
}
