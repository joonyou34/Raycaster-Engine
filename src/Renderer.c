#include "Renderer.h"

struct RenderData RN_buffer[RN_BUFFER_CAPACITY];
int RN_bufferSize;

struct RenderData RN_lineToData(float x1, float y1,
                                float x2, float y2,
                                float width,
                                byte R, byte G, byte B, byte A,
                                float distance) {
    struct RenderData ret;
    ret.dataType = RN_LINE;
    ret.distance = distance;

    ret.data = malloc(sizeof(struct LineData));
    struct LineData* data = ret.data;

    data->x1 = x1;
    data->y1 = y1;
    data->x2 = x2;
    data->y2 = y2;

    data->width = width;

    data->R = R;
    data->G = G;
    data->B = B;
    data->A = A;
    
    return ret;
}

struct RenderData RN_textureToData(GLuint textureId,
                                float x, float y,
                                float width, float height,
                                float distance) {
    struct RenderData ret;
    ret.dataType = RN_TEXTURE;
    ret.distance = distance;

    ret.data = malloc(sizeof(struct TextureData));
    struct TextureData* data = ret.data;

    data->textureId = textureId;
    
    data->x = x;
    data->y = y;
    data->width = width;
    data->height = height;

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
    for(int i = 0; i < RN_bufferSize; i++) {
        switch(RN_buffer[i].dataType) {
            case RN_TEXTURE:
                struct TextureData* data = RN_buffer[i].data;
                //TODO render the texture
                break;

            case RN_LINE: {
                struct LineData* data = RN_buffer[i].data;

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

        RN_delete(&RN_buffer[i]);
    }
    
    RN_bufferSize = 0;
}