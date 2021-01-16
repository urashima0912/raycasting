#include "render.h"
#include "../../config.h"
#include "../manager/map.h"
#include "../manager/object.h"
#include "../manager/tile.h"
#include "../manager/player.h"
#include <raylib.h>

//------------------------------------------------------------------------------------
// Private methods declaration.
//------------------------------------------------------------------------------------
static void drawObject(const Object_t *const obj);
static void drawMap(const Map_t *const map);
static void drawTile(const Tile_t *const tile);
static void drawPlayer(const Player_t *const player);

//------------------------------------------------------------------------------------
// Public methods declaration.
//------------------------------------------------------------------------------------
void initRender(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);
    HideCursor();
    SetTargetFPS(SCREEN_FPS);
}
void updateRender(void) {
    BeginDrawing();
    ClearBackground(BLACK);
    drawAllObject(&drawObject);
    EndDrawing();
}

//------------------------------------------------------------------------------------
// Private methods implementation.
//------------------------------------------------------------------------------------
static void drawObject(const Object_t *const obj) {
    switch (obj->type) {
        case OBJ_MAP:
            drawMap((Map_t *)obj->obj);
            break;
        case OBJ_PLAYER:
            drawPlayer((Player_t *)obj->obj);
            break;
    }
}
static void drawMap(const Map_t *const map) {
    const int nRow = map->size.y;
    const int nColumn = map->size.x;
    for (int row=0; row < nRow; ++row) {
        for (int column=0; column < nColumn; ++column) {
            Tile_t tile = map->tiles[row][column];
            drawTile(&tile);
        }
    }
}
static void drawTile(const Tile_t *const tile) {
    DrawRectangle(
        tile->position.x,
        tile->position.y,
        tile->size.x,
        tile->size.y,
        tile->color
    );
}
static void drawPlayer(const Player_t *const player) {
    DrawRectangle(
        player->position.x,
        player->position.y,
        6,
        6,
        RAYWHITE
    );
}

