#include "render.h"
#include "../../config.h"
#include "../manager/ray.h"
#include "../manager/map.h"
#include "../manager/object.h"
#include "../manager/tile.h"
#include "../manager/player.h"
#include "../manager/sprite.h"
#include "../global.h"

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
static void drawBackground(void);
static void drawSprite(Sprite_t *const sprite);

//------------------------------------------------------------------------------------
// Public methods declaration.
//------------------------------------------------------------------------------------
void initRender(void) {
    InitWindow(
        globalConfig.screeWidth,
        globalConfig.screeHeight,
        globalConfig.screenTitle
    );
    HideCursor();
    SetTargetFPS(SCREEN_FPS);

    const int32_t canvasWidth = globalConfig.canvasWidth;
    const int32_t canvasHeight = globalConfig.canvasHeight;
    const float angle = (globalConfig.FOV / 2) * DEG2RAD;
    distanceToPP = (canvasWidth / 2) / tanf(angle);
    screenMiddle = canvasHeight / 2;
}
void updateRender(void) {
    BeginDrawing();
    ClearBackground(BLANK);
    drawAllObject(&drawObject);
    EndDrawing();
}

//------------------------------------------------------------------------------------
// Private methods implementation.
//------------------------------------------------------------------------------------
static void drawObject(const Object_t *const obj) {
    switch (obj->type) {
        case OBJ_MAP:
            if (globalConfig.viewMap)
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
    const int32_t nRays = globalConfig.canvasNumRays;
    if (globalConfig.viewMap) {
        DrawRectangle(
            player->position.x - 3,
            player->position.y - 3,
            6,
            6,
            RAYWHITE
        );

        for (int i=0; i < nRays; ++i)
            drawRay(&player->rays[i]);

        drawLineShape((Line_t *)player->shapeLine.ptr);
    } else {
        drawBackground();
        const Map_t *const map = (Map_t *)storeObject[OBJ_MAP].obj;
        for (int32_t i=0; i < nRays; ++i)
            drawWall(map, &player->rays[i], i);
        for (int32_t i=0; i < NUM_SPRITES; ++i)
            drawSprite(map->sprites[i]);
    }
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
    float heightWall = (globalConfig.canvasTileHeight /ray->length) * distanceToPP;

    int32_t pY = screenMiddle - (heightWall / 2);
    Vector2 ptoA = (Vector2){column, pY};
//    Vector2 ptoB = (Vector2){column, pY + heightWall};

    Rectangle source = (Rectangle){0};
    source.x = ray->pixelPos;
    source.y = 0;
    source.width = 1;
    source.height = 48; //TODO: check height of image.

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
static void drawBackground(void) {
    const int32_t posY = globalConfig.canvasHeight / 2;
    DrawRectangle(0, 0, globalConfig.canvasWidth, posY, DARKGRAY);
    DrawRectangle(0, posY, globalConfig.canvasWidth, posY, BROWN);
}
static void drawSprite(Sprite_t *const sprite) {
    if (!sprite->visible)
        return;

    const int32_t WIDTH = 64;
    const float heightSprite = (WIDTH/sprite->length) * distanceToPP;
    int32_t  pY0 = screenMiddle - (heightSprite / 2);
    int32_t  pY1 = pY0 + heightSprite;
    const float widthSprite = heightSprite;

    const float pX0 = tanf(sprite->angle) * globalConfig.canvasHeight;
    const float pX = (globalConfig.canvasWidth/2 + pX0 - widthSprite/2);

    const int32_t widthColumn = heightSprite/WIDTH;

    for (int32_t i=0; i < WIDTH; ++i) {
        for (int32_t j=0; j < widthColumn; ++j) {
            const int32_t pX1 = pX + ((i-1)*widthColumn) + j;

            Rectangle source = (Rectangle){0};
            source.x = i;
            source.y = 0;
            source.width = 1;
            source.height = 64;

            Rectangle dest = (Rectangle){0};
            dest.x = pX1;
            dest.y = pY0;
            dest.width = 1;
            dest.height = heightSprite;

            DrawTexturePro(
                sprite->texture,
                source,
                dest,
                (Vector2){0, 0},
                0.0f,
                RAYWHITE
            );
        }
    }
}