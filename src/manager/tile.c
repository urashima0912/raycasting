#include "tile.h"
#include <raylib.h>

//------------------------------------------------------------------------------------
// Private functions declaration.
//------------------------------------------------------------------------------------
static Color getColorTile(TileType_t type);

//------------------------------------------------------------------------------------
// Public functions implementation.
//------------------------------------------------------------------------------------
Tile_t  initTile(Vector2 position, Vector2 size, TileType_t type) {
    Tile_t tile = {0};
    tile.position = position;
    tile.size = size;
    tile.type = type;
    tile.color = getColorTile(type);
    return tile;
}

//------------------------------------------------------------------------------------
// Private functions implementation.
//------------------------------------------------------------------------------------
static Color getColorTile(TileType_t type) {
    switch (type) {
        case TILE_FLOOR:
            return BLACK;
        default:
            return DARKGRAY;
    }
}

