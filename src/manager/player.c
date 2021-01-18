#include "player.h"
#include <stdlib.h>

//------------------------------------------------------------------------------------
// Private methods declaration.
//------------------------------------------------------------------------------------
static void initPlayerData(Player_t *const player, Vector2 position);
static void initPlayerRays(Player_t *const player);
static void freePlayerRays(Player_t *const player);

//------------------------------------------------------------------------------------
// Public methods implementation.
//------------------------------------------------------------------------------------
Player_t *initPlayer(Vector2 position) {
    Player_t *player = malloc(sizeof(Player_t));
    initPlayerData(player, position);
    return player;
}
void freePlayer(Player_t ** ptrPlayer) {
    if (ptrPlayer) {
        freePlayerRays((*ptrPlayer));
        freeShape(&(*ptrPlayer)->shapeLine);
        free(*ptrPlayer);
        *ptrPlayer = NULL;
    }
}

//------------------------------------------------------------------------------------
// Private methods implementation.
//------------------------------------------------------------------------------------
static void initPlayerData(Player_t *const player, Vector2 position) {
    player->position = position;
    player->shapeLine = initShape(SHAPE_LINE);
    player->angle = 0;
    player->angleVel = 0;
    player->velocity = (Vector2){0};
    initPlayerRays(player);
}
static void initPlayerRays(Player_t *const player) {
    player->rays = malloc(sizeof(struct Ray_t));
}
static void freePlayerRays(Player_t *const player) {
    if (player->rays) {
        TraceLog(LOG_INFO, "RAYS DELETED...");
        free(player->rays);
        player->rays = NULL;
    }
}


