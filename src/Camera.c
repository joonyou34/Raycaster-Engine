#include "Camera.h"
#include "System.h"
#include "Map.h"

struct HitData CAM_Ray_Cast(double posX, double posY, double rayDirX, double rayDirY){
    struct HitData ret;

    ret.hit_block_x = (int)posX;
    ret.hit_block_y = (int)posY;

    double totalDistX;
    double totalDistY;

    double deltaDistX = fabs(1/rayDirX);
    double deltaDistY = fabs(1/rayDirY);

    int stepX;
    int stepY;


    if(rayDirX < 0) {
        stepX = -1;
        totalDistX = (posX-ret.hit_block_x)*deltaDistX;
    }
    else {
        stepX = 1;
        totalDistX = (ret.hit_block_x + 1.0 - posX)*deltaDistX;
    }
    if(rayDirY < 0) {
        stepY = -1;
        totalDistY = (posY-ret.hit_block_y)*deltaDistY;
    }
    else {
        stepY = 1;
        totalDistY = (ret.hit_block_y + 1.0 - posY)*deltaDistY;
    }

    while(1) {
        if(totalDistX < totalDistY) {
            totalDistX += deltaDistX;
            ret.hit_block_x += stepX;
            ret.side = 0;
        }
        else if(totalDistX > totalDistY) {
            totalDistY += deltaDistY;
            ret.hit_block_y += stepY;
            ret.side = 1;
        }
        else{
            totalDistX += deltaDistX;
            ret.hit_block_x += stepX;
            totalDistY += deltaDistY;
            ret.hit_block_y += stepY;
            ret.side = 0;
        }

        if(map[ret.hit_block_y][ret.hit_block_x]) {
            if(ret.side == 0)
                ret.distance = (totalDistX-deltaDistX);
            else
                ret.distance = (totalDistY-deltaDistY);
            map[ret.hit_block_y][ret.hit_block_x] = min(((int)(ret.distance*10))+2, 255);
            break;
        }
    }

    if(ret.side == 0)
        ret.distance = (totalDistX-deltaDistX);
    else
        ret.distance = (totalDistY-deltaDistY);
    
    return ret;
}

void CAM_Render(struct Camera* cam){
    for(int i = 0; i < MAP_X; i++) {
        for(int j = 0; j < MAP_Y; j++)
            if(map[j][i])
                map[j][i] = 1;
    }
    for(int ray = 0; ray < BASE_WIDTH; ray++) {
        double camX = 2*ray/(double)BASE_WIDTH -1;
        double rayDirX = cam->dirX + cam->planeX * camX;
        double rayDirY = cam->dirY + cam->planeY * camX;

        struct HitData hitdata = CAM_Ray_Cast(cam->posX/squareWidth, cam->posY/squareHeight, rayDirX, rayDirY);

        int lineHeight = (int)(BASE_HEIGHT/hitdata.distance);
        int drawStart = ((BASE_HEIGHT - lineHeight)>>1);
        int drawEnd = ((BASE_HEIGHT + lineHeight)>>1);

        stkX1[stkPtr] = cam->posX;
        stkY1[stkPtr] = cam->posY;
        double dv = sqrt(rayDirX*rayDirX + rayDirY*rayDirY);
        double dx = rayDirX, dy = rayDirY;
        dx *= hitdata.distance*squareHeight, dy *= hitdata.distance*squareHeight;
        dx += cam->posX, dy += cam->posY;
        stkX2[stkPtr] = dx;
        stkY2[stkPtr] = dy;
        stkPtr++;

        glColor3ub(0, 0, (127<<hitdata.side));
        glBegin(GL_LINES);
        glVertex2d(ray, drawStart);
        glVertex2d(ray, drawEnd);
        glEnd();
    }
}

void CAM_setDirection(struct Camera* cam, double theta) {
    cam->dirX = cos(theta);
    cam->dirY = sin(theta);
    double planeSize = tan(cam->FOV/2.0); //FOV = 2*atan(planeSize), planeSize = tan(FOV/2)
    cam->planeX = -cam->dirY * planeSize; 
    cam->planeY = cam->dirX * planeSize;
}

void CAM_init(struct Camera* cam) {
    cam->posX = BASE_WIDTH / 2.f;
    cam->posY = BASE_HEIGHT / 2.f;
    cam->FOV = RAD_90;
    CAM_setDirection(cam, 0);
}

void CAM_followPlayer(struct Camera* cam, struct Player* p) {
    cam->posX = p->x;
    cam->posY = p->y;
    CAM_setDirection(cam, p->thetaX);
}