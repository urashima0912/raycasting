#ifndef RC_MAP_H
#define RC_MAP_H

#include <stdint.h>
#include <raylib.h>
#include "tile.h"
#include "sprite.h"
#include "ray.h"

#define L0_ROW      10
#define L0_COLUMN   10
#define NUM_SPRITES 1

typedef enum LevelType_t {
    LEVEL_0 = 0,
}LevelType_t;

typedef struct Map_t {
    LevelType_t type;
    Vector2     size;
    Texture     texture;
    Tile_t      **tiles;
    Sprite_t    *sprites[NUM_SPRITES];
    float       zBuffer[NUM_RAYS];
}Map_t;

Map_t   *initMap(LevelType_t levelType);
bool    isCollisionMap(const Map_t *const map, Vector2 position);
void    freeMap(Map_t **ptrMap);

#endif //RC_MAP_H
