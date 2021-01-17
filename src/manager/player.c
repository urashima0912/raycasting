#include "player.h"
#include <stdlib.h>

//------------------------------------------------------------------------------------
// Public methods implementation.
//------------------------------------------------------------------------------------
Player_t *initPlayer(Vector2 position) {
    Player_t *player = malloc(sizeof(Player_t));
    player->position = position;
    player->rayLine.ptoA = position;
    player->rayLine.ptoB = (Vector2){0};
    player->rayLine.color = RED;
    return player;
}
void freePlayer(Player_t ** ptrPlayer) {
    if (ptrPlayer) {
        free(*ptrPlayer);
        *ptrPlayer = NULL;
    }
}
