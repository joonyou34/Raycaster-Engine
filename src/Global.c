#include "Global.h"

unsigned int dtMs = 0;
float dt = 0;

int screenWidth = DEFAULT_BASE_WIDTH, screenHeight = DEFAULT_BASE_HEIGHT;

// bc: back color channel (value)
// ba: back color alpha
// fc: front color channel (value)
// fainv: front color alpha inverse (1 - front alpha)
#define blendColor(bc, ba, fc, fainv) (fainv * (ba * bc) + fc)

struct Color blend(struct Color back, struct Color front) {
    struct Color ret;
    float ba_f = back.a/255.f;
    float fainv = 1 - front.a/255.f;


    ret.r = blendColor(back.r, ba_f, front.r, fainv);
    ret.g = blendColor(back.g, ba_f, front.g, fainv);
    ret.b = blendColor(back.b, ba_f, front.b, fainv);
    
    ret.a = front.a + (byte)roundf(ba_f * fainv * 255.f);

    return ret;
}

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