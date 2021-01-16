#ifndef RC_MAP_H
#define RC_MAP_H

#include <stdint.h>
#include <raylib.h>
#include "tile.h"

#define L0_ROW 10
#define L0_COLUMN 10

typedef enum LevelType_t {
    LEVEL_0 = 0,
}LevelType_t;

typedef struct Map_t {
    LevelType_t type;
    Tile_t **tiles;
    Vector2 size;
}Map_t;

Map_t   *initMap(LevelType_t levelType);
void    freeMap(Map_t *map);

#endif //RC_MAP_H
