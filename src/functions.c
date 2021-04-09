#include "functions.h"
#include "gameStates.h"

// The edges of the play field
const int LEFT_EDGE = 0;
const int RIGHT_EDGE = 320;
const int TOP_EDGE = 0;
const int BOTTOM_EDGE = 165;

const int scrollspeed = 2;

const int floor_height = 160;
fix16 gravity = FIX16(0.2);
bool jumping = FALSE;

int score = 0;
char label_score[6] = "SCORE\0";
char str_score[3] = "0";
bool score_added = FALSE;

// General stuff
const char msg_start[22] = "Press START to Begin!";
const char msg_reset[22] = "GAME OVER\tPress START";
const char msg_pause[8] = "PAUSED";
bool game_on = FALSE;

void showText(char s[]){
    VDP_drawText(s, 20 - strlen(s)/2, 1);
}

void clearText(){
    VDP_clearText(0, 1, 32);
}

void startGame(){
    if(game_on == FALSE){
        game_on = TRUE;
        clearText();
        player.x = 10;
    }
    VDP_drawText(label_score, 1, 0);
    score = 0;
    updateScoreDisplay();
    for(int i = 0; i < MAX_ENEMIES; i++){
        obstacles[i].x = 320 + randomize(200);
    }
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
        XGM_startPlayPCM(SFX_DIE, 1, SOUND_PCM_CH2);
        showText(msg_reset);
        game_on = FALSE;
    }
}

void myJoyHandler( u16 joy, u16 changed, u16 state){
    if(joy == JOY_1){
        //Start the game or paused if START is pressed 
        if(state & BUTTON_START){
            if(game_on == FALSE){
                startGame();
                VDP_clearTextAreaBG(BG_A, 0, 0, 32, 24);
                playState();
            } else if(game_on == TRUE){
                game_on = FALSE;
                pauseGame();
            }
        }
        if( state & (BUTTON_A | BUTTON_UP) ){
            if(jumping == FALSE){
                jumping = TRUE;
                player.vel_y = FIX16(-4);
                //SPR_setAnim(player.sprite, ANIM_JUMP);
                XGM_startPlayPCM(SFX_JUMP, 1, SOUND_PCM_CH2);
            }
        }
    }
}

void moveObstacles(){

    for(int i = 0; i < MAX_ENEMIES; i++){
        //Move the obstacle
        obstacles[i].vel_x = -scrollspeed;
        obstacles[i].x += obstacles[i].vel_x;
        if(obstacles[i].x < -8){
            obstacles[i].x = 320 + randomize(200);
            if (obstacles[i].x - obstacles[i-1].x < 12){
                obstacles[i].x += 16;
            } 
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
        SPR_setPosition(obstacles[i].sprite, obstacles[i].x, fix16ToInt(obstacles[i].y));
    }

}

void updateScoreDisplay(){
    sprintf(str_score, "%d", score);
    VDP_clearText(0, 1, 3);
    VDP_drawText(str_score, 1, 1);
}

u16 randomize(u16 n){
    u16 x;
    do { x = random(); }
    while (x >= n);

    return x;
}

