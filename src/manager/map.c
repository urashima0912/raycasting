#include "map.h"
#include <stdlib.h>

//------------------------------------------------------------------------------------
// Constants declaration.
//------------------------------------------------------------------------------------
const uint8_t level0[L0_ROW][L0_COLUMN] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 1, 0, 1, 0, 0, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};

//------------------------------------------------------------------------------------
// Private methods declaration.
//------------------------------------------------------------------------------------
static Tile_t **loadTiles(LevelType_t levelType, Vector2 size);

//------------------------------------------------------------------------------------
// Public methods implementation.
//------------------------------------------------------------------------------------
Map_t *initMap(LevelType_t levelType) {
    Map_t *map = malloc(sizeof(Map_t));
    map->type = levelType;
    map->size = (Vector2){ L0_COLUMN, L0_ROW };
    map->tiles = loadTiles(levelType, map->size);
    return map;
}
void freeMap(Map_t **ptrMap) {
    if (*ptrMap != NULL) {
        if ((*ptrMap)->tiles) {
            for (int row=0; row < (*ptrMap)->size.y; ++row) {
                free((*ptrMap)->tiles[row]);
                (*ptrMap)->tiles[row] = NULL;
            }
            free((*ptrMap)->tiles);
            (*ptrMap)->tiles = NULL;
        }
        free((*ptrMap));
        (*ptrMap) = NULL;
    }
}

//------------------------------------------------------------------------------------
// Private methods implementation.
//------------------------------------------------------------------------------------
static Tile_t **loadTiles(LevelType_t levelType, Vector2 size) {
    Tile_t **tiles = NULL;

    const int tileWidth = GetScreenWidth() / size.x;
    const int tileHeight = GetScreenHeight() / size.y;
    const Vector2 tileSize = (Vector2){ tileWidth, tileHeight };

    tiles = malloc(sizeof(Tile_t *) * size.y);
    for (int row=0; row  < size.y; ++row) {
        tiles[row] = malloc(sizeof(Tile_t) * size.x);
        for (int column=0; column < size.x; ++column) {
            const Vector2 tilePos = (Vector2){ column * tileWidth, row *tileHeight };
            const TileType_t type =  level0[row][column];
            tiles[row][column] = initTile(tilePos, tileSize, type);
        }
    }
    return tiles;
}

