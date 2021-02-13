#ifndef RC_MAP_H
#define RC_MAP_H

#include <stdint.h>
#include <raylib.h>
#include "tile.h"
#include "sprite.h"
#include "ray.h"

#define NUM_SPRITES 1

#ifdef __cplusplus
extern "C" {
#endif

typedef enum WallType_t {
    WALL_EMPTY = 0,
    WALL_1,
    WALL_2,
    WALL_3,
    WALL_4,
    WALL_5,
}WallType_t;

typedef enum FloorType_t {
    FLOOR_EMPTY = 0,
    FLOOR_1,
}FloorType_t;

typedef enum LevelType_t {
    LEVEL_0 = 0,
} LevelType_t;

typedef struct Map_t {
    LevelType_t type;
    Vector2 size;
    Tile_t **walls;
    Tile_t **floors;
    Sprite_t *sprites[NUM_SPRITES];
} Map_t;

Map_t *initMap(LevelType_t levelType);
bool isCollisionWallMap(const Map_t *const map, Vector2 position);
bool isInsideMap(LevelType_t type, Vector2 position);
void freeMap(Map_t **ptrMap);
uint32_t getWallTypeMap(LevelType_t type, uint32_t x, uint32_t y);
uint32_t getFloorTypeMap(LevelType_t type, uint32_t x, uint32_t y);
Vector2 getLevelSize(LevelType_t type);
Vector2 getLevelSizeEx(LevelType_t type);

#ifdef __cplusplus
}
#endif
#endif //RC_MAP_H
