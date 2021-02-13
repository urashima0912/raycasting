#include "map.h"
#include "../global.h"
#include <stdlib.h>

//------------------------------------------------------------------------------------
// Constants declaration.
//------------------------------------------------------------------------------------
const WallType_t WALLS_LEVEL_0[L0_ROW][L0_COLUMN] = {
    {1, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 2},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 2},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {4, 0, 0, 0, 0, 0, 4, 0, 4, 0, 0, 0, 0, 0, 0, 2},
    {4, 0, 0, 0, 0, 0, 4, 0, 4, 0, 0, 0, 0, 0, 0, 2},
    {4, 0, 0, 0, 0, 0, 4, 4, 4, 0, 0, 0, 0, 0, 0, 2},
    {4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
};

const FloorType_t FLOORS_LEVEL_0[L0_ROW][L0_COLUMN] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};

//------------------------------------------------------------------------------------
// Private functions declaration.
//------------------------------------------------------------------------------------
static Tile_t **loadTiles(LevelType_t levelType, Vector2 size, TileType_t type);

//------------------------------------------------------------------------------------
// Public functions implementation.
//------------------------------------------------------------------------------------
Map_t *initMap(LevelType_t type) {
    Map_t *map = malloc(sizeof(Map_t));
    map->type = type;
    map->size = getLevelSize(type);
    map->walls = loadTiles(type, map->size, TILE_WALL);

    //TODO: change initSprite.
    map->sprites[0] = initSprite();

    // Initialization level global data.
    globalConfig.currentLevel = type;

    return map;
}
bool isCollisionWallMap(const Map_t *const map, Vector2 position) {
    const float tileWidth =  map->walls[0]->size.x;
    const float tileHeight =  map->walls[0]->size.y;

    const int posX = position.x / tileWidth;
    const int posY = position.y / tileHeight;

    uint32_t wallType = getWallTypeMap(map->type, posX, posY);
    return wallType != WALL_EMPTY;
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
uint32_t getWallTypeMap(LevelType_t type, uint32_t x, uint32_t y) {
    switch (type) {
        case LEVEL_0:
            return WALLS_LEVEL_0[y][x];
        default:
            return -1;
    }
}
Vector2 getLevelSize(LevelType_t type) {
    switch (type) {
        case LEVEL_0:
            return (Vector2){L0_COLUMN, L0_ROW};
        default:
            return (Vector2){0};
    }
}
Vector2 getLevelSizeEx(LevelType_t type) {
    const Vector2 size = getLevelSize(type);
    return (Vector2){
      size.x * globalConfig.canvasTileWidth,
      size.y * globalConfig.canvasTileHeight
    };
}
bool isInsideMap(LevelType_t type, Vector2 position) {
    const Vector2 sizeMap = getLevelSizeEx(type);
    const int32_t tileHeight = globalConfig.canvasTileHeight;
    const bool insideMapX = position.x > 0 && position.x < sizeMap.x;
    const bool insideMapY = position.y > 0 && position.y < sizeMap.y - tileHeight;

    return insideMapX && insideMapY;
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

