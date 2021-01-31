#include "event.h"
#include "../manager/object.h"
#include "../manager/player.h"
#include "../global.h"

//------------------------------------------------------------------------------------
// Private method declaration.
//------------------------------------------------------------------------------------
static void getEventObject(Object_t *const obj);
static void getEventPlayer(Player_t *player);

//------------------------------------------------------------------------------------
// Public method implementation.
//------------------------------------------------------------------------------------
void updateEvent(void) {
    updateAllObject(&getEventObject);
}

//------------------------------------------------------------------------------------
// Private method implementation.
//------------------------------------------------------------------------------------
static void getEventObject(Object_t *const obj) {
    switch (obj->type) {
        case OBJ_PLAYER:
            getEventPlayer((Player_t *)obj->obj);
            break;
        case OBJ_MAP:
            break;
    }
}
static void getEventPlayer(Player_t *player) {
    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))
        player->velocity.y = 2;
    else if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))
        player->velocity.y = -2;
    else
        player->velocity.y = 0;

    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))
        player->angleVel = -0.05;
    else if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
        player->angleVel = 0.05;
    else
        player->angleVel = 0;

    if (IsKeyPressed(KEY_F1))
        globalConfig.viewMap = !globalConfig.viewMap;
}


