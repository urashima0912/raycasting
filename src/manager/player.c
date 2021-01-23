#include "player.h"
#include <stdlib.h>

//------------------------------------------------------------------------------------
// Private methods declaration.
//------------------------------------------------------------------------------------
static void initPlayerData(Player_t *const player, Vector2 position);
static void initPlayerRays(Player_t *const player);

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
    for (int i=0; i < NUM_RAYS; ++i) {
        player->rays[i].ptoA = player->position;
        player->rays[i].ptoB = (Vector2){0};
        player->rays[i].angle = 0.0f;
        player->rays[i].angle = 0.0f;
        player->rays[i].color = RAY_COLOR_BASE;
    }
}

