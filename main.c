#include <raylib.h>
#include "src/system/render.h"
#include "src/system/event.h"
#include "src/system/physic.h"
#include "src/manager/object.h"

int main(void) {
    initRender();
    initStoreObject();
    while (!WindowShouldClose()) {
        updatePhysic();
        updateEvent();
        updateRender();
    }
    freeStoreObject();
    CloseWindow();
    return 0;
}