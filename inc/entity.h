#ifndef ENTITY_H
#define ENTITY_H

#include <genesis.h>

#define MAX_ENEMIES 3

typedef struct {
    int x;
    fix16 y;
    int w;
    int h;
    int vel_x;
    fix16 vel_y;
    Sprite* sprite;
    char name[6];
} Entity;

extern Entity player;
extern Entity obstacles[MAX_ENEMIES];

#endif