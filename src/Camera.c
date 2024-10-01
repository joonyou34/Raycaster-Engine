#include "Camera.h"
#include "System.h"
#include "Map.h"

void CAM_init(struct Camera* cam) {
    cam->posX = BASE_WIDTH / 2.f;
    cam->posY = BASE_HEIGHT / 2.f;
    cam->dirX = -1, cam->dirY = 0;
    cam->planeX = 0, cam->planeY = 0.66;
    cam->FOV = RAD_90;
}

struct HitData CAM_Ray_Cast(double posX, double posY, double rayDirX, double rayDirY){

    int curX = (int)posX, curY = (int)posY;

    //length of ray from current position to next x or y-side
    double rayLenX, rayLenY;

    //length of ray from one x or y-side to next x or y-side
    double deltaDistX = (rayDirX == 0) ? 1e30 : abs(1 / rayDirX);
    double deltaDistY = (rayDirY == 0) ? 1e30 : abs(1 / rayDirY);
    
    double perpWallDist;

    //what direction to step in x or y-direction (either +1 or -1)
    int stepX;
    int stepY;

    int hit = 0; //was there a wall hit?
    int side; //was a NS or a EW wall hit?

    if (rayDirX < 0)
        stepX = -1, rayLenX = (posX - curX) * deltaDistX;
    else
        stepX = 1, rayLenX = (curX + 1.0 - posX) * deltaDistX;

    if (rayDirY < 0)
        stepY = -1, rayLenY = (posY - curY) * deltaDistY;
    else
        stepY = 1, rayLenY = (curY + 1.0 - posY) * deltaDistY;

    while(!hit){
        if(rayLenX < rayLenY)
            rayLenX += deltaDistX, curX += stepX, side = 0;
        else
            rayLenY += deltaDistY, curY += stepY, side = 1;
        
        // printf("%d %d\n", curX, curY);
        if(map[curY][curX] >= 1 && map[curY][curX] < 255) hit = 1;
        // else
        //     map[curY][curX] = 255;
    }
        // printf("\n");

    struct HitData blockHit;
    blockHit.hit_block_x = curX;
    blockHit.hit_block_y = curY;

    if(side == 0) perpWallDist = (rayLenX - deltaDistX);
    else perpWallDist = (rayLenY - deltaDistY);

    if(map[curY][curX] == 1)
        map[curY][curX] = min(perpWallDist*10 + 2, 254);
    else map[curY][curX] = min(map[curY][curX], min(perpWallDist*10 + 2, 254));

    blockHit.distance = perpWallDist;
    blockHit.side = side;

    return blockHit;
}

void CAM_Render(struct Camera* cam){

    for(int i = 0; i < MAP_X; i++)
        for(int j = 0; j < MAP_Y; j++)
            if(map[j][i] > 0 && map[j][i] < 255) map[j][i] = 1;
            else map[j][i] = 0;

    static int cnt = 0;
    cnt++;
    // if(cnt % 60 == 0)
    //     printf("PLANE: %f %f DIR: %f %f\n", cam->planeX, cam->planeY, cam->dirX, cam->dirY);

    for(int x = 0; x <= BASE_WIDTH; x++) {
        double cameraX = ((2 * x) / (double)BASE_WIDTH) - 1; //x-coordinate in camera space
        struct HitData blockHit = CAM_Ray_Cast(cam->posX/squareWidth, cam->posY/squareHeight, cam->dirX + cam->planeX * cameraX, cam->dirY + cam->planeY * cameraX);

        // if(cnt % 1000 == 0)
        //     printf("%f %d %d %d rayDir: %f %f\n", blockHit.distance, blockHit.hit_block_x, blockHit.hit_block_y, blockHit.side, cam->dirX + cam->planeX * cameraX, cam->dirY + cam->planeY * cameraX);
        
        double dx = cam->dirX + cam->planeX * cameraX, dy = cam->dirY + cam->planeY * cameraX;
        double dv = sqrt(dx*dx+dy*dy);
        dx/=dv, dy/=dv;
        dx*=blockHit.distance, dy *= blockHit.distance;
        


        glColor3ub(0, 0, 255 - blockHit.side * 155);
        glBegin(GL_LINES);
        double height = min(BASE_HEIGHT / blockHit.distance, BASE_HEIGHT-1);
        glVertex2i(x, BASE_HEIGHT/2 - height/2);
        glVertex2i(x, BASE_HEIGHT/2 + height/2);
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

void CAM_followPlayer(struct Camera* cam, struct Player* p) {
    cam->posX = p->x;
    cam->posY = p->y;
    CAM_setDirection(cam, p->thetaX);
}