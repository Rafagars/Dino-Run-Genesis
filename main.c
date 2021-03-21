#include <genesis.h>
#include "functions.h"
#include "gameStates.h"

int main()
{   
    // Input
    JOY_init();
    JOY_setEventHandler( &myJoyHandler );

    VDP_setPlanSize(16, 16);

    titleState();
    
    return 0;
}
