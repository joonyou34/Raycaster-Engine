#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>


#define RN_TEXTURE 0
#define RN_LINE 1
struct RenderData {
    byte dataType;
    void* data;
};

struct RenderData RN_lineToData(float x1, float y1,
                                float x2, float y2,
                                byte R, byte G, byte B, byte A) {
    struct RenderData ret;
    ret.dataType = RN_LINE;

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
                                float width, float height) {
    struct RenderData ret;
    ret.dataType = RN_TEXTURE;

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

int main() {
    struct RenderData rd1 = RN_lineToData(1, 2, 3, 4, 1, 2, 3, 4);
    struct RenderData rd2 = RN_textureToData(1, 2, 3, 4, 5);

    printf("%f %f %f %f %d %d %d %d\n",
        *((float*)rd1.data),
        *((float*)rd1.data + 1),
        *((float*)rd1.data + 2),
        *((float*)rd1.data + 3),

        *((byte*)((float*)rd1.data + 4)),
        *((byte*)((float*)rd1.data + 4) + 1),
        *((byte*)((float*)rd1.data + 4) + 2),
        *((byte*)((float*)rd1.data + 4) + 3)
    );


    printf("%d %f %f %f %f\n",
        *((GLuint*)rd2.data),

        *((float*)((GLuint*)rd2.data + 1)),
        *((float*)((GLuint*)rd2.data + 1) + 1),
        *((float*)((GLuint*)rd2.data + 1) + 2),
        *((float*)((GLuint*)rd2.data + 1) + 3)
    );
    

    RN_delete(&rd1);
    RN_delete(&rd2);
}