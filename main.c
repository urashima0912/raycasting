#include <raylib.h>
#include "src/system/render.h"
#include "src/system/event.h"
#include "src/system/physic.h"
#include "src/manager/object.h"
#include "src/global.h"

int main(void) {
    initGlobalConfig();
    initGlobalZBuffer();
    initRender();
    initStoreObject();
    while (!WindowShouldClose()) {
        updatePhysic();
        updateEvent();
        updateRender();
    }
    freeStoreObject();
    freeGlobalZBuffer();
    CloseWindow();
    return 0;
}