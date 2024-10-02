#ifndef CAMERA
#define CAMERA

#include "Global.h"
#include "Player.h"

struct Player;

struct Camera {
    float posX, posY;
    double FOV;
    double dirX, dirY; 
    double planeX, planeY;
};

struct HitData{ // *not hitman related*
    int  side;
    int   hit_block_x, hit_block_y;
    double distance;
};

void CAM_init(struct Camera* cam);
struct HitData CAM_Ray_Cast(double posX, double posY, double rayDirX, double rayDirY);
void CAM_Render(struct Camera* cam);
void CAM_setDirection(struct Camera* cam, double theta);
void CAM_followPlayer(struct Camera* cam, struct Player* p);

#endif