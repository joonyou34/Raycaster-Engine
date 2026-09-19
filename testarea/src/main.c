#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>


int main(int argc, char* argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Test");

    GLfloat range[2];
    GLfloat granularity;

    glGetFloatv(GL_LINE_WIDTH_RANGE, range);
    glGetFloatv(GL_LINE_WIDTH_GRANULARITY, &granularity);

    printf("Range: %f - %f\n", range[0], range[1]);
    printf("Granularity: %f\n", granularity);

}