/**
 * @Joonyou34
 * @parlerler
 * @Evildot1
 * @WisdomCasual
 * @CodingPanda166
 */

// list of prefixes:
// PL_ : player-related functions
// MP_ : map-related functions
#include "Global.h"
#include "Player.h"
#include "Map.h"
#include "System.h"

struct Player player1;

void keyPress(unsigned char key, int x, int y)
{
    PL_Controls(&player1, key, 1);
}

void keyRelease(unsigned char key, int x, int y)
{
    PL_Controls(&player1, key, 0);
}

void mouseMovement(int x, int y)
{
    PL_Rotate(&player1, x, y);
    mouseX = x;
    mouseY = y;
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    PL_render(&player1);
    MP_render();
    PL_HitboxRender(&player1); // for debugging purposes
    glutSwapBuffers();
}

void init()
{
    glClearColor(0, 0, 0, 0);
    gluOrtho2D(0, BASE_WIDTH, BASE_HEIGHT, 0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    PL_Init(&player1);
}

void update(int value)
{
    updateDT();
    PL_Move(&player1);

    glutPostRedisplay();
    glutTimerFunc(mSPF, update, 0);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(BASE_WIDTH, BASE_HEIGHT);
    glutCreateWindow("Smiling Bob");
    init();
    glutPassiveMotionFunc(mouseMovement);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyPress);
    glutKeyboardUpFunc(keyRelease);
    glutTimerFunc(0, update, 0);
    glutMainLoop();
    return 0;
}