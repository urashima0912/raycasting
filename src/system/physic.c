#include "physic.h"
#include "../global.h"
#include "../manager/player.h"
#include "../manager/object.h"
#include <raylib.h>
#include <raymath.h>

//------------------------------------------------------------------------------------
// Private method declaration.
//------------------------------------------------------------------------------------
static void updateObject(Object_t *const obj);
static void updatePlayerPhysic(Player_t *player);
// all shapes.
static void updateLineShapePhysic(Line_t *const line, Vector2 ptoA, Vector2 ptoB);
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
    const float angleCos = cos(angle * DEG2RAD);
    const float angleSin = sin(angle * DEG2RAD);
    const Vector2 direction = (Vector2){ angleCos, angleSin };

    Vector2 newPosition = player->position;
    newPosition.x += direction.x * player->velocity.y;
    newPosition.y += direction.y * player->velocity.y;

    Vector2 auxVec = multVectorGlobal(direction, line->mod);
    Vector2 ptoB = addVectorGlobal(player->position, auxVec);

    updateLineShapePhysic(line, player->position, ptoB);
    player->position = newPosition;
    player->angle = angle;
}
static void updateLineShapePhysic(Line_t *const line, Vector2 ptoA, Vector2 ptoB) {
    line->ptoA = addVectorGlobal(ptoA, (Vector2){ 3, 3});
    line->ptoB = addVectorGlobal(ptoB, (Vector2){ 3, 3});
}
