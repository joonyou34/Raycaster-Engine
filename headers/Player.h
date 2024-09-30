#ifndef PLAYER
#define PLAYER
#include "Global.h"

struct Player
{
    float x, y;
    float thetaX;
    float v;
    float sensitivityX;
    float width, height;
    char UP_KEY, DOWN_KEY, LEFT_KEY, RIGHT_KEY;
    bool UP_HOLD, DOWN_HOLD, LEFT_HOLD, RIGHT_HOLD;
};

void PL_Controls(struct Player *p, unsigned char key, bool pressed);
void PL_render(struct Player *p);
void PL_HitboxRender(struct Player *p);
void PL_Init(struct Player *p);
bool PL_WallCollision(struct Player *p);
void PL_Move(struct Player *p);
void PL_Rotate(struct Player *p, int x, int y);
#endif