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

void drawCircle(float cx, float cy, float r, int num_segments) {
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i <= num_segments; i++) {
        float theta = 2.f * PI * i / num_segments;
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}