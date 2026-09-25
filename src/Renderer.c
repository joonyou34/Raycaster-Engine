#include "Renderer.h"

struct LineData RN_lineBuffer[RN_LINE_CAPACITY];
int RN_lineCount;

struct TextureData RN_textureBuffer[RN_TEXTURE_CAPACITY];
int RN_textureCount;

struct RenderData RN_buffer[RN_BUFFER_CAPACITY];
int RN_bufferSize;

void RN_AppendLine(float x1, float y1,
                                float x2, float y2,
                                float width,
                                byte R, byte G, byte B, byte A,
                                float distance) {

    struct LineData* line = &RN_lineBuffer[RN_lineCount];

    line->x1 = x1;
    line->y1 = y1;
    line->x2 = x2;
    line->y2 = y2;

    line->width = width;

    line->R = R;
    line->G = G;
    line->B = B;
    line->A = A;

    struct RenderData* data = &RN_buffer[RN_bufferSize++];

    data->dataIdx = (RN_lineCount++);
    data->dataType = RN_LINE;
    data->distance = distance;
}

void RN_AppendTexture(GLuint textureId,
                                float x, float y,
                                float width, float height,
                                float distance) {

    struct TextureData* texture = &RN_textureBuffer[RN_textureCount];

    texture->textureId = textureId;

    texture->x = x;
    texture->y = y;

    texture->width = width;
    texture->height = height;

    struct RenderData ret;
    ret.dataType = RN_TEXTURE;
    ret.distance = distance;

    struct RenderData* data = &RN_buffer[RN_bufferSize++];

    data->dataIdx = (RN_textureCount++);
    data->dataType = RN_TEXTURE;
    data->distance = distance;
}

int RN_comp(const void* a, const void* b) {
    float d1 = ((struct RenderData*)a)->distance;
    float d2 = ((struct RenderData*)b)->distance;
    
    if(d1 < d2) return -1;
    return (d1 > d2);
}

void RN_render() {
    //! consider using a different sorting algorithm since this one is weird

    //TODO add ceiling and floor renderers outside of the main render logic

    qsort(RN_buffer, RN_bufferSize, sizeof(struct RenderData), RN_comp);
    for(int i = 0; i < RN_bufferSize; i++) {
        switch(RN_buffer[i].dataType) {
            case RN_TEXTURE:
                struct TextureData* data = &RN_textureBuffer[RN_buffer[i].dataIdx];
                //TODO render the texture
                break;

            case RN_LINE: {
                struct LineData* data = &RN_lineBuffer[RN_buffer[i].dataIdx];

                glLineWidth(data->width);
                glColor4ub(data->R, data->G, data->B, data->A);
                //! consider optimizng this so you don't call glBegin and glEnd for every single object/line
                glBegin(GL_LINES);
                glVertex2f(data->x1, data->y1);
                glVertex2f(data->x2, data->y2);
                glEnd();
                break;
            }

            default:
                fprintf(stderr, "wrong or unimplemented render object type");
                exit(1);
        }
    }
    
    RN_bufferSize = 0;
    RN_lineCount = 0;
    RN_textureCount = 0;
}