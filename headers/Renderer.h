#ifndef RENDERER
#define RENDERER
#include "Global.h"

#define RN_BUFFER_CAPACITY 16384

#define RN_TEXTURE 0
#define RN_LINE 1
struct RenderData {
    byte dataType;
    void* data;
};

// struct RenderData RN_

struct RenderData RN_Buffer[RN_BUFFER_CAPACITY];
int RN_bufferSize;

void RN_render() {

}

#endif