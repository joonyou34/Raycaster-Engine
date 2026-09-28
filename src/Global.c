#include "Global.h"

unsigned int dtMs = 0;
float dt = 0;

int screenWidth = DEFAULT_BASE_WIDTH, screenHeight = DEFAULT_BASE_HEIGHT;

// bc: back color channel (value)
// ba: back color alpha
// fc: front color channel (value)
// fainv: front color alpha inverse (1 - front alpha)
// fa: front alpha
// suma_inv: 1/new_alpha
#define blendColor(bc, ba, fc, fainv, fa, suma_inv) (byte)roundf((fainv * (ba * bc) + fc*fa)*suma_inv)

struct Color blend(struct Color back, struct Color front) {
    if(front.a == 0) return back;
    if(back.a == 0) return front;
    
    struct Color ret;
    float ba_f = back.a/255.f;
    float fa_f = front.a/255.f;
    float fainv = 1.f - fa_f;
    float reta_f = fa_f + ba_f * fainv;
    float reta_inv = 1.f/reta_f;

    
    
    ret.a = (byte)roundf(reta_f*255.f);

    ret.r = blendColor(back.r, ba_f, front.r, fainv, fa_f, reta_inv);
    ret.g = blendColor(back.g, ba_f, front.g, fainv, fa_f, reta_inv);
    ret.b = blendColor(back.b, ba_f, front.b, fainv, fa_f, reta_inv);
    

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