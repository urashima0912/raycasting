#include "physic.h"
#include "../global.h"
#include "../manager/player.h"
#include "../manager/object.h"
#include "../manager/map.h"
#include "../manager/ray.h"
#include <raylib.h>
#include <raymath.h>
#include <stdint.h>

const float TAM_TILE = 50; // CHECK IT.

//------------------------------------------------------------------------------------
// Private method declaration.
//------------------------------------------------------------------------------------
static void updateObject(Object_t *const obj);
static void updatePlayerPhysic(Player_t *player);
static void updateLineShapePhysic(Line_t *const line, Vector2 ptoA, Vector2 ptoB);
static bool isCollisionVectorMapPhysic(Vector2 position);
static void updateRaysPlayer(Player_t *const player);
static void updateRay(Ray_t *const ray);

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
    if (!isCollisionVectorMapPhysic(newPosition))
        player->position = newPosition;

    player->angle = angle;
    updateRaysPlayer(player);
}
static void updateLineShapePhysic(Line_t *const line, Vector2 ptoA, Vector2 ptoB) {
    line->ptoA = ptoA;
    line->ptoB = ptoB;
}
static bool isCollisionVectorMapPhysic(Vector2 position) {
    const Map_t *const map = (Map_t *)storeObject[OBJ_MAP].obj;
    return isCollisionMap(map, position);
}
static void updateRaysPlayer(Player_t *const player) {
    float rayAngle = player->angle - (PI/6);
    const float diffAngle = ((float)FOV * DEG2RAD) / NUM_RAYS;

    for (int i=0; i < NUM_RAYS; ++i) {
        Ray_t *const auxRay = &player->rays[i];
        auxRay->angle = rayAngle;
        updateRay(auxRay);
        rayAngle += diffAngle;
        auxRay->ptoA = player->position;
    }
}
static void updateRay(Ray_t *const ray) {
    const Vector2 ptoA = ray->ptoA;
    Vector2 ptoB = ptoA;
    Vector2 unit = getUnitVectorToAngle(ray->angle);
    Vector2 auxVec = (Vector2){0};
    float mod = 2;
    bool hit = false;
    while (!hit) {
        auxVec = multVectorGlobal(unit, mod);
        ptoB = addVectorGlobal(ptoA, auxVec);
        hit = isCollisionVectorMapPhysic(ptoB);
        if (!hit)
            mod += 2;
    }
    ray->ptoB = ptoB;
}
