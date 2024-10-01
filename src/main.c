/**
* @Joonyou34
* @parlerler
* @Evildot1
* @WisdomCasual
* @CodingPanda166
*/

//list of prefixes:
//PL_ : player-related functions
//MP_ : map-related functions
//CAM_ : camera-related functions
#include "Global.h"
#include "Player.h"
#include "Map.h"
#include "System.h"
#include "Camera.h"

struct Player player1;
struct Camera player1Cam;


void keyPress(unsigned char key, int x, int y) {
    PL_Controls(&player1, key, 1);
}

void keyRelease(unsigned char key, int x, int y) {
    PL_Controls(&player1, key, 0);
}

void redisplayWindow(int windowNum) {
    glutSetWindow(windowNum);
    glutPostRedisplay();
}

//top-down display
void TD_display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    PL_render(&player1);
    MP_render();
    PL_HitboxRender(&player1); //for debugging purposes

    glutSwapBuffers();
}

//raycaster display
void RC_display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    CAM_Render(&player1Cam);

    glutSwapBuffers();
}

void initWindow(int width, int height, const char* name, void (*displayFunction)(void)) {
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(width, height);
    glutCreateWindow(name);
    glutDisplayFunc(displayFunction);

    glClearColor(0, 0, 0, 0);
    gluOrtho2D(0, BASE_WIDTH, BASE_HEIGHT, 0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void init() {
    PL_Init(&player1);
    CAM_init(&player1Cam);
    CAM_followPlayer(&player1Cam, &player1);
    glutSetWindow(2);
}


void update(int value) {
    updateDT();
    PL_Move(&player1, &player1Cam);
    
    redisplayWindow(1);
    redisplayWindow(2);
    glutTimerFunc(mSPF, update, 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);

    initWindow(BASE_WIDTH, BASE_HEIGHT, "top-down smiling Bob", TD_display);
    initWindow(BASE_WIDTH, BASE_HEIGHT, "raycasting Bob", RC_display);

    init();
    glutKeyboardFunc(keyPress);
    glutKeyboardUpFunc(keyRelease);
    glutTimerFunc(0, update, 0);
    glutMainLoop();
    return 0;
}