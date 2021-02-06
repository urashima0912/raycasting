#include "tile.h"
#include <raylib.h>

//------------------------------------------------------------------------------------
// Private functions declaration.
//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------
// Public functions implementation.
//------------------------------------------------------------------------------------
Tile_t  initTile(Vector2 position, Vector2 size, TileType_t type, uint32_t number) {
    Tile_t tile = {0};
    tile.position = position;
    tile.size = size;
    tile.type = type;
    tile.number = number;
    tile.color = RED;
    return tile;
}

//------------------------------------------------------------------------------------
// Private functions implementation.
//------------------------------------------------------------------------------------


