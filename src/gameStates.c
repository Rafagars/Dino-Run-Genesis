#include "gameStates.h"

int i;
u16 index;

void titleState(){
    index = TILE_USERINDEX;

    VDP_setPalette(PAL1, title.palette->data);

    VDP_drawImageEx(BG_A, &bg_a, TILE_ATTR_FULL(PAL1, 0, FALSE, FALSE, index), 0, 0, TRUE, DMA);
    
    index += bg_a.tileset->numTile;

    VDP_drawImageEx(BG_B, &title, TILE_ATTR_FULL(PAL1, 1, FALSE, FALSE, index), 0, 0, TRUE, DMA);

    index += title.tileset->numTile;
 

    //VDP_drawText(msg_start, 20 - strlen(msg_start)/2, 23);
}

void playState(){

    // Draw score text 
    VDP_drawText(label_score, 1, 1);
    VDP_drawText(str_score, 1, 2);

    index = TILE_USERINDEX;

    VDP_setPalette(PAL0, bg_a.palette->data);
    VDP_setPalette(PAL1, grass.palette->data);

    VDP_drawImageEx(BG_B, &bg_a, TILE_ATTR_FULL(PAL0, 0, FALSE, FALSE, index), 0, 0, TRUE, DMA);

    index += bg_a.tileset->numTile;

    VDP_setScrollingMode(HSCROLL_PLANE, VSCROLL_PLANE);

    VDP_loadTileSet(grass.tileset, 1, DMA);
    

    VDP_fillTileMapRect(BG_B, TILE_ATTR_FULL(PAL0, 1, FALSE, FALSE, 1), 0, 20, 32, 14);
    

}