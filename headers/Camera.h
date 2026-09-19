#ifndef CAMERA
#define CAMERA

#include "Global.h"
#include "Player.h"

struct Player;

struct Camera {
    float posX, posY;
    float FOV;
    float dirX, dirY; 
    float planeX, planeY;

    float screenTopLeftX, screenTopLeftY; // from 0.0 to 1.0
    float screenSize; // from 0.0 to 1.0 --> the percentage of the screen filled
    int baseWidth, baseHeight; // the selected resoluton (before scaling up to screen)
};

struct HitData{ // *not hitman related*
    int side;
    int hit_block_x, hit_block_y;
    float distance;
};

void CAM_init(struct Camera* cam);
struct HitData CAM_Ray_Cast(float posX, float posY, float rayDirX, float rayDirY);
void CAM_draw(struct Camera* cam);
void CAM_setDirection(struct Camera* cam, float theta);
void CAM_followPlayer(struct Camera* cam, struct Player* p);

#endif