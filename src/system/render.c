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
#include <stdlib.h>

static float distanceToPP = 0.0f;
static int32_t screenMiddle = 0;

//------------------------------------------------------------------------------------
// Private functions declaration.
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
static void drawFPS(void);
static void drawWallTile(const Tile_t *const tile);
static void drawFloorTile(const Tile_t *const tile);
static void drawCeilingTile(const Tile_t *const tile);
static void drawPlayerInfo(void);
static void drawCeiling(const Player_t *const player);
static void drawFloor(void);

//------------------------------------------------------------------------------------
// Public functions declaration.
//------------------------------------------------------------------------------------
void initRender(void) {
    InitWindow(
        globalConfig.screeWidth,
        globalConfig.screeHeight,
        globalConfig.screenTitle
    );
    HideCursor();
    DisableCursor();
    SetTargetFPS(SCREEN_FPS);

    const int32_t canvasWidth = globalConfig.canvasWidth;
    const int32_t canvasHeight = globalConfig.canvasHeight;
    const float angle = (globalConfig.FOV / 2) * DEG2RAD;
    distanceToPP = (canvasWidth / 2) / tanf(angle);
    const float diff = abs(globalConfig.screeHeight - canvasHeight);
    screenMiddle = (canvasHeight - diff)/ 2;
}
void updateRender(void) {
    BeginDrawing();
    ClearBackground(BLACK);
    if (globalConfig.viewMap) {
        BeginMode2D(globalCamera);
        drawAllObject(&drawObject);
        EndMode2D();
    } else {
        drawAllObject(&drawObject);
    }
    drawFPS();
    drawPlayerInfo();
    EndDrawing();
}

//------------------------------------------------------------------------------------
// Private functions implementation.
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
            Tile_t floorTile = map->floors[row][column];
            drawTile(&floorTile);
            Tile_t wallTile = map->walls[row][column];
            drawTile(&wallTile);

        }
    }
}
static void drawTile(const Tile_t *const tile) {
    switch (tile->type) {
        case TILE_WALL:
            drawWallTile(tile);
            break;
        case TILE_FLOOR:
            drawFloorTile(tile);
            break;
        case TILE_CEILING:
            drawCeilingTile(tile);
            break;
    }

}
static void drawWallTile(const Tile_t *const tile) {
    if (tile->number) {
        const int32_t width = globalConfig.canvasTileWidth;
        const int32_t height = globalConfig.canvasTileHeight;
        Rectangle rec = (Rectangle){
            (tile->number * width) - width,
            0,
            width,
            height,
        };
        DrawTextureRec(
            globalConfig.wallsTextures,
            rec,
            tile->position,
            RAYWHITE
        );
    }
}
static void drawFloorTile(const Tile_t *const tile) {
    if (tile->number) {
        const int32_t width = globalConfig.canvasTileWidth;
        const int32_t height = globalConfig.canvasTileHeight;
        Rectangle rec = (Rectangle){
                (tile->number * width) - width,
                0,
                width,
                height,
        };
        DrawTextureRec(
                globalConfig.floorsTextures,
                rec,
                tile->position,
                RAYWHITE
        );
    }
}
static void drawCeilingTile(const Tile_t *const tile) {
    //TODO
}
static void drawPlayer(const Player_t *const player) {
    const int32_t nRays = globalConfig.canvasNumRays;
    if (globalConfig.viewMap) {
        DrawRectangle(
            player->position.x - 3,
            player->position.y - 3,
            6,
            6,
            RED
        );

        for (int i=0; i < nRays; ++i)
            drawRay(&player->rays[i]);

        drawLineShape((Line_t *)player->shapeLine.ptr);
    } else {
        drawBackground();
        const Map_t *const map = (Map_t *)storeObject[OBJ_MAP].obj;
        drawCeiling(player);
        for (int32_t i=0; i < nRays; ++i) {
            drawWall(map, &player->rays[i], i);
        }
//        for (int32_t i=0; i < NUM_SPRITES; ++i)
//            drawSprite(map->sprites[i]);
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
    if (ray->wallType == WALL_EMPTY) {
        return;
    }

    const int32_t tileWidth = globalConfig.canvasTileWidth;
    const int32_t tileHeight = globalConfig.canvasTileHeight;
    const float heightWall = (tileHeight /ray->length) * distanceToPP;
    int32_t pY = screenMiddle - (heightWall / 2);
    Vector2 ptoA = (Vector2){column, pY};

    const uint32_t diff = (ray->wallType * tileWidth) - tileWidth;
    float pixel = ray->pixelPos;

    Rectangle source = (Rectangle){0};
    source.x = diff + pixel;
    source.y = 0;
    source.width = 1;
    source.height = tileHeight;

    Rectangle dest = (Rectangle){0};
    dest.x = ptoA.x;
    dest.y = ptoA.y;
    dest.width = 1;
    dest.height = heightWall;

    DrawTexturePro(
        globalConfig.wallsTextures,
        source,
        dest,
        (Vector2){0, 0},
        0.0f,
        RAYWHITE
    );
}
static void drawBackground(void) {
    const int32_t posY = screenMiddle;
    DrawRectangle(0, 0, globalConfig.canvasWidth, posY, BLACK);
    DrawRectangle(0, posY, globalConfig.canvasWidth, posY, DARKGRAY);
}
//TODO:I need check it(problem with sprite render).
static void drawSprite(Sprite_t *const sprite) {
    if (!sprite->visible)
        return;

    const float heightSprite = (sprite->size.y/sprite->length) * distanceToPP;

    int32_t  pY0 = screenMiddle - (heightSprite / 2);
    int32_t  pY1 = pY0 + heightSprite;
    
    const float heightTexture = fabsf(pY0 - pY1);
    const float widthTexture = heightTexture;
    

    const float pX0 = tanf(sprite->angle) * distanceToPP;
    const float pX = (globalConfig.canvasWidth/2 + pX0 - widthTexture/2);

    const float widthColumn = heightTexture/sprite->size.y;

    for (int32_t i=0; i < sprite->size.x; ++i) {
        for (int32_t j=0; j < (int32_t)widthColumn + 1; ++j) {
            const float pX1 = pX + ((i-1)*widthColumn) + j;
            if (pX1 >= globalConfig.canvasWidth || pX1 < 0)
                break;

            if (globalZBuffer[(int32_t)pX1] < sprite->length)
                break;
            Rectangle source = (Rectangle){0};
            source.x = i;
            source.y = 0;
            source.width = 1;
            source.height = sprite->size.y;

            Rectangle dest = (Rectangle){0};
            dest.x = pX1;
            dest.y = pY0;
            dest.width = 1;
            dest.height = heightTexture;

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
static void drawFPS(void) {
    if (globalConfig.viewFPS) {
        DrawFPS(10, 10);
    }
}
static void drawPlayerInfo(void) {
    if (!globalConfig.playerAngle || !globalConfig.playerPosition) {
        return;
    }

    const float playerAngle = *(globalConfig.playerAngle);
    const Vector2 playerPosition = *(globalConfig.playerPosition);

    if (globalConfig.viewFPS) {
        const int32_t  posX = playerPosition.x;
        const int32_t  posY = playerPosition.y;
        const int32_t fontSize = 20;
        const int32_t angle = playerAngle * RAD2DEG;
        const int32_t column = playerPosition.x/globalConfig.canvasTileWidth;
        const int32_t row = playerPosition.y/globalConfig.canvasTileHeight;
        const char *textPosition = TextFormat("x: %d, y: %d: ", posX, posY);
        const char *textTilePosition = TextFormat("r: %d, c: %d: ", row, column);
        const char *textAngle = TextFormat("angle: %d", angle);
        const Color color = RAYWHITE;
        const int32_t space = 24;
        const int32_t  diff = 10;
        DrawText(textPosition, 10, space + diff, fontSize, color);
        DrawText(textTilePosition, 10, space * 2 + diff, fontSize, color);
        DrawText(textAngle, 10, space * 3 + diff, fontSize, color);
    }
}
static void drawCeiling(const Player_t *const player) {
    //TODO
}
static void drawFloor(void) {
    //TODO
}
