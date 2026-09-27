#ifndef RENDERER
#define RENDERER
#include "Global.h"


#define RN_LINE_CAPACITY 16384
#define RN_TEXTURE_CAPACITY 16384
#define RN_BUFFER_CAPACITY (RN_LINE_CAPACITY + RN_TEXTURE_CAPACITY)

#define RN_TEXTURE 0
#define RN_LINE 1
struct RenderData {
    float distance;
    int dataIdx;
    byte dataType;
};

struct LineData {
    float x1, y1;
    float x2, y2;
    float width;
    struct Color color;
    byte R, G, B, A;
};

struct TextureData {
    GLuint textureId;
    float x, y;
    float width, height;
};

void RN_AppendLine(float x1, float y1,
                                float x2, float y2,
                                float width,
                                struct Color color,
                                float distance);

void RN_AppendTexture(GLuint textureId,
                                float x, float y,
                                float width, float height,
                                float distance);

void RN_render();


#endif