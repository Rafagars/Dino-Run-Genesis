#include "functions.h"

// The edges of the play field
const int LEFT_EDGE = 0;
const int RIGHT_EDGE = 320;
const int TOP_EDGE = 0;
const int BOTTOM_EDGE = 165;

const int floor_height = 160;
fix16 gravity = FIX16(0.2);
bool jumping = FALSE;

int score = 0;
char label_score[6] = "SCORE\0";
char str_score[3] = "0";
bool score_added = FALSE;

// General stuff
const char msg_start[22] = "Press START to Begin!";
const char msg_reset[22] = "GAME OVER";
const char msg_pause[8] = "PAUSED";
bool game_on = FALSE;

void showText(char s[]){
    VDP_drawText(s, 20 - strlen(s)/2, 10);
}

void clearText(){
    VDP_clearText(0, 10, 32);
}

void startGame(){
    if(game_on == FALSE){
        game_on = TRUE;
        clearText();
    }
    VDP_drawText(label_score, 1, 1);
    score = 0;
    updateScoreDisplay();
    obstacle.x = 320;
}

void pauseGame(){
    if(game_on == FALSE){
        showText(msg_pause);
    } else {
        game_on = TRUE;
    }
}

void endGame(){
    if(game_on == TRUE){
        SND_startPlayPCM_XGM(SFX_DIE, 1, SOUND_PCM_CH2);
        showText(msg_reset);
        game_on = FALSE;
    }
}

void myJoyHandler( u16 joy, u16 changed, u16 state){
    if(joy == JOY_1){
        //Start the game if START if pressed or Pause the game
        if(state & BUTTON_START){
            if(game_on == FALSE){
                startGame();
            } else if(game_on == TRUE){
                game_on = FALSE;
                pauseGame();
            }
        }
        if( state & BUTTON_A){
            if(jumping == FALSE){
                jumping = TRUE;
                player.vel_y = FIX16(-4);
                //SPR_setAnim(player.sprite, ANIM_JUMP);
                SND_startPlayPCM_XGM(SFX_JUMP, 1, SOUND_PCM_CH2);
            }
        }
    }
}

void updateScoreDisplay(){
    sprintf(str_score, "%d", score);
    VDP_clearText(1, 2, 3);
    VDP_drawText(str_score, 1, 2);
}

u16 randomize(u16 n){
    u16 x;
    do { x = random(); }
    while (x >= n);

    return x;
}
