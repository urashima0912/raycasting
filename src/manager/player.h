#ifndef RC_PLAYER_H
#define RC_PLAYER_H

#include <raylib.h>
#include <stdint.h>
#include "shape.h"
#include "ray.h"

typedef struct Player_t {
    Vector2 position;
    Vector2 velocity;
    float   angle;
    float   angleVel;
    Shape_t shapeLine;
    Ray_t   rays[NUM_RAYS];
} Player_t;

Player_t    *initPlayer(Vector2 position);
void        freePlayer(Player_t ** ptrPlayer);

#endif //RC_PLAYER_H
