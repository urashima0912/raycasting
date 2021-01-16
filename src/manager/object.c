#include "object.h"
#include "map.h"
#include "player.h"

//------------------------------------------------------------------------------------
// Public method implementation.
//------------------------------------------------------------------------------------
void initStoreObject(void) {
    // Load map.
    storeObject[0].type = OBJ_MAP;
    storeObject[0].obj = (Map_t *)initMap(LEVEL_0);

    // Load Player.
    const Vector2 playerPos = (Vector2){200, 100};
    storeObject[1].type = OBJ_PLAYER;
    storeObject[1].obj = (Player_t *)initPlayer(playerPos);
}
void updateAllObject(void (*funcPtr)(Object_t *const)) {
    for (int i=0; i < NUM_OBJECTS; ++i)
        funcPtr(&storeObject[i]);
}
void drawAllObject(void (*funcPrt)(const Object_t *const)) {
    for (int i=0; i < NUM_OBJECTS; ++i)
        funcPrt(&storeObject[i]);
}
void freeStoreObject(void) {
    // Free map.
    freeMap((Map_t **)&storeObject[0].obj);
    // Free player.
    freePlayer((Player_t **)&storeObject[1].obj);
}