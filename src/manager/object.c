#include "object.h"
#include "map.h"
#include "player.h"
#include "shape.h"

//------------------------------------------------------------------------------------
// Public method implementation.
//------------------------------------------------------------------------------------
void initStoreObject(void) {
    // Load map.
    storeObject[OBJ_MAP].type = OBJ_MAP;
    storeObject[OBJ_MAP].obj = (Map_t *)initMap(LEVEL_0);
    // Load Player.
    const Vector2 playerPos = (Vector2){50, 100};
    storeObject[OBJ_PLAYER].type = OBJ_PLAYER;
    storeObject[OBJ_PLAYER].obj = (Player_t *)initPlayer(playerPos);
}
void updateAllObject(void (*funcPtr)(Object_t *const)) {
    for (int i=0; i < NUM_OBJECTS; ++i)
        funcPtr(&storeObject[i]);
}
void drawAllObject(void (*funcPtr)(const Object_t *const)) {
    for (int i=0; i < NUM_OBJECTS; ++i)
        funcPtr(&storeObject[i]);
}
void freeStoreObject(void) {
    // Free map.
    freeMap((Map_t **)&storeObject[0].obj);
    // Free player.
    freePlayer((Player_t **)&storeObject[1].obj);
}