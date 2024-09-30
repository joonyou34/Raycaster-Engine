#ifndef SYSTEM
#define SYSTEM

#include "Global.h"

//milliseconds per frame
extern unsigned int mSPF;

//time of last frame
extern unsigned int lastTime;

void updateDT();

void changeFPS(unsigned short FPS);

void drawCircle(float cx, float cy, float r, int num_segments);

#endif