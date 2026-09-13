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
};

struct HitData{ // *not hitman related*
    int  side;
    int   hit_block_x, hit_block_y;
    float distance;
};

void CAM_init(struct Camera* cam);
struct HitData CAM_Ray_Cast(float posX, float posY, float rayDirX, float rayDirY);
void CAM_Render(struct Camera* cam);
void CAM_setDirection(struct Camera* cam, float theta);
void CAM_followPlayer(struct Camera* cam, struct Player* p);

#endif