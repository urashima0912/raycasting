#include "player.h"
#include <stdlib.h>

//------------------------------------------------------------------------------------
// Public methods implementation.
//------------------------------------------------------------------------------------
Player_t *initPlayer(Vector2 position) {
    Player_t *player = malloc(sizeof(Player_t));
    player->position = position;
    player->shapeLine = initShape(SHAPE_LINE);
    player->angle = 0;
    player->angleVel = 0;
    player->velocity = (Vector2){0};
    return player;
}
void freePlayer(Player_t ** ptrPlayer) {
    if (ptrPlayer) {
        freeShape(&(*ptrPlayer)->shapeLine);
        free(*ptrPlayer);
        *ptrPlayer = NULL;
    }
}
