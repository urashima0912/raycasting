#include "player.h"
#include <stdlib.h>

//------------------------------------------------------------------------------------
// Private methods declaration.
//------------------------------------------------------------------------------------
static void initPlayerData(Player_t *const player, Vector2 position);

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
}

