#ifndef MAP
#define MAP

#include "Global.h"
#define MAP_X 16
#define MAP_Y 12

// size of each square of the grid
extern float squareWidth;
extern float squareHeight;

// the grid
extern unsigned char map[MAP_Y][MAP_X];

void MP_render();

#endif