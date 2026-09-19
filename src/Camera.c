#include "Camera.h"
#include "System.h"
#include "Map.h"
#include "Renderer.h"

struct HitData CAM_Ray_Cast(float posX, float posY, float rayDirX, float rayDirY){
    struct HitData ret;

    ret.hit_block_x = (int)posX;
    ret.hit_block_y = (int)posY;

    float totalDistX;
    float totalDistY;

    float deltaDistX = fabsf(1/rayDirX);
    float deltaDistY = fabsf(1/rayDirY);

    int stepX;
    int stepY;


    if(rayDirX < 0) {
        stepX = -1;
        totalDistX = (posX-ret.hit_block_x)*deltaDistX;
    }
    else {
        stepX = 1;
        totalDistX = (ret.hit_block_x + 1.f - posX)*deltaDistX;
    }
    if(rayDirY < 0) {
        stepY = -1;
        totalDistY = (posY-ret.hit_block_y)*deltaDistY;
    }
    else {
        stepY = 1;
        totalDistY = (ret.hit_block_y + 1.f - posY)*deltaDistY;
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

            #ifdef DEBUG_FEATURES
                // setting tile value based on distance
                if(DEBUG_showTileDistance)
                    map[ret.hit_block_y][ret.hit_block_x] = min(((int)(ret.distance*10))+2, 255);
            #endif

            break;
        }
    }

    if(ret.side == 0)
        ret.distance = (totalDistX-deltaDistX);
    else
        ret.distance = (totalDistY-deltaDistY);
    
    return ret;
}

void CAM_draw(struct Camera* cam){
    #ifdef DEBUG_FEATURES
        static bool needCleanup = 0;
        if(needCleanup || DEBUG_showTileDistance) {
            // resets the map tiles to 1 (assuming tile values were modified to distance)
            for(int i = 0; i < MAP_X; i++) {
                for(int j = 0; j < MAP_Y; j++)
                    if(map[j][i])
                        map[j][i] = 1;
            }
        }
        stkPtr = 0;
    #endif

    float xOff = 0;
    float yOff = 0;

    float scaleX = screenWidth  / (float)cam->baseWidth;
    float scaleY = screenHeight / (float)cam->baseHeight;

    float scale;
    float effectiveHeight;
    if(scaleY < scaleX) {
        scale = scaleY;
        
        float deltaWidth = (scaleX - scaleY) * cam->baseWidth;

        xOff = deltaWidth/2.f + (screenWidth-deltaWidth)*cam->screenTopLeftX;
        yOff = screenHeight * cam->screenTopLeftY;

        effectiveHeight = cam->screenSize * screenHeight;
    } else {
        scale = scaleX;
        
        float deltaHeight = (scaleY - scaleX) * cam->baseHeight;
        
        xOff = screenWidth * cam->screenTopLeftX;
        yOff = deltaHeight/2.f + (screenHeight-deltaHeight)*cam->screenTopLeftY;

        effectiveHeight = cam->screenSize * (screenHeight - deltaHeight);
    }

    scale *= cam->screenSize;

    int lineScale = ceilf(scale);
    xOff += (lineScale-1)/2;

    for(int ray = 0; ray < cam->baseWidth; ray++) { // cast the rays
        float camX = 2*ray/(float)cam->baseWidth -1;
        float rayDirX = cam->dirX + cam->planeX * camX;
        float rayDirY = cam->dirY + cam->planeY * camX;

        struct HitData hitdata = CAM_Ray_Cast(cam->posX/squareWidth, cam->posY/squareHeight, rayDirX, rayDirY);

        float lineHeight = effectiveHeight/max(hitdata.distance, 1.f);
        float drawStart = yOff + (effectiveHeight - lineHeight)/2.f;
        float drawEnd = yOff + (effectiveHeight + lineHeight)/2.f;

        #ifdef DEBUG_FEATURES
            if(DEBUG_showRaycasterRays) { // debugging raycasting rays
                stkX1[stkPtr] = cam->posX;
                stkY1[stkPtr] = cam->posY;
                float dv = sqrt(rayDirX*rayDirX + rayDirY*rayDirY);
                float dx = rayDirX, dy = rayDirY;
                dx *= hitdata.distance*squareHeight, dy *= hitdata.distance*squareHeight;
                dx += cam->posX, dy += cam->posY;
                stkX2[stkPtr] = dx;
                stkY2[stkPtr] = dy;
                stkPtr++;
            }

            needCleanup = DEBUG_showTileDistance;
        #endif

        RN_append(RN_lineToData(
            xOff + scale*ray, drawStart,
            xOff + scale*ray, drawEnd,
            lineScale,
            0, 0, (127 << hitdata.side), 255,
            hitdata.distance
        ));
    }
}

void CAM_setDirection(struct Camera* cam, float theta) {
    cam->dirX = cosf(theta);
    cam->dirY = sinf(theta);
    float planeSize = tanf(cam->FOV/2.f); //FOV = 2*atan(planeSize), planeSize = tan(FOV/2)
    cam->planeX = -cam->dirY * planeSize; 
    cam->planeY = cam->dirX * planeSize;
}

void CAM_init(struct Camera* cam) {
    cam->screenTopLeftX = 0.f;
    cam->screenTopLeftY = 0.f;
    cam->screenSize = 1.f;

    cam->baseWidth = DEFAULT_BASE_WIDTH;
    cam->baseHeight = DEFAULT_BASE_HEIGHT;

    cam->posX = DEFAULT_BASE_WIDTH / 2.f;
    cam->posY = DEFAULT_BASE_HEIGHT / 2.f;
    cam->FOV = RAD_90;
    CAM_setDirection(cam, 0);
}

void CAM_followPlayer(struct Camera* cam, struct Player* p) {
    cam->posX = p->x;
    cam->posY = p->y;
    CAM_setDirection(cam, p->thetaX);
}