#ifndef GLOBAL
#define GLOBAL
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//absolute width
#define BASE_WIDTH 800
//absolute height
#define BASE_HEIGHT 600

#define PI       3.1415926f
#define TWO_PI   6.2831852f
#define RAD_30   0.5235988f   // 30 degrees
#define RAD_45   0.7853982f   // 45 degrees
#define RAD_60   1.0471976f   // 60 degrees
#define RAD_90   1.5707963f   // 90 degrees
#define RAD_180  3.1415926f   // 180 degrees
#define RAD_270  4.7123889f   // 270 degrees
#define RAD_360  6.2831853f   // 360 degrees
typedef boolean bool;

//deltaTime in ms
extern unsigned int dtMs;
//deltaTime in seconds
extern float dt;

extern int stkPtr;
extern float stkX1[BASE_WIDTH+10];
extern float stkY1[BASE_WIDTH+10];
extern float stkX2[BASE_WIDTH+10];
extern float stkY2[BASE_WIDTH+10];

#endif