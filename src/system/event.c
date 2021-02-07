#include "event.h"
#include "../manager/object.h"
#include "../manager/player.h"
#include "../global.h"


//------------------------------------------------------------------------------------
// Constants and variables declaration.
//------------------------------------------------------------------------------------
static int32_t prevMouseX = 0;

//------------------------------------------------------------------------------------
// Private method declaration.
//------------------------------------------------------------------------------------
static void getEventObject(Object_t *const obj);
static void getEventPlayer(Player_t *player);

//------------------------------------------------------------------------------------
// Public method implementation.
//------------------------------------------------------------------------------------
void initEvent(void) {
    prevMouseX = GetMouseX();
}
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
    player->velocity = (Vector2){0};
    player->angleVel = 0;

    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) {
        player->velocity.y = 2;
    }
    else if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) {
        player->velocity.y = -2;
    }
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
        player->velocity.x = -PI/2;
        player->velocity.y = 2;
    }
    else if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
        player->velocity.x = PI/2;
        player->velocity.y = 2;
    }

    int32_t  currentMouseX = GetMouseX();
    const int32_t diff = 40;
    if (currentMouseX < (prevMouseX - diff) || IsKeyDown(KEY_Q)) {
        player->angleVel = -0.045;
        prevMouseX = currentMouseX;
    } else if (currentMouseX > (prevMouseX + diff) || IsKeyDown(KEY_E)) {
        player->angleVel = 0.045;
        prevMouseX = currentMouseX;
    }

    // Show info map.
    if (IsKeyPressed(KEY_F1))
        globalConfig.viewMap = !globalConfig.viewMap;
    if (IsKeyPressed(KEY_F2))
        globalConfig.viewFPS = !globalConfig.viewFPS;
}


