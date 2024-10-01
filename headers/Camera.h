#ifndef CAMERA
#define CAMERA

#include "Global.h"
#include "Player.h"

struct Player;

struct Camera {
    float posX, posY; //player position
    double FOV;
    double dirX, dirY; //direction vector
    double planeX, planeY; //the 2d raycaster version of camera plane
};

struct HitData{ // *not hitman related*
    bool  side;
    int   hit_block_x, hit_block_y;
    double distance;
};

void CAM_init(struct Camera* cam);
struct HitData CAM_Ray_Cast(double posX, double posY, double rayDirX, double rayDirY);
void CAM_Render(struct Camera* cam);
void CAM_setDirection(struct Camera* cam, double theta);
void CAM_followPlayer(struct Camera* cam, struct Player* p);

#endif