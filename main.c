#include <genesis.h>
#include "functions.h"
#include "gameStates.h"

int main()
{   
    // Input
    JOY_init();
    JOY_setEventHandler( &myJoyHandler );

    
    VDP_setPlanSize(16, 16);
    if(game_on == TRUE){
        VDP_setPaletteColor(0, RGB24_TO_VDPCOLOR(0x6dc2ca));
    } else {
        playState();
    }

    return 0;
}
