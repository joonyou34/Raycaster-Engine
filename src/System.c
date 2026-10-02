#include "System.h"

unsigned int mSPF = 16;

unsigned int lastTime = 0;


void updateDT() {
    unsigned int curtime = glutGet(GLUT_ELAPSED_TIME);
    dtMs = curtime-lastTime;
    lastTime = curtime;
    dt = dtMs/1000.f;
}

void changeFPS(unsigned short FPS) {
    mSPF = 1000u/FPS;
}