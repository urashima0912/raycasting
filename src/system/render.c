#include "render.h"
#include "../../config.h"
#include "../manager/ray.h"
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
static void drawLineShape(const Line_t *const line);
static void drawRay(const Ray_t *const ray);

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
    drawLineShape((Line_t *)player->shapeLine.ptr);
    for (int i=0; i < NUM_RAYS; ++i)
        drawRay(&player->rays[i]);
}
static void drawLineShape(const Line_t *const line) {
    DrawLineV(
        line->ptoA,
        line->ptoB,
        line->color
    );
}
static void drawRay(const Ray_t *const ray) {
    DrawLineV(
        ray->ptoA,
        ray->ptoB,
        ray->color
    );
}



