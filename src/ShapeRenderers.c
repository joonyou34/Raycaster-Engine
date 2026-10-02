#include "ShapeRenderers.h"


void drawArc(float cx, float cy, float rx, float ry, float theta, int segments,
            struct Color centerColor, struct Color vertexsColor) {

    float deltaTheta = theta/segments;
    float deltaSin = sinf(deltaTheta);
    float deltaCos = cosf(deltaTheta);

    float curSin = 0, curCos = 1;


    glColor4ub(centerColor.r, centerColor.g, centerColor.b, centerColor.a);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    
    glColor4ub(vertexsColor.r, vertexsColor.g, vertexsColor.b, vertexsColor.a);
    glVertex2f(cx + rx, cy);

    float oldSin;
    for(int segment = 1; segment <= segments; segment++) {
        oldSin = curSin;
        curSin = oldSin * deltaCos + deltaSin * curCos;
        curCos = curCos * deltaCos - oldSin * deltaSin;

        glVertex2f(cx + rx * curCos, cy + ry * curSin);
    }
    glEnd();
}

void drawArcFrom(float cx, float cy, float rx, float ry, float startTheta, float theta, int segments,
            struct Color centerColor, struct Color vertexsColor) {

    float deltaTheta = theta/segments;
    float deltaSin = sinf(deltaTheta);
    float deltaCos = cosf(deltaTheta);

    float curSin = sinf(startTheta), curCos = cosf(startTheta);

    glColor4ub(centerColor.r, centerColor.g, centerColor.b, centerColor.a);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    
    glColor4ub(vertexsColor.r, vertexsColor.g, vertexsColor.b, vertexsColor.a);
    glVertex2f(cx + rx * curCos, cy + ry * curSin);

    float oldSin;
    for(int segment = 1; segment <= segments; segment++) {
        oldSin = curSin;
        curSin = oldSin * deltaCos + deltaSin * curCos;
        curCos = curCos * deltaCos - oldSin * deltaSin;

        glVertex2f(cx + rx * curCos, cy + ry * curSin);
    }
    glEnd();
}


void drawRing(float cx, float cy, float r1x, float r1y, float r2x, float r2y, float theta,
                int segments, struct Color innerColor, struct Color outerColor) {

    float deltaTheta = theta/segments;
    float deltaSin = sinf(deltaTheta);
    float deltaCos = cosf(deltaTheta);

    float curSin = 0, curCos = 1;

    
    glBegin(GL_TRIANGLE_STRIP);
    glColor4ub(innerColor.r, innerColor.g, innerColor.b, innerColor.a);
    glVertex2f(cx + r1x, cy);
    glColor4ub(outerColor.r, outerColor.g, outerColor.b, outerColor.a);
    glVertex2f(cx + r2x, cy);
    
    float oldSin;
    for(int segment = 1; segment <= segments; segment++) {
        oldSin = curSin;
        curSin = oldSin * deltaCos + deltaSin * curCos;
        curCos = curCos * deltaCos - oldSin * deltaSin;
        
        glColor4ub(innerColor.r, innerColor.g, innerColor.b, innerColor.a);
        glVertex2f(cx + r1x * curCos, cy + r1y * curSin);

        glColor4ub(outerColor.r, outerColor.g, outerColor.b, outerColor.a);
        glVertex2f(cx + r2x * curCos, cy + r2y * curSin);
    }
    glEnd();
}


void drawRingFrom(float cx, float cy, float r1x, float r1y, float r2x, float r2y, float startTheta,
                    float theta, int segments, struct Color innerColor, struct Color outerColor) {

    float deltaTheta = theta/segments;
    float deltaSin = sinf(deltaTheta);
    float deltaCos = cosf(deltaTheta);

    float curSin = sinf(startTheta), curCos = cosf(startTheta);

    
    glBegin(GL_TRIANGLE_STRIP);
    glColor4ub(innerColor.r, innerColor.g, innerColor.b, innerColor.a);
    glVertex2f(cx + r1x * curCos, cy + r1y * curSin);
    glColor4ub(outerColor.r, outerColor.g, outerColor.b, outerColor.a);
    glVertex2f(cx + r2x * curCos, cy + r2y * curSin);
    
    float oldSin;
    for(int segment = 1; segment <= segments; segment++) {
        oldSin = curSin;
        curSin = oldSin * deltaCos + deltaSin * curCos;
        curCos = curCos * deltaCos - oldSin * deltaSin;
        
        glColor4ub(innerColor.r, innerColor.g, innerColor.b, innerColor.a);
        glVertex2f(cx + r1x * curCos, cy + r1y * curSin);

        glColor4ub(outerColor.r, outerColor.g, outerColor.b, outerColor.a);
        glVertex2f(cx + r2x * curCos, cy + r2y * curSin);
    }
    glEnd();
}