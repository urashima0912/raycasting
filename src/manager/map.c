#include "map.h"

#include <stdlib.h>

const uint8_t level0[L0_ROW][L0_COLUMN] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};

//------------------------------------------------------------------------------------
// Declaration statics methods.
//------------------------------------------------------------------------------------
static Tile_t **loadTiles(LevelType_t levelType, Vector2 size);

//------------------------------------------------------------------------------------
// Implementation public methods.
//------------------------------------------------------------------------------------
Map_t *initMap(LevelType_t levelType) {
    Map_t *map = malloc(sizeof(Map_t));
    map->type = levelType;
    map->size = (Vector2){ L0_COLUMN, L0_ROW };
    map->tiles = loadTiles(levelType, map->size);
    return map;
}

void freeMap(Map_t **map) {
    if (*map != NULL) {
        if ((*map)->tiles) {
            for (int row=0; row < (*map)->size.y; ++row) {
                free((*map)->tiles[row]);
                (*map)->tiles[row] = NULL;
            }
            free((*map)->tiles);
            (*map)->tiles = NULL;
        }
        free((*map));
        (*map) = NULL;
    }
}


//------------------------------------------------------------------------------------
// Implementation static methods.
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

