#include "gameStates.h"

int i;
u16 index;

//Backgrounds for the Title Screen
void titleState(){
    
    VDP_setTextPlane(BG_B);

    index = TILE_USERINDEX;

    VDP_setPalette(PAL1, title.palette->data);

    VDP_drawImageEx(BG_A, &bg_a, TILE_ATTR_FULL(PAL1, 0, FALSE, FALSE, index), 0, 0, TRUE, DMA);
    
    index += bg_a.tileset->numTile;

    VDP_drawImageEx(BG_B, &title, TILE_ATTR_FULL(PAL1, 1, FALSE, FALSE, index), 0, 0, TRUE, DMA);

    index += title.tileset->numTile;
 

    VDP_drawText(msg_start, 20 - strlen(msg_start)/2, 23);
}

//Backgrounds, window layer and scroll mode for the level
void playState(){
    
    VDP_setTextPlane(WINDOW);
    VDP_setWindowVPos(FALSE, 2);
    
    //Draw score text 
    VDP_drawText(label_score, 1, 0);
    VDP_drawText(str_score, 1, 1);

    index = TILE_USERINDEX;

    VDP_setPalette(PAL0, bg_a.palette->data);

    VDP_drawImageEx(BG_A, &bg_a, TILE_ATTR_FULL(PAL0, 0, FALSE, FALSE, index), 22, 0, TRUE, DMA);
    
    index += bg_a.tileset->numTile;


    VDP_setScrollingMode(HSCROLL_PLANE, VSCROLL_PLANE);

    VDP_drawImageEx(BG_B, &bg_b, TILE_ATTR_FULL(PAL0, 1 ,FALSE, FALSE, index), 0, 0, FALSE, DMA);
}