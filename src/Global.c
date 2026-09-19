#include "Global.h"

unsigned int dtMs = 0;
float dt = 0;

int screenWidth = DEFAULT_BASE_WIDTH, screenHeight = DEFAULT_BASE_HEIGHT;

#ifdef DEBUG_FEATURES
    int stkPtr = 0;
    float stkX1[DEFAULT_BASE_WIDTH+10] = {};
    float stkY1[DEFAULT_BASE_WIDTH+10] = {};
    float stkX2[DEFAULT_BASE_WIDTH+10] = {};
    float stkY2[DEFAULT_BASE_WIDTH+10] = {};

    bool DEBUG_showHitboxs = 0;
    bool DEBUG_showRaycasterRays = 0;
    bool DEBUG_showTileDistance = 0;
#endif