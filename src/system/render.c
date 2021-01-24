#include "render.h"
#include "../../config.h"
#include "../manager/ray.h"
#include "../manager/map.h"
#include "../manager/object.h"
#include "../manager/tile.h"
#include "../manager/player.h"
#include <raylib.h>
#include <raymath.h>

static float distanceToPP = 0.0f;
static int32_t screenMiddle = 0;

//------------------------------------------------------------------------------------
// Private methods declaration.
//------------------------------------------------------------------------------------
static void drawObject(const Object_t *const obj);
static void drawMap(const Map_t *const map);
static void drawTile(const Tile_t *const tile);
static void drawPlayer(const Player_t *const player);
static void drawLineShape(const Line_t *const line);
static void drawRay(const Ray_t *const ray);
static void drawWall(const Map_t *const map, const Ray_t *const ray, int32_t column);

//------------------------------------------------------------------------------------
// Public methods declaration.
//------------------------------------------------------------------------------------
void initRender(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);
    HideCursor();
    SetTargetFPS(SCREEN_FPS);

    const float angle = (FOV / 2) * DEG2RAD;
    distanceToPP = (GetScreenWidth() / 2) / tan(angle);
    screenMiddle = GetScreenHeight() / 2;
}
void updateRender(void) {
    BeginDrawing();
    ClearBackground(DARKBLUE);
    drawAllObject(&drawObject);
    EndDrawing();
}

//------------------------------------------------------------------------------------
// Private methods implementation.
//------------------------------------------------------------------------------------
static void drawObject(const Object_t *const obj) {
    switch (obj->type) {
        case OBJ_MAP:
//            drawMap((Map_t *)obj->obj);
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
//    DrawRectangle(
//        player->position.x - 3,
//        player->position.y - 3,
//        6,
//        6,
//        RAYWHITE
//    );
//
//    for (int i=0; i < NUM_RAYS; ++i)
//        drawRay(&player->rays[i]);
//
//    drawLineShape((Line_t *)player->shapeLine.ptr);
    const Map_t *const map = (Map_t *)storeObject[OBJ_MAP].obj;
    for (int i=0; i < NUM_RAYS; ++i)
        drawWall(map, &player->rays[i], i);
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
static void drawWall(const Map_t *const map, const Ray_t *const ray, int32_t column) {
    float heightWall = (TAM_TILE /ray->length) * distanceToPP;
    int32_t pY = screenMiddle - (heightWall / 2);

    Vector2 ptoA = (Vector2){column, pY};
//    Vector2 ptoB = (Vector2){column, pY + heightWall};

    Rectangle source = (Rectangle){0};
    source.x = ray->pixelPos;
    source.y = 0;
    source.width = 1;
    source.height = 64;

    Rectangle dest = (Rectangle){0};
    dest.x = ptoA.x;
    dest.y = ptoA.y;
    dest.width = 1;
    dest.height = heightWall;

    DrawTexturePro(
        map->texture,
        source,
        dest,
        (Vector2){0, 0},
        0.0f,
        RAYWHITE
    );

//    DrawLineV(ptoA, ptoB, GRAY);
}




