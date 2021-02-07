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
    initEvent();
    loadGlobalResources();
    initStoreObject();
    while (!WindowShouldClose()) {
        updatePhysic();
        updateEvent();
        updateRender();
    }
    freeGlobalResources();
    freeStoreObject();
    freeGlobalZBuffer();
    CloseWindow();
    return 0;
}