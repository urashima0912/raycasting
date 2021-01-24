#include "physic.h"
#include "../global.h"
#include "../manager/player.h"
#include "../manager/object.h"
#include "../manager/map.h"
#include "../manager/ray.h"
#include <raymath.h>
#include <stdint.h>
#include <stdlib.h>

//------------------------------------------------------------------------------------
// Private method declaration.
//------------------------------------------------------------------------------------
static void updateObject(Object_t *const obj);
static void updatePlayerPhysic(Player_t *player);
static void updateLineShapePhysic(Line_t *const line, Vector2 ptoA, Vector2 ptoB);
static bool isCollisionVectorMapPhysic(Vector2 position);
static void updateRaysPlayer(Player_t *const player);
static void updateRay(Ray_t *const ray, const float angle);
//static void updateSprite(Sprite_t *const sprite, const Player_t *const player);

static Vector2 horizontalCollision(const Ray_t *const ray);
static Vector2 verticalCollision(const Ray_t *const ray);

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
//            Map_t *const map = storeObject[OBJ_MAP].obj;
//            for (int32_t i=0; i < NUM_SPRITES; ++i)
//                updateSprite(map->sprites[i], (Player_t *)obj->obj);
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
    float rayAngle = getAngleGlobal(player->angle, -(PI/6));
    const float diffAngle = ((float)FOV * DEG2RAD) / NUM_RAYS;

    for (int i=0; i < NUM_RAYS; ++i) {
        Ray_t *const auxRay = &player->rays[i];
        auxRay->angle = rayAngle;
        updateRay(auxRay, player->angle);
        rayAngle += diffAngle;
        auxRay->ptoA = player->position;
    }
}
static void updateRay(Ray_t *const ray, const float angle) {
    const Vector2 vecH = horizontalCollision(ray);
    const Vector2 vecV = verticalCollision(ray);

    const Vector2 vecTmp = getSmallVector(vecH, vecV);
    const bool isHorizontalCollision = areEqualV(vecH, vecTmp);

    ray->ptoB = addVectorGlobal(ray->ptoA, vecTmp);
    ray->length = getSmallLengthV(vecH, vecV);

    if (isHorizontalCollision) {
        const int32_t diff = (int32_t)(ray->ptoB.x/TAM_TILE) * TAM_TILE;
        ray->pixelPos = ray->ptoB.x - diff;
    }
    else {
        const int32_t diff = (int32_t)(ray->ptoB.y/TAM_TILE) * TAM_TILE;
        ray->pixelPos = ray->ptoB.y - diff;
    }

    // fix eye-fish.
    ray->length = ray->length * cos(angle - ray->angle);
}
//static void updateSprite(Sprite_t *const sprite, const Player_t *const player) {
//    const float pX = sprite->position.x - player->position.x;
//    const float pY = sprite->position.y - player->position.y;
//
//    sprite->length = lengthVectorGlobal((Vector2){pX, pY});
//    float angle = atan2f(pY, pX);
//    float diffAngle = player->angle - angle;
//    if (diffAngle < PI)
//        diffAngle += 2 * PI;
//    else if (diffAngle > PI)
//        diffAngle -= 2 * PI;
//
//    sprite->angle = angle - player->angle; //TODO: check it.
//    const float MIDDLE_FOV = (FOV / 2) * DEG2RAD;
//    sprite->visible = diffAngle < MIDDLE_FOV;
//}
static Vector2 horizontalCollision(const Ray_t *const ray) {
    const float angle = ray->angle;
    const bool lookUp = isLookUp(angle);
    Vector2 ptoA = ray->ptoA;
    Vector2 vecTmp = (Vector2){0};
    Vector2 vecTmp2 = (Vector2){0};

    vecTmp.y = (int32_t)(floor(ptoA.y / TAM_TILE) * TAM_TILE);
    if (!lookUp) vecTmp.y += TAM_TILE;
    vecTmp.y = fabsf(ptoA.y - vecTmp.y);

    if (lookUp) vecTmp.y *= -1;
    vecTmp.x = vecTmp.y / tanf(angle);

    vecTmp2 = vecTmp;
    if (lookUp)
        vecTmp2.y = -(fabsf(vecTmp.y) + 1);
    ptoA = addVectorGlobal(ptoA, vecTmp2);
    while (isPositionInsideMap(ptoA) && !isCollisionVectorMapPhysic(ptoA)) {
        vecTmp2 = (Vector2){0};
        vecTmp2.y = (lookUp) ? -TAM_TILE: TAM_TILE;
        vecTmp2.x = vecTmp2.y / tanf(angle);

        vecTmp = addVectorGlobal(vecTmp, vecTmp2);
        if (lookUp)
            vecTmp2.y = -(TAM_TILE + 1);

        ptoA = addVectorGlobal(ptoA, vecTmp2);
    }

    return vecTmp;
}
static Vector2 verticalCollision(const Ray_t *const ray) {
    const bool lookLeft = isLookLeft(ray->angle);
    const float angle = ray->angle;
    Vector2 ptoA = ray->ptoA;
    Vector2 vecTmp = (Vector2){0};
    Vector2 vecTmp2 = (Vector2){0};

    vecTmp.x = (int32_t)(floor(ptoA.x / TAM_TILE) * TAM_TILE);
    if (!lookLeft) vecTmp.x += TAM_TILE;
    vecTmp.x = fabsf(ptoA.x - vecTmp.x);

    if (lookLeft) vecTmp.x *= -1;
    vecTmp.y = vecTmp.x * tanf(angle);

    vecTmp2 = vecTmp;
    if (lookLeft)
        vecTmp2.x = -(fabsf(vecTmp.x) + 1);
    ptoA = addVectorGlobal(ptoA, vecTmp2);
    while (isPositionInsideMap(ptoA) && !isCollisionVectorMapPhysic(ptoA)) {
        vecTmp2 = (Vector2){0};
        vecTmp2.x = (lookLeft) ? -TAM_TILE: TAM_TILE;
        vecTmp2.y = vecTmp2.x * tanf(angle);

        vecTmp = addVectorGlobal(vecTmp, vecTmp2);
        if (lookLeft)
            vecTmp2.x = -(TAM_TILE + 1);
        ptoA = addVectorGlobal(ptoA, vecTmp2);
    }

    return vecTmp;
}
