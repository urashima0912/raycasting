#include "physic.h"
#include "../manager/player.h"
#include "../manager/object.h"
#include <raylib.h>
#include <raymath.h>

//------------------------------------------------------------------------------------
// Private method declaration.
//------------------------------------------------------------------------------------
static void updateObject(Object_t *const obj);
static void updatePlayerPhysic(Player_t *player);

//------------------------------------------------------------------------------------
// Public method implementation.
//------------------------------------------------------------------------------------
void updatePhysic(void) {
    updateAllObject(&updateObject);
}

//------------------------------------------------------------------------------------
// Private method implementation.
//------------------------------------------------------------------------------------
static void updateObject(Object_t *const obj) {
    switch (obj->type) {
        case OBJ_PLAYER:
            updatePlayerPhysic((Player_t *)obj->obj);
            break;
        case OBJ_MAP:
            break;
    }
}
static void updatePlayerPhysic(Player_t *player) {
    const float movVel = player->velocity.y;
    Vector2 newPos = player->position;
    float angle = player->angle + player->angleVel;

    if (angle > 360)
        angle = 0;
    else if (angle < 0)
        angle = 360;

    newPos.x += cos(angle * DEG2RAD) * movVel;
    newPos.y += sin(angle * DEG2RAD) * movVel;

    player->position = newPos;
    player->angle = angle;
}
