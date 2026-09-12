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
//DEBUG_: debug feature
#include "Global.h"
#include "Player.h"
#include "Map.h"
#include "System.h"
#include "Camera.h"

struct Player player1;
struct Camera player1Cam;


void specialKeyPress(int key, int mouseX, int mouseY) {
    #ifdef DEBUG_FEATURES
        switch(key) {
            case GLUT_KEY_F1:
                DEBUG_showHitboxs ^= 1;
                break;
            case GLUT_KEY_F2:
                DEBUG_showRaycasterRays ^= 1;
                break;
            case GLUT_KEY_F3:
                DEBUG_showTileDistance ^= 1;
                break;
        }
    #endif
}

void specialKeyRelease(int key, int mouseX, int mouseY) {
    //! DOES NOTHING RIGHT NOW
}

void keyPress(unsigned char key, int mouseX, int mouseY) {
    PL_Controls(&player1, key, 1);
}

void keyRelease(unsigned char key, int mouseX, int mouseY) {
    PL_Controls(&player1, key, 0);
}

void redisplayWindow(int windowNum) {
    glutSetWindow(windowNum);
    glutPostRedisplay();
}

#ifdef DEBUG_FEATURES
//top-down display
void TD_display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    PL_render(&player1);
    MP_render();
    
    if(DEBUG_showHitboxs)
        PL_HitboxRender(&player1); //for debugging purposes

    // render raycaster rays
    for(int i = 0; i < stkPtr; i++) {
        glColor3ub(255, 0, 0);
        glBegin(GL_LINES);
        glVertex2f(stkX1[i], stkY1[i]);
        glVertex2f(stkX2[i], stkY2[i]);
        glEnd();
    }

    glutSwapBuffers();
}
#endif


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

    #ifdef DEBUG_FEATURES
        glutSetWindow(2);
    #else
        glutSetWindow(1);
    #endif
        
}


void update(int value) {
    updateDT();
    PL_Move(&player1, &player1Cam);
    
    redisplayWindow(1);
    #ifdef DEBUG_FEATURES
        redisplayWindow(2);
    #endif
    glutTimerFunc(mSPF, update, 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);

    #ifdef DEBUG_FEATURES
        initWindow(BASE_WIDTH, BASE_HEIGHT, "top-down smiling Bob", TD_display);
    #endif
    initWindow(BASE_WIDTH, BASE_HEIGHT, "raycasting Bob", RC_display);

    init();
    glutKeyboardFunc(keyPress);
    glutKeyboardUpFunc(keyRelease);
    glutSpecialFunc(specialKeyPress);
    glutSpecialUpFunc(specialKeyRelease);
    glutTimerFunc(0, update, 0);
    glutMainLoop();
    return 0;
}