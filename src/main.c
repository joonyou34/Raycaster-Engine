/**
* @Joonyou34
* @parlerler
* @Evildot1
*/

//list of prefixes:
//PL_ : player-related functions
//MP_ : map-related functions

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//absolute width
#define BASE_WIDTH 800
//absolute height
#define BASE_HEIGHT 600
#define PI 3.1415926f
#define TWO_PI 6.2831852f
#define MAP_X 16
#define MAP_Y 12
typedef boolean bool;

unsigned int mSPF = 16;

unsigned int lastTime = 0;
//deltaTime in ms
unsigned int dtMs = 0;
//deltaTime in seconds
float dt = 0;

// size of each square of the grid
float squareWidth = BASE_WIDTH / MAP_X; 
float squareHeight = BASE_HEIGHT / MAP_Y;

// the grid
unsigned char map[MAP_Y][MAP_X] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

struct Player {
    float x, y;
    float thetaX;
    float v;
    float sensitivityX;
    float width, height;
    char UP_KEY, DOWN_KEY, LEFT_KEY, RIGHT_KEY;
    bool UP_HOLD, DOWN_HOLD, LEFT_HOLD, RIGHT_HOLD;
} player1;

void updateDT() {
    unsigned int curtime = glutGet(GLUT_ELAPSED_TIME);
    dtMs = curtime-lastTime;
    lastTime = curtime;
    dt = dtMs/1000.f;
}

void changeFPS(unsigned short FPS) {
    mSPF = 1000u/FPS;
}

void drawCircle(float cx, float cy, float r, int num_segments) {
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i <= num_segments; i++) {
        float theta = 2.f * PI * i / num_segments;
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}

void PL_Controls(struct Player* p, unsigned char key, bool pressed) {
    if(key == p->UP_KEY)
        p->UP_HOLD = pressed;
    if(key == p->DOWN_KEY)
        p->DOWN_HOLD = pressed;
    if(key == p->LEFT_KEY)
        p->LEFT_HOLD = pressed;
    if(key == p->RIGHT_KEY)
        p->RIGHT_HOLD = pressed;
}


// the bob function (very important) (DONT DELETE)
void PL_render(struct Player* p) {
    

    const int lineLen = 75;
    glColor3ub(255, 0, 0); 
    glBegin(GL_LINES);
    glVertex2i(p->x, p->y);
    glVertex2i(p->x + lineLen*cosf(p->thetaX), p->y + lineLen*sinf(p->thetaX));
    glEnd();

    glColor3ub(235, 180, 30);
    glBegin(GL_TRIANGLES);
    glVertex2i(p->x - 30*cosf(p->thetaX), p->y - 50*sinf(p->thetaX)); 
    glVertex2i(p->x - 30*cosf(p->thetaX), p->y);     
    glVertex2i(p->x-5*cosf(p->thetaX), p->y - 30*sinf(p->thetaX));


    glVertex2i(p->x + 30*cosf(p->thetaX), p->y - 50*sinf(p->thetaX)); 
    glVertex2i(p->x + 30*cosf(p->thetaX), p->y);      
    glVertex2i(p->x+5*cosf(p->thetaX), p->y - 30*sinf(p->thetaX));    
    glEnd();


    glColor3ub(255, 200, 50);
    drawCircle(p->x, p->y, 20, 20);
    glEnd();

    glColor3ub(0, 0, 0); 
    glPointSize(3);
    glBegin(GL_POINTS);
    glVertex2i(p->x-10*cosf(p->thetaX), p->y-15*sinf(p->thetaX));
    glVertex2i(p->x+10*cosf(p->thetaX), p->y-15*sinf(p->thetaX));
    glEnd();

    glColor3ub(127, 0, 25); 
    glBegin(GL_TRIANGLES);
    glVertex2i(p->x - 7*cosf(p->thetaX), p->y + 5*sinf(p->thetaX)); 
    glVertex2i(p->x + 7*cosf(p->thetaX), p->y + 5*sinf(p->thetaX));     
    glVertex2i(p->x , p->y + 20*sinf(p->thetaX));  
    glEnd();
}

// initializes all important player variables
void PL_Init(struct Player* p) {
    p->x = BASE_WIDTH/2.f;
    p->y = BASE_HEIGHT/2.f;
    p->v = 200.f;
    p->sensitivityX = 2.f;
    p->thetaX = 0.f;
    p->UP_HOLD = 0;
    p->DOWN_HOLD = 0;
    p->LEFT_HOLD = 0;
    p->RIGHT_HOLD = 0;
    p->DOWN_KEY = 's';
    p->UP_KEY = 'w';
    p->LEFT_KEY = 'a';
    p->RIGHT_KEY = 'd';
    p->width = 40;
    p->height = 40;
}

bool PL_WallCollision(struct Player* p) {
    int cellX = round((p->x/BASE_WIDTH)*(MAP_X-1)), cellY = round((p->y/BASE_HEIGHT)*(MAP_Y-1));
    float halfW = p->width * 0.5f, halfH = p->height * 0.5f;

    int limI = min(cellY+2, MAP_Y);
    int limJ = min(cellX+2, MAP_X);
    for(int y = max(cellY-1, 0); y < limI; y++) {
        for(int x = max(cellX-1, 0); x < limJ; x++) {
            if (map[y][x]) {
                float wallX = x * squareWidth;
                float wallY = y * squareHeight;
                if (p->x - halfW < wallX + squareWidth &&
                    p->x + halfW > wallX &&
                    p->y - halfH < wallY + squareHeight &&
                    p->y + halfH > wallY)
                    return 1;
            }
        }
    }
    return 0;
}

void PL_Move(struct Player* p)
{
    if(p->LEFT_HOLD)
        p->thetaX-= p->sensitivityX*dt;
    if(p->RIGHT_HOLD)
        p->thetaX+= p->sensitivityX*dt;
    fmod(p->thetaX, TWO_PI);
    if(p->thetaX < 0)
        p->thetaX += TWO_PI;

    
    float d = 0;
    if(p->UP_HOLD)
        d+=p->v*dt;
    if(p->DOWN_HOLD)
        d-=p->v*dt;
    
    float dx = d*cosf(p->thetaX);
    float dy = d*sinf(p->thetaX); 
    p->x += dx;
    if(PL_WallCollision(p))
        p->x -= dx;
    p->y += dy;
    if(PL_WallCollision(p))
        p->y -= dy;
}


void MP_render()
{

    for(int x = 0; x < MAP_X; x++) 
    {
        for(int y = 0; y < MAP_Y; y++)
        {
            if(map[y][x] > 0)
            {
                glColor3ub(127,0,127);
                glBegin(GL_QUADS);
                glVertex2f(x * squareWidth+1, y * squareHeight+1); // bottom left
                glVertex2f((x + 1)  * squareWidth-1, y * squareHeight+1); // bottom right
                glVertex2f((x + 1) * squareWidth-1, (y + 1) * squareHeight-1); // top right
                glVertex2f(x * squareWidth+1, (y + 1) * squareHeight-1); // top left
                glEnd();
            }
        }
    }
}


void keyPress(unsigned char key, int x, int y) {
    PL_Controls(&player1, key, 1);
}

void keyRelease(unsigned char key, int x, int y) {
    PL_Controls(&player1, key, 0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    PL_render(&player1);
    MP_render();
    glutSwapBuffers();
}

void init() {
    glClearColor(0, 0, 0, 0);
    gluOrtho2D(0, BASE_WIDTH, BASE_HEIGHT, 0);
    PL_Init(&player1);
}

void update(int value) {
    updateDT();
    PL_Move(&player1);
    
    glutPostRedisplay();
    glutTimerFunc(mSPF, update, 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(BASE_WIDTH,BASE_HEIGHT);
    glutCreateWindow("Smiling Bob");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyPress);
    glutKeyboardUpFunc(keyRelease);
    glutTimerFunc(0, update, 0);
    glutMainLoop();
    return 0;
}