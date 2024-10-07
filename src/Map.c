#include "Map.h"

float squareWidth = BASE_WIDTH / MAP_X; 
float squareHeight = BASE_HEIGHT / MAP_Y;

unsigned char map[MAP_Y][MAP_X] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

void MP_render()
{

    for(int x = 0; x < MAP_X; x++) 
    {
        for(int y = 0; y < MAP_Y; y++)
        {
            if(map[y][x] > 0)
            {
                glColor3ub(127,0,127);
                if(map[y][x] > 1)
                    glColor3ub(0,map[y][x],0);
                if(map[y][x] == 255)
                    glColor3ub(255,0,0);


                glBegin(GL_QUADS);
                glVertex2f(x * squareWidth+1, y * squareHeight+1); // top left
                glVertex2f((x + 1)  * squareWidth-2, y * squareHeight+1); // top right
                glVertex2f((x + 1) * squareWidth-2, (y + 1) * squareHeight-2); // bottom right
                glVertex2f(x * squareWidth+1, (y + 1) * squareHeight-2); // bottom left
                glEnd();
            }
        }
    }
}