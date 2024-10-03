#include "Map.h"
struct Entity
{
    int id;
    float x, y;
    float width, height;
    float thetaX;
};
extern int entityCount;
void create_Entity(struct Entity **E, float x, float y, float width, float height, float angle);
void ET_Render(struct Entity **E);
void et_map(struct Entity **E, unsigned char ET_grid[MAP_Y][MAP_X]);