#include "map.h"
#include "../global.h"
#include <stdlib.h>

//------------------------------------------------------------------------------------
// Constants declaration.
//------------------------------------------------------------------------------------
const WallType_t WALLS_LEVEL_0[L0_ROW][L0_COLUMN] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};

const FloorType_t FLOORS_LEVEL_0[L0_ROW][L0_COLUMN] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

//------------------------------------------------------------------------------------
// Private functions declaration.
//------------------------------------------------------------------------------------
static Tile_t **loadTiles(LevelType_t levelType, Vector2 size, TileType_t type);

//------------------------------------------------------------------------------------
// Public functions implementation.
//------------------------------------------------------------------------------------
Map_t *initMap(LevelType_t levelType) {
    Map_t *map = malloc(sizeof(Map_t));
    map->type = levelType;
    map->size = (Vector2){ L0_COLUMN, L0_ROW };
    map->walls = loadTiles(levelType, map->size, TILE_WALL);

    //TODO: change initSprite.
    map->sprites[0] = initSprite();
    return map;
}
bool isCollisionWallMap(const Map_t *const map, Vector2 position) {
    const float tileWidth =  map->walls[0]->size.x;
    const float tileHeight =  map->walls[0]->size.y;

    const int posX = position.x / tileWidth;
    const int posY = position.y / tileHeight;

    return WALLS_LEVEL_0[posY][posX] != WALL_EMPTY;
}
void freeMap(Map_t **ptrMap) {
    if (*ptrMap != NULL) {
        if ((*ptrMap)->walls) {
            for (int row=0; row < (*ptrMap)->size.y; ++row) {
                free((*ptrMap)->walls[row]);
                (*ptrMap)->walls[row] = NULL;
            }
            free((*ptrMap)->walls);
            (*ptrMap)->walls = NULL;
        }
        freeSprite(&((*ptrMap)->sprites[0]));
        free((*ptrMap));
        (*ptrMap) = NULL;
    }
}

//------------------------------------------------------------------------------------
// Private functions implementation.
//------------------------------------------------------------------------------------
static Tile_t **loadTiles(LevelType_t levelType, Vector2 size, TileType_t type) {
    Tile_t **tiles = NULL;
    const int32_t tileWidth = globalConfig.canvasTileWidth;
    const int32_t tileHeight = globalConfig.canvasTileHeight;
    const Vector2 tileSize = (Vector2){ tileWidth, tileHeight };

    tiles = malloc(sizeof(Tile_t *) * size.y);
    for (int row=0; row  < size.y; ++row) {
        tiles[row] = malloc(sizeof(Tile_t) * size.x);
        for (int column=0; column < size.x; ++column) {
            const Vector2 tilePos = (Vector2){ column * tileWidth, row *tileHeight };
            const WallType_t number =  WALLS_LEVEL_0[row][column];
            tiles[row][column] = initTile(tilePos, tileSize, type, number);
        }
    }
    return tiles;
}

