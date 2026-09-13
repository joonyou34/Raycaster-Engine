#include "Renderer.h"

struct RenderData RN_buffer[RN_BUFFER_CAPACITY];
int RN_bufferSize;

struct RenderData RN_lineToData(float x1, float y1,
                                float x2, float y2,
                                byte R, byte G, byte B, byte A,
                                float distance) {
    struct RenderData ret;
    ret.dataType = RN_LINE;
    ret.distance = distance;

    ret.data = malloc(sizeof(float)*4 + sizeof(byte)*4);


    *((float*)ret.data)     = x1;
    *((float*)ret.data + 1) = y1;
    *((float*)ret.data + 2) = x2;
    *((float*)ret.data + 3) = y2;

    *((byte*)((float*)ret.data + 4))     = R;
    *((byte*)((float*)ret.data + 4) + 1) = G;
    *((byte*)((float*)ret.data + 4) + 2) = B;
    *((byte*)((float*)ret.data + 4) + 3) = A;


    return ret;
}

struct RenderData RN_textureToData(GLuint textureId,
                                float x, float y,
                                float width, float height,
                                float distance) {
    struct RenderData ret;
    ret.dataType = RN_TEXTURE;
    ret.distance = distance;

    ret.data = malloc(sizeof(float)*4 + sizeof(GLuint));

    *((GLuint*)ret.data) = textureId;
    
    *((float*)((GLuint*)ret.data + 1))     = x;
    *((float*)((GLuint*)ret.data + 1) + 1) = y;
    *((float*)((GLuint*)ret.data + 1) + 2) = width;
    *((float*)((GLuint*)ret.data + 1) + 3) = height;

    return ret;
}

void RN_delete(struct RenderData* a) {
    free(a->data);
    a->data = NULL;
}

void RN_append(struct RenderData data) {
    RN_buffer[RN_bufferSize++] = data;
}

int RN_comp(const void* a, const void* b) {
    float d1 = ((struct RenderData*)a)->distance;
    float d2 = ((struct RenderData*)b)->distance;
    
    if(d1 < d2) return -1;
    return (d1 > d2);
}

void RN_render() {
    //! consider using a different sorting algorithm since this one is weird
    qsort(RN_buffer, RN_bufferSize, sizeof(struct RenderData), RN_comp);
    //TODO iterate over the buffer and render everything
}