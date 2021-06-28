#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <genesis.h>
#include <maths.h>
#include <resources.h>
#include <string.h>
#include "entity.h"

#define SFX_JUMP 64
#define SFX_DIE  65

extern bool onTitle;

extern const int scrollspeed;

extern const int floor_height;
extern fix16 gravity;
extern bool jumping;

extern int score;
extern char label_score[6];
extern char str_score[3];
extern bool score_added;

extern const char msg_start[22];
extern const char msg_reset[22];
extern const char msg_pause[8];
extern bool game_on;

extern void showText(char s[]);
extern void clearText();

extern void startGame();
extern void pauseGame();
extern void endGame();

extern void myJoyHandler( u16 joy, u16 changed, u16 state);

extern void moveObstacles();

extern void updateScoreDisplay();

extern u16 randomize(u16 n);


#endif