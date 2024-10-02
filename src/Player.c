#include "Player.h"
#include "System.h"
#include "Map.h"
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

void PL_HitboxRender(struct Player* p) {
    float halfW = p->width * 0.5f, halfH = p->height * 0.5f;

    glColor4ub(255, 0, 0, 127);
    glBegin(GL_QUADS);
    glVertex2f(p->x - halfW, p->y - halfH); // top left
    glVertex2f(p->x + halfW, p->y - halfH); // top right
    glVertex2f(p->x + halfW, p->y + halfH); // bottom right
    glVertex2f(p->x - halfW, p->y + halfH); // bottom left
    glEnd();

    //white dots for tile checks
    int cellXi = (((p->x - halfW)/BASE_WIDTH)*(MAP_X)),
        cellXf = (((p->x + halfW)/BASE_WIDTH)*(MAP_X)),
        cellYi = (((p->y - halfH)/BASE_HEIGHT)*(MAP_Y)),
        cellYf = (((p->y + halfH)/BASE_HEIGHT)*(MAP_Y));
    cellXi = max(cellXi, 0), cellYi = max(cellYi, 0);
    cellXf = min(cellXf, MAP_X-1), cellYf = min(cellYf, MAP_Y-1);
    glColor3ub(255, 255, 255); 
    glPointSize(3);
    glBegin(GL_POINTS);
    glVertex2i(cellXi*squareWidth + squareWidth/2, cellYi*squareWidth + squareWidth/2);
    glVertex2i(cellXf*squareWidth + squareWidth/2, cellYi*squareWidth + squareWidth/2);
    glVertex2i(cellXi*squareWidth + squareWidth/2, cellYf*squareWidth + squareWidth/2);
    glVertex2i(cellXf*squareWidth + squareWidth/2, cellYf*squareWidth + squareWidth/2);
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

//can be optimized to iterate over the outline of the square only (if hitbox will be greater than a single grid)
bool PL_WallCollision(struct Player* p) {
    float halfW = p->width * 0.5f, halfH = p->height * 0.5f;
    int cellXi = (((p->x - halfW)/BASE_WIDTH)*(MAP_X)),
        cellXf = (((p->x + halfW)/BASE_WIDTH)*(MAP_X)),
        cellYi = (((p->y - halfH)/BASE_HEIGHT)*(MAP_Y)),
        cellYf = (((p->y + halfH)/BASE_HEIGHT)*(MAP_Y));
    cellXi = max(cellXi, 0), cellYi = max(cellYi, 0);
    cellXf = min(cellXf, MAP_X-1), cellYf = min(cellYf, MAP_Y-1);
    for(int x = cellXi; x <= cellXf; x++) {
        for(int y = cellYi; y <= cellYf; y++) {
            if(map[y][x])
                return 1;
        }
    }

    return 0;
}

void PL_Move(struct Player* p, struct Camera* cam)
{
    if(p->LEFT_HOLD)
        p->thetaX-= p->sensitivityX*dt;
    if(p->RIGHT_HOLD)
        p->thetaX+= p->sensitivityX*dt;
    fmod(p->thetaX, TWO_PI);
    if(p->thetaX < 0)
        p->thetaX += TWO_PI;

    
    float deltaMove = 0;
    if(p->UP_HOLD)
        deltaMove+=p->v*dt;
    if(p->DOWN_HOLD)
        deltaMove-=p->v*dt;

    
    
    float dx = deltaMove*cosf(p->thetaX);
    float dy = deltaMove*sinf(p->thetaX); 
    p->x += dx;
    if(PL_WallCollision(p))
        p->x -= dx;
    p->y += dy;
    if(PL_WallCollision(p))
        p->y -= dy;
    
    
    CAM_followPlayer(cam, p);
}