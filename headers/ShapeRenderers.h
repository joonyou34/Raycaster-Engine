#ifndef SHAPE_RENDERER
#define SHAPE_RENDERER

#include "Global.h"

// draws an eleptic arc (a ciruclar one if rx = ry)
// starts from angle zero and cycles in the direction:
// - positive theta if theta is positive
// - negative theta if theta is negative
// segments determine the number of triangular segments to use
// the higher the number of segments the smoother the arc looks
//! but, it affects performance
//! segments < 3 would probably result in undefined behavior or weird artifacts
void drawArc(float cx, float cy, float rx, float ry, float theta, int segments,
            struct Color centerColor, struct Color vertexsColor);


// draws an eleptic arc (a ciruclar one if rx = ry)
// starts from angle startTheta and cycles in the direction:
// - positive theta if theta is positive
// - negative theta if theta is negative
// segments determine the number of triangular segments to use
// the higher the number of segments the smoother the arc looks
//! but, it affects performance
//! segments < 3 would probably result in undefined behavior or weird artifacts
void drawArcFrom(float cx, float cy, float rx, float ry, float startTheta, float theta, int segments,
            struct Color centerColor, struct Color vertexsColor);

// draws an elaptic (or circular if rx = ry for both r1 and r2) ring if theta is 2 * PI,
// or a partial ring if theta < 2 * PI
// starts from angle zero and cycles in the direction:
// - positive theta if theta is positive
// - negative theta if theta is negative
// segments determine the number of triangular segments to use
// the higher the number of segments the smoother the arc looks
//! but, it affects performance
//! segments < 3 would probably result in undefined behavior or weird artifacts
void drawRing(float cx, float cy, float r1x, float r1y, float r2x, float r2y, float theta,
                int segments, struct Color innerColor, struct Color outerColor);
// draws an elaptic (or circular if rx = ry for both r1 and r2) ring if theta is 2 * PI,
// or a partial ring if theta < 2 * PI
// starts from angle startTheta and cycles in the direction:
// - positive theta if theta is positive
// - negative theta if theta is negative
// segments determine the number of triangular segments to use
// the higher the number of segments the smoother the arc looks
//! but, it affects performance
//! segments < 3 would probably result in undefined behavior or weird artifacts
void drawRingFrom(float cx, float cy, float r1x, float r1y, float r2x, float r2y, float startTheta,
                    float theta, int segments, struct Color innerColor, struct Color outerColor);

#endif