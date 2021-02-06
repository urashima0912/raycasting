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

typedef enum LevelType_t {
    LEVEL_0 = 0,
} LevelType_t;

typedef struct Map_t {
    LevelType_t type;
    Vector2 size;
    Texture texture;
    Tile_t **walls;
    Sprite_t *sprites[NUM_SPRITES];
} Map_t;

Map_t *initMap(LevelType_t levelType);
bool isCollisionMap(const Map_t *const map, Vector2 position);
void freeMap(Map_t **ptrMap);

#ifdef __cplusplus
}
#endif
#endif //RC_MAP_H
