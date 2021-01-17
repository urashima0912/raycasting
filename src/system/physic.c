#include "physic.h"
#include "../global.h"
#include "../manager/player.h"
#include "../manager/object.h"
#include "../manager/map.h"
#include <raylib.h>
#include <raymath.h>
#include <stdint.h>

//------------------------------------------------------------------------------------
// Private method declaration.
//------------------------------------------------------------------------------------
static void updateObject(Object_t *const obj);
static void updatePlayerPhysic(Player_t *player);
static void updateLineShapePhysic(Line_t *const line, Vector2 ptoA, Vector2 ptoB);
static bool isCollisonVectorMapPhysic(Vector2 position);
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
    Line_t *const line = player->shapeLine.ptr;
    const float angle = getAngleGlobal(player->angle, player->angleVel);
    const float angleCos = cos(angle);
    const float angleSin = sin(angle);
    const Vector2 direction = (Vector2){ angleCos, angleSin };

    Vector2 newPosition = player->position;

    newPosition.x += direction.x * player->velocity.y;
    newPosition.y += direction.y * player->velocity.y;

    Vector2 auxVec = multVectorGlobal(direction, line->mod);
    Vector2 ptoB = addVectorGlobal(player->position, auxVec);

    updateLineShapePhysic(line, player->position, ptoB);
    if (!isCollisonVectorMapPhysic(newPosition))
        player->position = newPosition;

    player->angle = angle;
}
static void updateLineShapePhysic(Line_t *const line, Vector2 ptoA, Vector2 ptoB) {
    line->ptoA = addVectorGlobal(ptoA, (Vector2){ 3, 3});
    line->ptoB = addVectorGlobal(ptoB, (Vector2){ 3, 3});
}
static bool isCollisonVectorMapPhysic(Vector2 position) {
    const Map_t *const map = (Map_t *)storeObject[OBJ_MAP].obj;
    return isCollisionMap(map, position);
}
