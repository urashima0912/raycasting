#ifndef RC_TILE_H
#define RC_TILE_H

#include <raylib.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum TileType_t {
    TILE_FLOOR = 0,
    TILE_WALL,
    TILE_CEILING,
} TileType_t;

typedef struct Tile_t {
    Vector2 position;
    Vector2 size;
    TileType_t type;
    Color color;
    uint8_t number;
} Tile_t;

Tile_t initTile(Vector2 position, Vector2 size, TileType_t type, uint32_t number);

#ifdef __cplusplus
}
#endif
#endif //RC_TILE_H
