#include "Player.h"
#include "System.h"
#include "Map.h"
#include "Global.h"
#include "Entity.h"

int entityCount = 0;
void create_Entity(struct Entity **E, float x, float y, float width, float height, float angle)
{
    if (x > BASE_WIDTH)
        x = BASE_WIDTH / 2;
    if (y > BASE_HEIGHT)
        y = BASE_HEIGHT / 2;
    if (x < 0)
        x = 0;
    if (y < 0)
        y = 0;
    struct Entity *newEntity = (struct Entity *)malloc(sizeof(struct Entity));
    newEntity->id = entityCount;
    newEntity->x = x;
    newEntity->y = y;
    newEntity->width = width;
    newEntity->height = height;
    newEntity->thetaX = angle;
    E[entityCount] = newEntity;
    (entityCount)++;
}

void ET_Render(struct Entity **E)
{
    for (int i = 0; i < entityCount; i++)
    {
        struct Entity *curEntity = E[i];

        glColor3ub(100, 180, 30);
        glBegin(GL_TRIANGLES);
        glVertex2i(curEntity->x + 10, curEntity->y);
        glVertex2i(curEntity->x - 10, curEntity->y);
        glVertex2i(curEntity->x, curEntity->y + 20);
        glEnd();
    }
}

unsigned char ET_grid[MAP_Y][MAP_X] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

void et_map(struct Entity **E, unsigned char ET_grid[MAP_Y][MAP_X])
{
    for (int i = 0; i < entityCount; i++)
    {
        struct Entity *curEntity = E[i];
        int map_X = (curEntity->x / BASE_WIDTH) * MAP_X;
        int map_Y = (curEntity->y / BASE_HEIGHT) * MAP_Y;
        ET_grid[map_Y][map_X] = curEntity->id;
    }
}