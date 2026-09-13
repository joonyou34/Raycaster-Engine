#ifndef RENDERER
#define RENDERER
#include "Global.h"

#define RN_BUFFER_CAPACITY 16384

#define RN_TEXTURE 0
#define RN_LINE 1
struct RenderData {
    void* data;
    float distance;
    byte dataType;
};

struct LineData {
    float x1, y1;
    float x2, y2;
    byte R, G, B, A;
};

struct TextureData {
    GLuint textureId;
    float x, y;
    float width, height;
};

struct RenderData RN_lineToData(float x1, float y1,
                                float x2, float y2,
                                byte R, byte G, byte B, byte A,
                                float distance);

struct RenderData RN_textureToData(GLuint textureId,
                                float x, float y,
                                float width, float height,
                                float distance);

void RN_delete(struct RenderData* a);
void RN_append(struct RenderData data);
void RN_render();


#endif